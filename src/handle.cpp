#include "handle.h"
#include "device.h"

QPndman::Handle::Handle(Operation operation, Package package, Device* device) : QObject(0), 
  d(new Data(operation, package, device))
{
  pndman_handle_init(QString::number(QDateTime::currentMSecsSinceEpoch()).toLocal8Bit().data(), 
                     &d->handle);
  updateHandleFlags();
}

QPndman::Handle::Data::Data(Operation operation, Package package, Device* device) :
  handle(), name(""), error(""), force(false), package(package), device(device), 
  operation(operation), installLocation(Desktop), done(false), 
  cancelled(false)
{
}
QPndman::Handle::Data::~Data()
{
  pndman_handle_free(&handle);
}


pndman_handle* QPndman::Handle::getPndmanHandle()
{
  return &(d->handle);
}

int QPndman::Handle::download()
{
  return pndman_download();
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
  setError(d->handle.error);
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
QPndman::Device* QPndman::Handle::getDevice() const
{
  return d->device;
}
QPndman::Operation QPndman::Handle::getOperation() const
{
  return d->operation;
}
QPndman::InstallLocation QPndman::Handle::getInstallLocation() const
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
  
  if(d->operation == Install) d->handle.flags |= PNDMAN_HANDLE_INSTALL;
  else if(d->operation == Remove) d->handle.flags |= PNDMAN_HANDLE_REMOVE;

  if(d->installLocation == Desktop) d->handle.flags |= PNDMAN_HANDLE_INSTALL_DESKTOP;
  else if(d->installLocation == Menu) d->handle.flags |= PNDMAN_HANDLE_INSTALL_MENU;
  else if(d->installLocation == DesktopAndMenu) d->handle.flags |= PNDMAN_HANDLE_INSTALL_APPS;
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
