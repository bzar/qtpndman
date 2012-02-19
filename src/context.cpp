#include "context.h"
#include "util.h"

#include <QDebug>

namespace
{
  int counter = 0;
}

QPndman::Context::Context() : QObject(0), d(new Data)
{  
  pndman_repository_init(&d->pndmanRepositories);
  pndman_device_init(&d->pndmanDevices);
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
}

QPndman::Context::Data::Data() : 
  pndmanRepositories(), pndmanDevices()
{
  if(counter == 0)
    pndman_init();
  ++counter;

}
QPndman::Context::Data::~Data()
{
  --counter;
  if(counter == 0)
    pndman_quit();
}

pndman_repository* QPndman::Context::getPndmanRepositories()
{
  return &d->pndmanRepositories;
}

pndman_repository* QPndman::Context::getLastPndmanRepository()
{
  return getLast(&d->pndmanRepositories);
}

pndman_repository* QPndman::Context::getLocalPndmanRepository()
{
  return &d->pndmanRepositories;
}

pndman_device* QPndman::Context::getPndmanDevices()
{
  return &d->pndmanDevices;
}

pndman_device* QPndman::Context::getLastPndmanDevice()
{
  return getLast(&d->pndmanDevices);
}

