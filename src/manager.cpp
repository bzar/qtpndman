#include "manager.h"

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
  {
    emit repositoriesChanged(getRepositories());
    return true;
  }
  
  return false;
}

bool QPndman::Manager::removeRepository(QString const& url)
{
  return false;
}

bool QPndman::Manager::removeAllRepositories()
{
  return false;
}

QList<QPndman::Repository*> QPndman::Manager::getRepositories()
{
  return QList<Repository*>();
}


bool QPndman::Manager::addDevice(QString const& path)
{
  return false;
}

bool QPndman::Manager::detectDevices()
{
  return false;
}

bool QPndman::Manager::removeDevice(QString const& path)
{
  return false;
}

bool QPndman::Manager::removeAllDevices()
{
  return false;
}

QList<QPndman::Device*> QPndman::Manager::getDevices()
{
  return QList<Device*>();
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
  return 0;
}

bool QPndman::Manager::sync(Repository* repository)
{
  return false;
}

int QPndman::Manager::sync(QList<Repository*> const& repositories)
{
  return 0;
}

int QPndman::Manager::syncAll()
{
  return 0;
}


QPndman::Manager::Manager() : QObject(0), _repositories(), _devices()
{
  pndman_init();
  pndman_repository_init(&_repositories);
  pndman_device_init(&_devices);
}
