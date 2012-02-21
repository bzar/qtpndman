#include "context.h"
#include "util.h"

#include <QDebug>

namespace
{
  int counter = 0;
}

QPndman::Context::Context(QObject* parent) : QObject(parent), d(new Data)
{  
  if(counter == 0)
    pndman_init();
  ++counter;

  d->localPndmanRepository = pndman_repository_init();
  d->pndmanRepositories = d->localPndmanRepository;
}

QPndman::Context::~Context()
{
  pndman_repository_free_all(d->pndmanRepositories);
  d->pndmanRepositories = 0;
  d->localPndmanRepository = 0;
  
  pndman_device_free_all(d->pndmanDevices);
  d->pndmanDevices = 0;
  d.clear();
  --counter;
  if(counter == 0)
    pndman_quit();
}

QPndman::Context::Data::Data() : 
  localPndmanRepository(0), pndmanRepositories(0), pndmanDevices(0)
{
}

QPndman::Context::Data::~Data()
{
}

pndman_repository* QPndman::Context::addPndmanRepository(QString const& url)
{
  return pndman_repository_add(url.toLocal8Bit().data(), d->pndmanRepositories);
}

void QPndman::Context::removePndmanRepository(pndman_repository* repository)
{
  if(d)
  {
    for(pndman_repository* r = d->pndmanRepositories; r; r = r->next)
    {
      if(r == repository)
      {
        d->pndmanRepositories = pndman_repository_free(repository);
        break;
      }
    }
  }
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
  if(d)
  {
    for(pndman_device* dev = d->pndmanDevices; dev; dev = dev->next)
    {
      if(dev == device)
      {
        d->pndmanDevices = pndman_device_free(device);
        break;
      }
    }  
  }
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

bool QPndman::Context::crawlPndmanDevice(pndman_device* device)
{
  return pndman_crawl(device, d->localPndmanRepository);
}

bool QPndman::Context::saveRepositories(pndman_device* device)
{
  return pndman_commit_all(d->pndmanRepositories, device) == 0;
}

bool QPndman::Context::loadRepository(pndman_repository* repository, pndman_device* device)
{
  return pndman_read_from_device(repository, device) == 0;
}
