#include "handle.h"

QPndman::Handle::Handle() : QObject(0), 
  _handle(), _name(""), _error(""), _force(false), _operation(Handle::Install), _installLocation(Handle::Desktop), _done(false)
{
}

pndman_handle* QPndman::Handle::getPndmanHandle()
{
  return &_handle;
}

void QPndman::Handle::update()
{
  setName(_handle.name);
  setError(_handle.error);
  setForce(_handle.flags & PNDMAN_HANDLE_FORCE);
  
  if(_handle.flags & PNDMAN_HANDLE_INSTALL) setOperation(Handle::Install);
  else if(_handle.flags & PNDMAN_HANDLE_REMOVE) setOperation(Handle::Remove);
  
  if(_handle.flags & PNDMAN_HANDLE_INSTALL_DESKTOP) setInstallLocation(Handle::Desktop);
  else if(_handle.flags & PNDMAN_HANDLE_INSTALL_MENU) setInstallLocation(Handle::Menu);
  else if(_handle.flags & PNDMAN_HANDLE_INSTALL_APPS) setInstallLocation(Handle::DesktopAndMenu);
  
  setDone(_handle.done);
}

QString QPndman::Handle::getName() const
{
  return _name;
}
QString QPndman::Handle::getError() const
{
  return _error;
}
bool QPndman::Handle::getForce() const
{
  return _force;
}
QPndman::Handle::Operation QPndman::Handle::getOperation() const
{
  return _operation;
}
QPndman::Handle::InstallLocation QPndman::Handle::getInstallLocation() const
{
  return _installLocation;
}
bool QPndman::Handle::getDone() const
{
  return _done;
}

void QPndman::Handle::setForce(bool const& force)
{
  if(force != _force) 
  {
    _force = force;
    updateHandleFlags();
    emit forceChanged(_force);
  }
}
void QPndman::Handle::setOperation(Operation const operation)
{
  if(operation != _operation) 
  {
    _operation = operation; 
    updateHandleFlags();
    emit operationChanged(_operation);
  }
}
void QPndman::Handle::setInstallLocation(InstallLocation const installLocation)
{
  if(installLocation != _installLocation) 
  {
    _installLocation = installLocation; 
    updateHandleFlags();
    emit installLocationChanged(_installLocation);
  }
}

void QPndman::Handle::updateHandleFlags()
{
  _handle.flags = 0;
  if(_force) _handle.flags |= PNDMAN_HANDLE_FORCE;
  
  if(_operation == Handle::Install) _handle.flags |= PNDMAN_HANDLE_INSTALL;
  else if(_operation == Handle::Remove) _handle.flags |= PNDMAN_HANDLE_REMOVE;

  if(_installLocation == Handle::Desktop) _handle.flags |= PNDMAN_HANDLE_INSTALL_DESKTOP;
  else if(_installLocation == Handle::Menu) _handle.flags |= PNDMAN_HANDLE_INSTALL_MENU;
  else if(_installLocation == Handle::DesktopAndMenu) _handle.flags |= PNDMAN_HANDLE_INSTALL_APPS;
}

void QPndman::Handle::setName(QString const& name)
{
  if(name != _name) 
  {
    _name = name;
    emit nameChanged(_name);
  }
}
void QPndman::Handle::setError(QString const& error)
{
  if(error != _error) 
  {
    _error = error; 
    emit errorChanged(_error);
  }
}
void QPndman::Handle::setDone(bool const& done)
{
  if(done != _done) 
  {
    _done = done; 
    emit doneChanged(_done);
    if(done)
    {
      emit Handle::done();
    }
  }
}

