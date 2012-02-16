#include "device.h"

QPndman::Device::Device(QString const& mount, QString const& device, qint64 const& size, qint64 const& free, qint64 const& available, QObject* parent) : QObject(parent), 
  _mount(mount), _device(device), _size(size), _free(free), _available(available)
{
}

QPndman::Device::Device(Device const& other) : QObject(0), 
  _mount(other._mount), _device(other._device), _size(other._size), _free(other._free), _available(other._available)
{
}

QPndman::Device& QPndman::Device::operator=(Device const& other)
{
  if(&other == this)
    return *this;
  
  _mount = other._mount;
  _device = other._device;
  _size = other._size;
  _free = other._free;
  _available = other._available;
  
  return *this;
}

QString QPndman::Device::getMount() const
{
  return _mount;
}
QString QPndman::Device::getDevice() const
{
  return _device;
}
qint64 QPndman::Device::getSize() const
{
  return _size;
}
qint64 QPndman::Device::getFree() const
{
  return _free;
}
qint64 QPndman::Device::getAvailable() const
{
  return _available;
}

void QPndman::Device::setMount(QString const& mount)
{
  if(mount != _mount) 
  {
    _mount = mount; 
    emit mountChanged(_mount);
  }
}
void QPndman::Device::setDevice(QString const& device)
{
  if(device != _device) 
  {
    _device = device; 
    emit deviceChanged(_device);
  }
}
void QPndman::Device::setSize(qint64 const& size)
{
  if(size != _size) 
  {
    _size = size; 
    emit sizeChanged(_size);
  }
}
void QPndman::Device::setFree(qint64 const& free)
{
  if(free != _free) 
  {
    _free = free; 
    emit freeChanged(_free);
  }
}
void QPndman::Device::setAvailable(qint64 const& available)
{
  if(available != _available) 
  {
    _available = available; 
    emit availableChanged(_available);
  }
}
