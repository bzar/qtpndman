#include "handle.h"

QPndman::Handle::Handle() : QObject(0), d(new Data())
{
}
QPndman::Handle::Data::Data() :
  handle(), name(""), error(""), force(false), package(), device(), 
  operation(Handle::Install), installLocation(Handle::Desktop), done(false), 
  cancelled(false)
{
}

QPndman::Handle::Handle(Handle const& other) : QObject(0), d(other.d)
{
}
QPndman::Handle& QPndman::Handle::operator=(Handle const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}
pndman_handle* QPndman::Handle::getPndmanHandle()
{
  return &(d->handle);
}

bool QPndman::Handle::execute()
{
  if(pndman_handle_perform(&d->handle) == 0)
  {
    emit executed();
    return true;
  }
  else
  {
    emit error(d->error);
    return false;
  }
}

bool QPndman::Handle::cancel()
{
  if(pndman_handle_free(&d->handle) == 0)
  {
    d->cancelled = true;
    emit cancelledChanged(true);
    emit cancelled();
    return true;
  }
  else
  {
    emit error(d->error);
    return false;      
  }
}

void QPndman::Handle::update()
{
  setName(d->handle.name);
  setError(d->handle.error);
  setForce(d->handle.flags & PNDMAN_HANDLE_FORCE);
  
  if(d->handle.flags & PNDMAN_HANDLE_INSTALL) setOperation(Handle::Install);
  else if(d->handle.flags & PNDMAN_HANDLE_REMOVE) setOperation(Handle::Remove);
  
  if(d->handle.flags & PNDMAN_HANDLE_INSTALL_DESKTOP) setInstallLocation(Handle::Desktop);
  else if(d->handle.flags & PNDMAN_HANDLE_INSTALL_MENU) setInstallLocation(Handle::Menu);
  else if(d->handle.flags & PNDMAN_HANDLE_INSTALL_APPS) setInstallLocation(Handle::DesktopAndMenu);
  
  setDone(d->handle.done);
}

QString QPndman::Handle::getName() const
{
  return d->name;
}
QString QPndman::Handle::getError() const
{
  return d->error;
}
bool QPndman::Handle::getForce() const
{
  return d->force;
}
QPndman::Package QPndman::Handle::getPackage() const
{
  return d->package;
}
QPndman::Device QPndman::Handle::getDevice() const
{
  return d->device;
}
QPndman::Handle::Operation QPndman::Handle::getOperation() const
{
  return d->operation;
}
QPndman::Handle::InstallLocation QPndman::Handle::getInstallLocation() const
{
  return d->installLocation;
}
bool QPndman::Handle::getDone() const
{
  return d->done;
}

bool QPndman::Handle::getCancelled() const
{
  return d->cancelled;
}


void QPndman::Handle::setForce(bool const& force)
{
  if(force != d->force) 
  {
    d->force = force;
    updateHandleFlags();
    emit forceChanged(d->force);
  }
}
void QPndman::Handle::setPackage(Package package)
{
  if(package.getMd5() != d->package.getMd5()) 
  {
    d->package = package;
    d->handle.pnd = d->package.getPndmanPackage();
    emit packageChanged(d->package);
  }
}
void QPndman::Handle::setDevice(Device device)
{
  if(device.getMount() != d->device.getMount()) 
  {
    d->device = device;
    emit deviceChanged(d->device);
    d->handle.device = d->device.getPndmanDevice();
  }
}

void QPndman::Handle::setOperation(Operation const operation)
{
  if(operation != d->operation) 
  {
    d->operation = operation; 
    updateHandleFlags();
    emit operationChanged(d->operation);
  }
}
void QPndman::Handle::setInstallLocation(InstallLocation const installLocation)
{
  if(installLocation != d->installLocation) 
  {
    d->installLocation = installLocation; 
    updateHandleFlags();
    emit installLocationChanged(d->installLocation);
  }
}

void QPndman::Handle::updateHandleFlags()
{
  d->handle.flags = 0;
  if(d->force) d->handle.flags |= PNDMAN_HANDLE_FORCE;
  
  if(d->operation == Handle::Install) d->handle.flags |= PNDMAN_HANDLE_INSTALL;
  else if(d->operation == Handle::Remove) d->handle.flags |= PNDMAN_HANDLE_REMOVE;

  if(d->installLocation == Handle::Desktop) d->handle.flags |= PNDMAN_HANDLE_INSTALL_DESKTOP;
  else if(d->installLocation == Handle::Menu) d->handle.flags |= PNDMAN_HANDLE_INSTALL_MENU;
  else if(d->installLocation == Handle::DesktopAndMenu) d->handle.flags |= PNDMAN_HANDLE_INSTALL_APPS;
}

void QPndman::Handle::setName(QString const& name)
{
  if(name != d->name) 
  {
    d->name = name;
    emit nameChanged(d->name);
  }
}
void QPndman::Handle::setError(QString const& error)
{
  if(error != d->error) 
  {
    d->error = error; 
    emit errorChanged(d->error);
  }
}
void QPndman::Handle::setDone(bool const& done)
{
  if(done != d->done) 
  {
    d->done = done; 
    emit doneChanged(d->done);
    if(done)
    {
      emit Handle::done();
    }
  }
}
