#include "synchandle.h"
#include "repository.h"
#include <QDebug>

QPndman::SyncHandle::SyncHandle(Repository* repository, bool fullSync, QObject* parent) : QObject(parent ? parent : repository),
  handle(), error(""), repository(repository), _done(false), bytesDownloaded(0), bytesToDownload(0)
{
  unsigned int flags = 0;
  if(fullSync) flags |= PNDMAN_SYNC_FULL;
  pndman_sync_request(&handle, flags, repository->getPndmanRepository());
  update();
}

QPndman::SyncHandle::~SyncHandle()
{
  pndman_sync_request_free(&handle);
}

pndman_sync_handle* QPndman::SyncHandle::getPndmanSyncHandle()
{
  return &handle;
}

int QPndman::SyncHandle::sync()
{
  return pndman_sync();
}

QPndman::Repository* QPndman::SyncHandle::getRepository() const
{
  return repository;
}
QString QPndman::SyncHandle::getError() const
{
  return error;
}
bool QPndman::SyncHandle::getDone() const
{
  return _done;
}

qint64 QPndman::SyncHandle::getBytesDownloaded() const
{
  return bytesDownloaded;
}

qint64 QPndman::SyncHandle::getBytesToDownload() const
{
  return bytesToDownload;
}

void QPndman::SyncHandle::update()
{
  setError(handle.error);
  setDone(handle.progress.done);
  setBytesDownloaded(static_cast<qint64>(handle.progress.download));
  setBytesToDownload(static_cast<qint64>(handle.progress.total_to_download));
}


void QPndman::SyncHandle::setError(QString const& newError)
{
  if(error != error)
  {
    error = error;
    emit errorChanged(error);
  }
}
void QPndman::SyncHandle::setDone(bool const& done)
{
  if(_done != done)
  {
    _done = done;
    emit doneChanged(_done);
    if(_done)
    {
      emit SyncHandle::done();
    }
  }
}

void QPndman::SyncHandle::setBytesDownloaded(qint64 const value)
{
  if(value != bytesDownloaded)
  {
    bytesDownloaded = value;
    emit bytesDownloadedChanged(bytesDownloaded);
  }
}

void QPndman::SyncHandle::setBytesToDownload(qint64 const value)
{
  if(value != bytesToDownload)
  {
    bytesToDownload = value;
    emit bytesDownloadedChanged(bytesToDownload);
  }
}
