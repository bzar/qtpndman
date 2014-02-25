#include "device.h"
#include <QDebug>
#include "repository.h"

QList<QPndman::Device*> QPndman::Device::detectDevices(Context*  c, QObject* parent)
{
  QList<Device*> detectedDevices;
  for(pndman_device* dev = c->detectPndmanDevices(); dev != 0; dev = dev->next)
  {
    detectedDevices << new Device(c, dev, parent);
  }
  
  return detectedDevices;
}

int QPndman::Device::nextIdentifier = 1;

QPndman::Device::Device(Context*  c, QString const& path, QObject* parent) : QObject(parent ? parent : c),
  identifier(nextIdentifier++), context(c), pndmanDevice(c->addPndmanDevice(path)),
  mount(), size(0), free(0), available(0), appdata()
{
  if(pndmanDevice)
  {
    mount = pndmanDevice->mount;
    size = pndmanDevice->size;
    free = pndmanDevice->free;
    available = pndmanDevice->available;
    appdata = pndmanDevice->appdata;
  }
}

QPndman::Device::Device(Context*  c, pndman_device* p, QObject* parent) : QObject(parent ? parent : c), identifier(nextIdentifier++),
  context(c), pndmanDevice(p), mount(p->mount),
  size(p->size), free(p->free), available(p->available), appdata(p->appdata)
{
}

QPndman::Device::~Device()
{
  context->removePndmanDevice(pndmanDevice);
}

QPndman::InstallHandle* QPndman::Device::install(Package* package, Enum::InstallLocation location, bool force)
{
  InstallHandle* handle = new InstallHandle(context, package, this, location, force);
  handle->setParent(this);
  if(!handle->execute())
  {
    delete handle;
    return 0;
  }
  return handle;
}

bool QPndman::Device::remove(Package* package)
{
  RemoveHandle* handle = new RemoveHandle(context, package, this);
  bool result = handle->execute();
  delete handle;

  return result;
}

bool QPndman::Device::crawl(bool full)
{
  return context->crawlPndmanDevice(pndmanDevice, full) != 0;
}

bool QPndman::Device::saveRepositories()
{
  return context->saveRepositories(pndmanDevice);
}

bool QPndman::Device::loadRepository(Repository* repository, bool autoUpdate)
{
  if(!context->loadRepository(repository->getPndmanRepository(), pndmanDevice))
  {
    return false;
  }
  
  if(autoUpdate)
  {
    repository->update();
  }
  return true;
}

pndman_device* QPndman::Device::getPndmanDevice() const
{
  return pndmanDevice;
}

bool QPndman::Device::isNull() const
{
  return pndmanDevice == 0;
}

int QPndman::Device::getIdentifier() const
{
  return identifier;
}

QString QPndman::Device::getMount() const
{
  return mount;
}
qint64 QPndman::Device::getSize() const
{
  return size;
}
qint64 QPndman::Device::getFree() const
{
  return free;
}
qint64 QPndman::Device::getAvailable() const
{
  return available;
}
QString QPndman::Device::getAppdata() const
{
  return appdata;
}

void QPndman::Device::update()
{
  pndman_device_update(pndmanDevice);
  setFree(pndmanDevice->free);
  setAvailable(pndmanDevice->available);
}

void QPndman::Device::setFree(qint64 const& newFree)
{
  if(free != newFree)
  {
    free = newFree;
    emit freeChanged(free);
  }
}
void QPndman::Device::setAvailable(qint64 const& newAvailable)
{
  if(available != newAvailable)
  {
    available = newAvailable;
    emit availableChanged(available);
  }
}
