#include "manager.h"

#include <QDebug>

QScopedPointer<QPndman::Manager> QPndman::Manager::_manager(0);

QPndman::Manager* QPndman::Manager::getManager()
{
  if(_manager.isNull())
  {
    _manager.reset(new Manager);
  }
  
  return _manager.data();
}


QPndman::Manager::~Manager()
{
  pndman_quit();
}


bool QPndman::Manager::addRepository(QString const& url)
{
  if(pndman_repository_add(url.toLocal8Bit().data(), &_repositories))
    return false;
  
  emit repositoriesChanged(getRepositories());
  return true;
}

bool QPndman::Manager::removeRepository(QString const& url)
{
  for(pndman_repository* r = &_repositories; r != 0; r = r->next)
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
  pndman_repository_free_all(&_repositories);
}

QList<QPndman::Repository*> QPndman::Manager::getRepositories()
{
  QList<Repository*> repositories;
  for(pndman_repository* r = &_repositories; r != 0; r = r->next)
  {
    repositories << new Repository(r->url, r->name, r->updates, QDateTime::fromTime_t(r->timestamp), r->version, QList<Package>(), r->exist);
  }
  
  return repositories;
}


bool QPndman::Manager::addDevice(QString const& path)
{
  if(pndman_device_add(path.toLocal8Bit().data(), &_devices))
    return false;
  
  pndman_device* latestDevice = &_devices;
  while(latestDevice->next != 0)
    latestDevice = latestDevice->next;
  
  if(pndman_read_from_device(&_repositories, latestDevice))
    return false;
  
  emit devicesChanged(getDevices());
  return true;
}

bool QPndman::Manager::detectDevices()
{
  return false;
}

bool QPndman::Manager::removeDevice(QString const& path)
{
  for(pndman_device* d = &_devices; d != 0; d = d->next)
  {
    if(QString(d->mount) == path || QString(d->device) == path)
    {
      pndman_device_free(d);
      return true;
    }
  }
  return false;
}

bool QPndman::Manager::removeAllDevices()
{
  pndman_device_free_all(&_devices);
}

QList<QPndman::Device*> QPndman::Manager::getDevices()
{
  QList<Device*> devices;
  for(pndman_device* d = &_devices; d != 0; d = d->next)
  {
    devices << new Device(d->mount, d->device, d->size, d->free, d->available);
  }
  
  return devices;
}


QPndman::Handle* QPndman::Manager::createHandle(QString const& name)
{
  return 0;
}

bool QPndman::Manager::performHandle(Handle* handle)
{
  return false;
}

bool QPndman::Manager::removeHandle(Handle* handle)
{
  return false;
}


int QPndman::Manager::download()
{
  return pndman_download();
}

bool QPndman::Manager::sync(Repository* repository)
{
  for(pndman_repository* r = &_repositories; r != 0; r = r->next)
  {
    if(QString(r->url) == repository->getUrl())
    {
      pndman_sync_request(r);
      pndman_sync();
      return true;
    }
  }
  
  return false;
}

int QPndman::Manager::sync(QList<Repository*> const& repositories)
{
  int result = 0;
  foreach(Repository* r, repositories)
  {
    if(sync(r))
    {
      result += 1;
    }
  }
  return result;
}

int QPndman::Manager::syncAll()
{
  int result = 0;
  for(pndman_repository* r = &_repositories; r != 0; r = r->next)
  {
    pndman_sync_request(r);
    result += pndman_sync();
  }
  return result;
}


QPndman::Manager::Manager() : QObject(0), _repositories(), _devices()
{
  pndman_init();
  pndman_repository_init(&_repositories);
  pndman_device_init(&_devices);
}
