#include "device.h"

QPndman::Device::Device() : QObject(0), d()
{
  
}
QPndman::Device::Device(pndman_device* p) : QObject(0), d(new Data(p))
{
  
}
int QPndman::Device::Data::nextIdentifier = 1;

QPndman::Device::Data::Data(pndman_device* p) : identifier(nextIdentifier++),
  pndmanDevice(p), mount(p->mount), device(p->device), 
  size(p->size), free(p->free), available(p->available), appdata(p->appdata)
{
}

QPndman::Device::Device(Device const& other) : QObject(0), d(other.d)
{
}

QPndman::Device& QPndman::Device::operator=(Device const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

pndman_device* QPndman::Device::getPndmanDevice() const
{
  return d->pndmanDevice;
}

bool QPndman::Device::isNull() const
{
  return !d;
}

int QPndman::Device::getIdentifier() const
{
  return isNull() ? 0 : d->identifier;
}

QString QPndman::Device::getMount() const
{
  return isNull() ? "" : d->mount;
}
QString QPndman::Device::getDevice() const
{
  return isNull() ? "" : d->device;
}
qint64 QPndman::Device::getSize() const
{
  return isNull() ? 0 : d->size;
}
qint64 QPndman::Device::getFree() const
{
  return isNull() ? 0 : d->free;
}
qint64 QPndman::Device::getAvailable() const
{
  return isNull() ? 0 : d->available;
}
QString QPndman::Device::getAppdata() const
{
  return isNull() ? "" : d->appdata;
}

void QPndman::Device::update()
{
  setMount(d->pndmanDevice->mount);
  setDevice(d->pndmanDevice->device);
  setSize(d->pndmanDevice->size);
  setFree(d->pndmanDevice->free);
  setAvailable(d->pndmanDevice->available);
  setAppdata(d->pndmanDevice->appdata);
}

void QPndman::Device::setMount(QString const& mount)
{
  if(!isNull() && mount != d->mount) 
  {
    d->mount = mount; 
    emit mountChanged(d->mount);
  }
}
void QPndman::Device::setDevice(QString const& device)
{
  if(!isNull() && device != d->device) 
  {
    d->device = device; 
    emit deviceChanged(d->device);
  }
}
void QPndman::Device::setSize(qint64 const& size)
{
  if(!isNull() && size != d->size) 
  {
    d->size = size; 
    emit sizeChanged(d->size);
  }
}
void QPndman::Device::setFree(qint64 const& free)
{
  if(!isNull() && free != d->free) 
  {
    d->free = free; 
    emit freeChanged(d->free);
  }
}
void QPndman::Device::setAvailable(qint64 const& available)
{
  if(!isNull() && available != d->available) 
  {
    d->available = available; 
    emit availableChanged(d->available);
  }
}
void QPndman::Device::setAppdata(QString const& appdata)
{
  if(!isNull() && appdata != d->appdata) 
  {
    d->appdata = appdata; 
    emit appdataChanged(d->appdata);
  }
}
