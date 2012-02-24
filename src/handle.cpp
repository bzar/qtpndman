#include "handle.h"
#include "device.h"
#include <QDebug>

namespace
{
  int nextId = 0;
}

QPndman::Handle::Handle(Context*  context, Operation operation, Package package, Device* device, bool force) : QObject(device), 
  d(new Data(context, operation, package, device, force))
{
  pndman_handle_init(d->name.toLocal8Bit().data(), &d->handle);
  d->handle.device = device->getPndmanDevice();
  d->handle.pnd = package.getPndmanPackage();
  updateHandleFlags();
  update();
}

QPndman::Handle::Data::Data(Context*  context, Operation operation, Package package, Device* device, bool force) :
  context(context), handle(), 
  name(QString::number(++nextId)), 
  error(""), force(force), package(package), 
  device(device), operation(operation), installLocation(Desktop), done(false), 
  cancelled(false), bytesDownloaded(0), bytesToDownload(0)
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
  setDone(d->handle.progress.done);
  setBytesDownloaded(static_cast<qint64>(d->handle.progress.download));
  setBytesToDownload(static_cast<qint64>(d->handle.progress.total_to_download));
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

qint64 QPndman::Handle::getBytesDownloaded() const
{
  return d->bytesDownloaded;
}
qint64 QPndman::Handle::getBytesToDownload() const
{
  return d->bytesToDownload;
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
    if(done)
    {
      pndman_handle_commit(&d->handle, d->context->getLocalPndmanRepository());
      emit Handle::done();
    }
    emit doneChanged(d->done);
  }
}

void QPndman::Handle::setBytesDownloaded(qint64 const value)
{
  if(value != d->bytesDownloaded) 
  {
    d->bytesDownloaded = value; 
    emit bytesDownloadedChanged(d->bytesDownloaded);
  }
}

void QPndman::Handle::setBytesToDownload(qint64 const value)
{
  if(value != d->bytesToDownload) 
  {
    d->bytesToDownload = value; 
    emit bytesToDownloadChanged(d->bytesToDownload);
  }
}
