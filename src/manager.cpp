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


bool QPndman::Manager::addRepository(QString const& url)
{
  if(pndman_repository_add(url.toLocal8Bit().data(), &d->repositories))
    return false;
  
  emit repositoriesChanged(getRepositories());
  return true;
}

bool QPndman::Manager::removeRepository(QString const& url)
{
  for(pndman_repository* r = &d->repositories; r != 0; r = r->next)
  {
    if(QString(r->url) == url)
    {
      pndman_repository_free(r);
      return true;
    }
  }
  return false;
}

bool QPndman::Manager::removeAllRepositories()
{
  return pndman_repository_free_all(&d->repositories) == 0;
}

QList<QPndman::Repository> QPndman::Manager::getRepositories()
{
  return makeQList<pndman_repository, Repository>(&d->repositories);
}


bool QPndman::Manager::addDevice(QString const& path)
{
  if(pndman_device_add(path.toLocal8Bit().data(), &d->devices))
    return false;
  
  pndman_device* latestDevice = &d->devices;
  while(latestDevice->next != 0)
    latestDevice = latestDevice->next;
  
  emit devicesChanged(getDevices());
  return true;
}

bool QPndman::Manager::detectDevices()
{
  return pndman_device_detect(&d->devices) == 0;
}

bool QPndman::Manager::removeDevice(QString const& path)
{
  for(pndman_device* dev = &d->devices; dev != 0; dev = dev->next)
  {
    if(QString(dev->mount) == path || QString(dev->device) == path)
    {
      pndman_device_free(dev);
      return true;
    }
  }
  return false;
}

bool QPndman::Manager::removeAllDevices()
{
  return pndman_device_free_all(&d->devices) == 0;
}

QList<QPndman::Device> QPndman::Manager::getDevices()
{
  return makeQList<pndman_device, Device>(&d->devices);
}


QPndman::Handle QPndman::Manager::install(Package package, Device device, Handle::InstallLocation location)
{
  Handle handle;
  pndman_handle_init("FOO", handle.getPndmanHandle());
  handle.update();
  handle.setOperation(Handle::Install);
  handle.setPackage(package);
  handle.setDevice(device);
  handle.setInstallLocation(location);
  handle.execute();
  return handle;  
}

QPndman::Handle QPndman::Manager::remove(Package package, Device device)
{
  Handle handle;
  pndman_handle_init("FOO", handle.getPndmanHandle());
  handle.update();
  handle.setOperation(Handle::Remove);
  handle.setPackage(package);
  handle.setDevice(device);
  handle.execute();
  return handle;
}

int QPndman::Manager::download()
{
  return pndman_download();
}

QPndman::SyncHandle QPndman::Manager::sync(Repository repository)
{
  SyncHandle handle;
  for(pndman_repository* r = &d->repositories; r != 0; r = r->next)
  {
    if(QString(r->url) == repository.getUrl())
    {
      if(initSyncHandle(handle, r))
      {
        d->syncTimer.start();
      }
    }
  }

  return handle;
}

QList<QPndman::SyncHandle> QPndman::Manager::sync(QList<Repository> const& repositories)
{
  QList<SyncHandle> handles;
  foreach(Repository repository, repositories)
  {
    for(pndman_repository* r = &d->repositories; r != 0; r = r->next)
    {
      if(QString(r->url) == repository.getUrl())
      {
        SyncHandle handle;
        if(initSyncHandle(handle, r))
        {
          handles << handle;
        }
      }
    }
  }

  if(!handles.isEmpty())
    d->syncTimer.start();
  
  return handles;
}

QList<QPndman::SyncHandle> QPndman::Manager::syncAll()
{
  QList<SyncHandle> handles;
  for(pndman_repository* r = &d->repositories; r != 0; r = r->next)
  {
    SyncHandle handle;
    if(initSyncHandle(handle, r))
    {
      handles << handle;
    }
  }

  if(!handles.isEmpty())
    d->syncTimer.start();
  
  return handles;
}


QPndman::Manager::Manager() : QObject(0), d(new Data)
{
  pndman_init();
  pndman_repository_init(&d->repositories);
  pndman_device_init(&d->devices);
  
  d->syncTimer.setInterval(100);
  d->syncTimer.setSingleShot(false);
  d->cleanTimer.setInterval(1000);
  d->cleanTimer.setSingleShot(false);
  connect(&d->syncTimer, SIGNAL(timeout()), this, SLOT(continueSyncing()));
  connect(&d->cleanTimer, SIGNAL(timeout()), this, SLOT(cleanUp()));
  connect(this, SIGNAL(syncStarted(SyncHandle)), &d->cleanTimer, SLOT(start()));
}

QPndman::Manager::Data::Data() : repositories(), devices(), handles(), syncHandles(), syncTimer(), cleanTimer()
{
  
}
bool QPndman::Manager::currentlySyncing() const
{
  return d->syncTimer.isActive();
}

void QPndman::Manager::continueSyncing()
{
  int status = pndman_sync();
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

bool QPndman::Manager::initSyncHandle(SyncHandle& handle, pndman_repository* r)
{
  if(pndman_sync_request(handle.getPndmanSyncHandle(), r))
  {
    handle.update();
    emit syncError(handle);
    return false;
  }
  
  handle.update();
  d->syncHandles << handle;
  emit syncStarted(handle);
  return true;
}

void QPndman::Manager::cleanUp()
{
  QMutableListIterator<SyncHandle> shi(d->syncHandles);
  while(shi.hasNext()) 
  {
    SyncHandle sh = shi.next();
    if(sh.getPndmanSyncHandle()->done)
    {
      shi.remove();
    }
  }

  QMutableListIterator<Handle> hi(d->handles);
  while(hi.hasNext()) 
  {
    Handle h = hi.next();
    if(h.getPndmanHandle()->done)
    {
      hi.remove();
    }
  }
  
  if(d->syncHandles.size() == 0 && d->handles.size() == 0)
  {
    d->cleanTimer.stop();
  }
}

