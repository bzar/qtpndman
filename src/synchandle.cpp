#include "synchandle.h"
#include "repository.h"
#include <QDebug>

QPndman::SyncHandle::SyncHandle(Repository* repository, bool fullSync, QObject* parent) : QObject(parent ? parent : repository),
  handle(), error(""), repository(repository), _done(false), bytesDownloaded(0), bytesToDownload(0)
{
  unsigned int flags = 0;
  if(fullSync) flags |= PNDMAN_SYNC_FULL;
  pndman_sync_handle_init(&handle);
  handle.flags = flags;
  handle.repository = repository->getPndmanRepository();
  handle.user_data = this;
  handle.callback = handleCallback;
  repository->getContext()->performSyncHandle(&handle);
  update();
}

QPndman::SyncHandle::~SyncHandle()
{
  repository->getContext()->freeSyncHandle(&handle);
}

pndman_sync_handle* QPndman::SyncHandle::getPndmanSyncHandle()
{
  return &handle;
}

void QPndman::SyncHandle::handleCallback(pndman_curl_code code, pndman_sync_handle *handle)
{
  SyncHandle* h = static_cast<SyncHandle*>(handle->user_data);
  h->update();
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

quint64 QPndman::SyncHandle::getBytesDownloaded() const
{
  return bytesDownloaded;
}

quint64 QPndman::SyncHandle::getBytesToDownload() const
{
  return bytesToDownload;
}

void QPndman::SyncHandle::update()
{
  setError(handle.error);
  setDone(handle.progress.done);
  setBytesDownloaded(static_cast<quint64>(handle.progress.download));
  setBytesToDownload(static_cast<quint64>(handle.progress.total_to_download));
}


void QPndman::SyncHandle::setError(QString const& newError)
{
  if(error != newError)
  {
    error = newError;
    emit errorChanged(error);
  }
}
void QPndman::SyncHandle::setDone(bool const& newDone)
{
  if(_done != newDone)
  {
    _done = newDone;
    emit doneChanged(_done);
    if(_done)
    {
      emit SyncHandle::done();
    }
  }
}

void QPndman::SyncHandle::setBytesDownloaded(quint64 const value)
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

void QPndman::SyncHandle::setBytesToDownload(quint64 const value)
{
  if(value != bytesToDownload)
  {
    bytesToDownload = value;
    emit bytesDownloadedChanged(bytesToDownload);
  }
}
