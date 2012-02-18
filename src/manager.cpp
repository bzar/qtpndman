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


QPndman::Handle QPndman::Manager::createHandle(QString const& name)
{
  Handle handle;
  pndman_handle_init(name.toLocal8Bit().data(), handle.getPndmanHandle());
  handle.update();
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
      pndman_sync_request(handle.getPndmanSyncHandle(), r);
      handle.update();
      d->syncTimer.start();
      emit syncStarted(handle);
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
        pndman_sync_request(handle.getPndmanSyncHandle(), r);
        handle.update();
        handles << handle;
        emit syncStarted(handle);
      }
    }
  }

  d->syncTimer.start();
  return handles;
}

QList<QPndman::SyncHandle> QPndman::Manager::syncAll()
{
  QList<SyncHandle> handles;
  for(pndman_repository* r = &d->repositories; r != 0; r = r->next)
  {
    SyncHandle handle;
    pndman_sync_request(handle.getPndmanSyncHandle(), r);
    handle.update();
    handles << handle;
    emit syncStarted(handle);
  }

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
  connect(&d->syncTimer, SIGNAL(timeout()), this, SLOT(continueSyncing()));
}

QPndman::Manager::Data::Data() : repositories(), devices(), syncTimer()
{
  
}
bool QPndman::Manager::currentlySyncing() const
{
  return d->syncTimer.isActive();
}

void QPndman::Manager::continueSyncing()
{
  qDebug() << "syncing";
  int status = pndman_sync();
  if(status > 0)
  {
    return;
  }
  else if(status == 0)
  {
    qDebug() << "syncing finished";
    d->syncTimer.stop();
    emit syncFinished();
  }
  else
  {
    qDebug() << "syncing error";
    d->syncTimer.stop();
    emit syncError();    
  }
}