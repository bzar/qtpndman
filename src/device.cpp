#include "device.h"
#include <QDebug>
#include "repository.h"

QList<QPndman::Device*> QPndman::Device::detectDevices(Context& c, QObject* parent)
{
  QList<Device*> detectedDevices;
  for(pndman_device* dev = c.detectPndmanDevices(); dev != 0; dev = dev->next)
  {
    detectedDevices << new Device(c, dev);
  }
  
  return detectedDevices;
}

QPndman::Device::Device(Context& c, QString const& path, QObject* parent) : QObject(parent ? parent : &c), d()
{
  pndman_device* dev = c.addPndmanDevice(path);
  if(dev)
  {
    d = QSharedPointer<Data>(new Data(c, dev));
  }
}

QPndman::Device::Device(Context& c, pndman_device* p, QObject* parent) : QObject(parent ? parent : &c), d(new Data(c, p))
{
}

int QPndman::Device::Data::nextIdentifier = 1;

QPndman::Device::Data::Data(Context& c, pndman_device* p) : identifier(nextIdentifier++), 
  context(c), pndmanDevice(p), mount(p->mount), device(p->device), 
  size(p->size), free(p->free), available(p->available), appdata(p->appdata)
{
}

QPndman::Device::Data::~Data()
{
  context.removePndmanDevice(pndmanDevice);
}

QPndman::Handle* QPndman::Device::install(Package package, InstallLocation location)
{
  Handle* handle = new Handle(Install, package, this);
  handle->setParent(this);
  handle->setInstallLocation(location);
  handle->execute();
  return handle;
}

QPndman::Handle* QPndman::Device::remove(Package package)
{
  Handle* handle = new Handle(Remove, package, this);
  handle->setParent(this);
  handle->execute();
  return handle;  
}

bool QPndman::Device::crawl()
{
  return d->context.crawlPndmanDevice(d->pndmanDevice);
}

bool QPndman::Device::saveRepositories()
{
  return d->context.saveRepositories(d->pndmanDevice);
}

bool QPndman::Device::loadRepository(Repository* repository)
{
  return d->context.loadRepository(repository->getPndmanRepository(), d->pndmanDevice);
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
