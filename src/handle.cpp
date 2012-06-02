#include "handle.h"
#include "device.h"
#include <QDebug>

QPndman::InstallHandle::InstallHandle(QPndman::Context* context, QPndman::Package* package, QPndman::Device* device, Enum::InstallLocation const installLocation, bool force, QObject* parent):
  Handle(context, Enum::Install, package, device, force, parent), installLocation(installLocation)
{
  if(installLocation == Enum::Desktop) handle.flags |= PNDMAN_PACKAGE_INSTALL_DESKTOP;
  else if(installLocation == Enum::Menu) handle.flags |= PNDMAN_PACKAGE_INSTALL_MENU;
  else if(installLocation == Enum::DesktopAndMenu) handle.flags |= PNDMAN_PACKAGE_INSTALL_APPS;
}

bool QPndman::InstallHandle::execute()
{
  if(pndman_package_handle_perform(&handle) == 0)
  {
    emit executed();
    return true;
  }
  else
  {
    setError(handle.error);
    return false;
  }
}

QPndman::UpgradeHandle::UpgradeHandle(QPndman::Context* context, QPndman::Package* package, bool force, QObject* parent):
  Handle(context, Enum::Upgrade, package, 0, force, parent)
{
  handle.device = context->getPndmanDevices();
}

bool QPndman::UpgradeHandle::execute()
{
  if(pndman_package_handle_perform(&handle) == 0)
  {
    emit executed();
    return true;
  }
  else
  {
    setError(handle.error);
    return false;
  }
}

QPndman::RemoveHandle::RemoveHandle(QPndman::Context* context, QPndman::Package* package, QPndman::Device* device, bool force, QObject* parent):
  Handle(context, Enum::Remove, package, device, force, parent)
{
}

bool QPndman::RemoveHandle::execute()
{
  if(!context->commitHandle(&handle))
  {
    setError(handle.error);
    return false;
  }
  
  emit executed();
  _done = true;
  emit done();
  emit doneChanged(true);
  return true;
}

QPndman::Handle::Handle(Context*  context, Enum::Operation operation, Package* package, Device* device, bool force, QObject* parent) : QObject(parent ? parent : device),
  context(context), handle(),
  name("."), _error(""), force(force), package(package),
  device(device), operation(operation), _done(false),
  _cancelled(false), bytesDownloaded(0), bytesToDownload(0)
{
  pndman_package_handle_init(name.toLocal8Bit().data(), &handle);
  handle.device = device ? device->getPndmanDevice() : 0;
  handle.pnd = package->getPndmanPackage();  
  handle.callback = handleCallback;
  handle.user_data = this;
  handle.flags = 0;

  if(force) handle.flags |= PNDMAN_PACKAGE_FORCE;

  if(operation == Enum::Install) handle.flags |= PNDMAN_PACKAGE_INSTALL;
  else if(operation == Enum::Remove) handle.flags |= PNDMAN_PACKAGE_REMOVE;
  else if(operation == Enum::Upgrade) handle.flags |= PNDMAN_PACKAGE_INSTALL; // Upgrade done with install flag

  update();
}

QPndman::Handle::~Handle()
{
  pndman_package_handle_free(&handle);
}

pndman_package_handle *QPndman::Handle::getPndmanHandle()
{
  return &handle;
}

void QPndman::Handle::handleCallback(pndman_curl_code code, pndman_package_handle *handle)
{
  Handle* h = static_cast<Handle*>(handle->user_data);
  h->update();
}

void QPndman::Handle::cancel()
{
  _cancelled = true;
  emit cancelledChanged(true);
  emit cancelled();
}

void QPndman::Handle::update()
{
  if(!_cancelled)
  {
    setError(handle.error);
    setDone(handle.progress.done);
    setBytesDownloaded(static_cast<qint64>(handle.progress.download));
    setBytesToDownload(static_cast<qint64>(handle.progress.total_to_download));
  }
}

QString QPndman::Handle::getName() const
{
  return name;
}
QString QPndman::Handle::getError() const
{
  return _error;
}
bool QPndman::Handle::getForce() const
{
  return force;
}
QPndman::Package* QPndman::Handle::getPackage() const
{
  return package;
}
QPndman::Device* QPndman::Handle::getDevice() const
{
  return device;
}
QPndman::Enum::Operation QPndman::Handle::getOperation() const
{
  return operation;
}
bool QPndman::Handle::getDone() const
{
  return _done;
}

bool QPndman::Handle::getCancelled() const
{
  return _cancelled;
}

qint64 QPndman::Handle::getBytesDownloaded() const
{
  return bytesDownloaded;
}
qint64 QPndman::Handle::getBytesToDownload() const
{
  return bytesToDownload;
}

void QPndman::Handle::setError(QString const& newError)
{
  if(_error != newError)
  {
    _error = newError;
    emit errorChanged(_error);
    emit error(_error);
  }
}
void QPndman::Handle::setDone(bool const& done)
{
  if(_done != done)
  {
    _done = done;
    if(_done)
    {
      if(context->commitHandle(&handle))
      {
        emit Handle::done();
      }
      else
      {
        setError(handle.error);
      }
    }
    emit doneChanged(_done);
  }
}

void QPndman::Handle::setBytesDownloaded(qint64 const value)
{
  if(value != bytesDownloaded)
  {
    if(bytesDownloaded == 0)
    {
      emit downloadStarted();
    }

    bytesDownloaded = value;
    emit bytesDownloadedChanged(bytesDownloaded);

    if(bytesDownloaded == bytesToDownload)
    {
      emit downloadFinished();
    }
  }
}

void QPndman::Handle::setBytesToDownload(qint64 const value)
{
  if(value != bytesToDownload)
  {
    bytesToDownload = value;
    emit bytesToDownloadChanged(bytesToDownload);
  }
}

QPndman::Enum::InstallLocation QPndman::InstallHandle::getInstallLocation() const
{
  return installLocation;
}
