#include "context.h"
#include "util.h"

#include <QDebug>

namespace
{
  int counter = 0;
}

QPndman::Context::Context() : QObject(0), d(new Data)
{  
}


QPndman::Context::Context(Context const& other) : d(other.d)
{
}

QPndman::Context& QPndman::Context::operator=(Context const& other)
{
  if(&other != this) 
  {
    d = other.d;
  }
  
  return *this;
  
}

QPndman::Context::~Context()
{
  emit destroyed();
}

QPndman::Context::Data::Data() : 
  localPndmanRepository(0), pndmanRepositories(0), pndmanDevices(0)
{
  if(counter == 0)
    pndman_init();
  ++counter;

  localPndmanRepository = pndman_repository_init();
  pndmanRepositories = localPndmanRepository;
}

QPndman::Context::Data::~Data()
{
  pndman_repository_free_all(pndmanRepositories);
  pndman_device_free_all(pndmanDevices);
  
  --counter;
  if(counter == 0)
    pndman_quit();
}

pndman_repository* QPndman::Context::addPndmanRepository(QString const& url)
{
  return pndman_repository_add(url.toLocal8Bit().data(), d->pndmanRepositories);
}

void QPndman::Context::removePndmanRepository(pndman_repository* repository)
{
  d->pndmanRepositories = pndman_repository_free(repository);
}

pndman_repository* QPndman::Context::getPndmanRepositories()
{
  return d->pndmanRepositories;
}

pndman_repository* QPndman::Context::getLastPndmanRepository()
{
  return getLast(d->pndmanRepositories);
}

pndman_repository* QPndman::Context::getLocalPndmanRepository()
{
  return d->localPndmanRepository;
}

pndman_device* QPndman::Context::addPndmanDevice(QString const& path)
{
  pndman_device* device = pndman_device_add(path.toLocal8Bit().data(), d->pndmanDevices);
  if(!d->pndmanDevices)
  {
    d->pndmanDevices = device;
  }
  
  return device;
}

void QPndman::Context::removePndmanDevice(pndman_device* device)
{
  d->pndmanDevices = pndman_device_free(device);
}

pndman_device* QPndman::Context::getPndmanDevices()
{
  return d->pndmanDevices;
}

pndman_device* QPndman::Context::getLastPndmanDevice()
{
  return getLast(d->pndmanDevices);
}

pndman_device* QPndman::Context::detectPndmanDevices()
{
  return pndman_device_detect(d->pndmanDevices);
}