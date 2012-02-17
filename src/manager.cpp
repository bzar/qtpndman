#include "manager.h"
#include "util.h"

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
  removeAllDevices();
  removeAllRepositories();
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

QList< QSharedPointer<QPndman::Repository> > QPndman::Manager::getRepositories()
{
  return makeQList<pndman_repository, Repository>(&_repositories);
}


bool QPndman::Manager::addDevice(QString const& path)
{
  if(pndman_device_add(path.toLocal8Bit().data(), &_devices))
    return false;
  
  pndman_device* latestDevice = &_devices;
  while(latestDevice->next != 0)
    latestDevice = latestDevice->next;
  
  emit devicesChanged(getDevices());
  return true;
}

bool QPndman::Manager::detectDevices()
{
  return pndman_device_detect(&_devices) == 0;
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
  return pndman_device_free_all(&_devices) == 0;
}

QList< QSharedPointer<QPndman::Device> > QPndman::Manager::getDevices()
{
  return makeQList<pndman_device, Device>(&_devices);
}


QPndman::Handle* QPndman::Manager::createHandle(QString const& name)
{
  Handle* handle = new Handle;
  if(pndman_handle_init(name.toLocal8Bit().data(), handle->getPndmanHandle()))
    return 0;
  handle->update();
  return handle;
}

bool QPndman::Manager::performHandle(Handle* handle)
{
  return pndman_handle_perform(handle->getPndmanHandle()) == 0;
}

bool QPndman::Manager::removeHandle(Handle* handle)
{
  if(pndman_handle_free(handle->getPndmanHandle()))
    return false;
  delete handle;
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
    }
  }

  int result = 0;
  while(result = pndman_sync() > 0);
  return result != -1;
}

bool QPndman::Manager::sync(QList<Repository*> const& repositories)
{
  foreach(Repository* repository, repositories)
  {
    for(pndman_repository* r = &_repositories; r != 0; r = r->next)
    {
      if(QString(r->url) == repository->getUrl())
      {
        pndman_sync_request(r);
      }
    }
  }

  int result = 0;
  while(result = pndman_sync() > 0);
  return result != -1;
}

bool QPndman::Manager::syncAll()
{
  for(pndman_repository* r = &_repositories; r != 0; r = r->next)
  {
    pndman_sync_request(r);
  }

  int result = 0;
  while(result = pndman_sync() > 0);
  return result != -1;
}


QPndman::Manager::Manager() : QObject(0), _repositories(), _devices()
{
  pndman_init();
  pndman_repository_init(&_repositories);
  pndman_device_init(&_devices);
}
