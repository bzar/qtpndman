#include "manager.h"
#include "util.h"

#include <QDebug>

QPndman::Manager* QPndman::Manager::getManager()
{
  static Manager manager;
  return &manager;
}

QPndman::Manager::Manager(Manager const& other) : d(other.d)
{
}

QPndman::Manager::~Manager()
{
  removeAllDevices();
  removeAllRepositories();
  pndman_quit();
}


QPndman::Repository* QPndman::Manager::addRepository(QString const& url)
{
  if(pndman_repository_add(url.toLocal8Bit().data(), &d->pndmanRepositories))
    return 0;
  
  Repository* repository = new Repository(getLast(&d->pndmanRepositories));
  repository->setParent(this);
  d->repositories << repository;
  emit repositoriesChanged();
  return repository;
}

bool QPndman::Manager::removeRepository(Repository* repository)
{
  QMutableListIterator<Repository*> i(d->repositories);
  while(i.hasNext()) 
  {
    Repository* r = i.next();
    if(repository->getIdentifier() == r->getIdentifier())
    {
      pndman_repository_free(r->getPndmanRepository());
      i.remove();
      delete r;
      return true;
    }

  }
  return false;
}

bool QPndman::Manager::removeAllRepositories()
{
  foreach(Repository* r, d->repositories)
  {
    delete r;
  }
  d->repositories.clear();
  return pndman_repository_free_all(&d->pndmanRepositories) == 0;
}

QList<QPndman::Repository*> QPndman::Manager::getRepositories()
{
  return d->repositories;
}


QPndman::Device* QPndman::Manager::addDevice(QString const& path)
{
  if(pndman_device_add(path.toLocal8Bit().data(), &d->pndmanDevices))
    return 0;
  
  Device* device = new Device(getLast(&d->pndmanDevices));
  device->setParent(this);
  d->devices << device;
  emit devicesChanged();
  return device;
}

QList<QPndman::Device*> QPndman::Manager::detectDevices()
{
  QList<Device*> detectedDevices;
  pndman_device* prevLast = getLast(&d->pndmanDevices);
  if(pndman_device_detect(&d->pndmanDevices) == 0)
  {
    for(pndman_device* dev = prevLast->next; dev != 0; dev = dev->next)
    {
      Device* device = new Device(dev);
      device->setParent(this);
      d->devices << device;
      detectedDevices << device;
    }
  }
  
  if(!detectedDevices.empty())
  {
    emit devicesChanged();
  }
  return detectedDevices;
}

bool QPndman::Manager::removeDevice(Device* device)
{
  QMutableListIterator<Device*> i(d->devices);
  while(i.hasNext())
  {
    Device* d = i.next();
    if(device->getIdentifier() == d->getIdentifier())
    {
      pndman_device_free(d->getPndmanDevice());
      i.remove();
      return true;
    }

  }
  return false;
}

bool QPndman::Manager::removeAllDevices()
{
  d->devices.clear();
  return pndman_device_free_all(&d->pndmanDevices) == 0;
}

QList<QPndman::Device*> QPndman::Manager::getDevices()
{
  return d->devices;
}


QPndman::Handle* QPndman::Manager::install(Package package, Device* device, Handle::InstallLocation location)
{
  Handle* handle = new Handle;
  handle->setParent(this);
  pndman_handle_init("FOO", handle->getPndmanHandle());
  handle->update();
  handle->setOperation(Handle::Install);
  handle->setPackage(package);
  handle->setDevice(device);
  handle->setInstallLocation(location);
  handle->execute();
  d->handles << handle;
  return handle;
}

QPndman::Handle* QPndman::Manager::remove(Package package, Device* device)
{
  Handle* handle = new Handle;
  handle->setParent(this);
  pndman_handle_init("FOO", handle->getPndmanHandle());
  handle->update();
  handle->setOperation(Handle::Remove);
  handle->setPackage(package);
  handle->setDevice(device);
  handle->execute();
  d->handles << handle;
  return handle;
}

int QPndman::Manager::download()
{
  return pndman_download();
}

QPndman::SyncHandle* QPndman::Manager::sync(Repository* repository)
{
  SyncHandle* handle = createSyncHandle(repository);
  if(handle)
  {
    d->syncTimer.start();
  }

  return handle;
}

QList<QPndman::SyncHandle*> QPndman::Manager::sync(QList<Repository*> const& repositories)
{
  QList<SyncHandle*> handles;
  foreach(Repository* repository, repositories)
  {
    SyncHandle* handle = createSyncHandle(repository);
    if(handle)
    {
      handles << handle;
    }
  }

  if(!handles.isEmpty())
    d->syncTimer.start();
  
  return handles;
}

QList<QPndman::SyncHandle*> QPndman::Manager::syncAll()
{
  return sync(d->repositories);
}


QPndman::Manager::Manager() : QObject(0), d(new Data)
{
  pndman_init();
  pndman_repository_init(&d->pndmanRepositories);
  pndman_device_init(&d->pndmanDevices);
  
  Repository* local = new Repository(&d->pndmanRepositories);
  local->setParent(this);
  d->repositories << local;

  d->syncTimer.setInterval(100);
  d->syncTimer.setSingleShot(false);
  d->cleanTimer.setInterval(1000);
  d->cleanTimer.setSingleShot(false);
  connect(&d->syncTimer, SIGNAL(timeout()), this, SLOT(continueSyncing()));
  connect(&d->cleanTimer, SIGNAL(timeout()), this, SLOT(cleanUp()));
  connect(this, SIGNAL(syncStarted(SyncHandle*)), &d->cleanTimer, SLOT(start()));
}

QPndman::Manager::Data::Data() : 
  pndmanRepositories(), pndmanDevices(), handles(), syncHandles(), 
  repositories(), devices(), syncTimer(), cleanTimer()
{
}
bool QPndman::Manager::currentlySyncing() const
{
  return d->syncTimer.isActive();
}

void QPndman::Manager::continueSyncing()
{
  int status = pndman_sync();
  foreach(SyncHandle* handle, d->syncHandles)
  {
    handle->update();
  }

  if(status == 0)
  {
    d->syncTimer.stop();
    emit syncFinished();
  }
  else if(status < 0)
  {
    d->syncTimer.stop();
    emit syncError();    
  }
  else
  {
    emit syncing();
  }
  
}

QPndman::SyncHandle* QPndman::Manager::createSyncHandle(Repository* repository)
{
  SyncHandle* handle = new SyncHandle(repository);
  handle->setParent(this);
  if(pndman_sync_request(handle->getPndmanSyncHandle(), repository->getPndmanRepository()))
  {
    handle->update();
    emit syncError(handle);
    delete handle;
    return 0;
  }
  
  handle->update();
  d->syncHandles << handle;
  emit syncStarted(handle);
  return handle;
}

void QPndman::Manager::cleanUp()
{
  QMutableListIterator<SyncHandle*> shi(d->syncHandles);
  while(shi.hasNext()) 
  {
    SyncHandle* sh = shi.next();
    if(sh->getPndmanSyncHandle()->done)
    {
      shi.remove();
      delete sh;
    }
  }

  QMutableListIterator<Handle*> hi(d->handles);
  while(hi.hasNext()) 
  {
    Handle* h = hi.next();
    if(h->getPndmanHandle()->done)
    {
      hi.remove();
      delete h;
    }
  }
  
  if(d->syncHandles.size() == 0 && d->handles.size() == 0)
  {
    d->cleanTimer.stop();
  }
}

