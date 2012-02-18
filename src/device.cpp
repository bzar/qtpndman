#include "device.h"

QPndman::Device::Device() : QObject(0), d()
{
  
}
QPndman::Device::Device(pndman_device* p) : QObject(0), d(new Data(p))
{
  
}

QPndman::Device::Data::Data(pndman_device* p) : 
  pndmanDevice(p), mount(p->mount), device(p->device), size(p->size), free(p->free), available(p->available), appdata(p->appdata)
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

QString QPndman::Device::getMount() const
{
  return d->mount;
}
QString QPndman::Device::getDevice() const
{
  return d->device;
}
qint64 QPndman::Device::getSize() const
{
  return d->size;
}
qint64 QPndman::Device::getFree() const
{
  return d->free;
}
qint64 QPndman::Device::getAvailable() const
{
  return d->available;
}
QString QPndman::Device::getAppdata() const
{
  return d->appdata;
}

void QPndman::Device::setMount(QString const& mount)
{
  if(mount != d->mount) 
  {
    d->mount = mount; 
    emit mountChanged(d->mount);
  }
}
void QPndman::Device::setDevice(QString const& device)
{
  if(device != d->device) 
  {
    d->device = device; 
    emit deviceChanged(d->device);
  }
}
void QPndman::Device::setSize(qint64 const& size)
{
  if(size != d->size) 
  {
    d->size = size; 
    emit sizeChanged(d->size);
  }
}
void QPndman::Device::setFree(qint64 const& free)
{
  if(free != d->free) 
  {
    d->free = free; 
    emit freeChanged(d->free);
  }
}
void QPndman::Device::setAvailable(qint64 const& available)
{
  if(available != d->available) 
  {
    d->available = available; 
    emit availableChanged(d->available);
  }
}
void QPndman::Device::setAppdata(QString const& appdata)
{
  if(appdata != d->appdata) 
  {
    d->appdata = appdata; 
    emit appdataChanged(d->appdata);
  }
}
