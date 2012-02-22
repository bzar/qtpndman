#include "synchandle.h"
#include "repository.h"
#include <QDebug>

QPndman::SyncHandle::SyncHandle(Repository* repository, bool fullSync) : QObject(repository), d(new Data(repository))
{
  unsigned int flags = 0;
  if(fullSync) flags |= PNDMAN_SYNC_FULL;
  pndman_sync_request(&d->handle, flags, repository->getPndmanRepository());
  update();
}
QPndman::SyncHandle::Data::Data(Repository* repository) : 
  handle(), error(""), repository(repository), done(false), bytesDownloaded(0), bytesToDownload(0)
{
}
QPndman::SyncHandle::Data::~Data()
{
  pndman_sync_request_free(&handle);
}


pndman_sync_handle* QPndman::SyncHandle::getPndmanSyncHandle()
{
  return &d->handle;
}

int QPndman::SyncHandle::sync()
{
  return pndman_sync();
}

QPndman::Repository* QPndman::SyncHandle::getRepository() const
{
  return d->repository;
}
QString QPndman::SyncHandle::getError() const
{
  return d->error;
}
bool QPndman::SyncHandle::getDone() const
{
  return d->done;
}

qint64 QPndman::SyncHandle::getBytesDownloaded() const
{
  return d->bytesDownloaded;
}

qint64 QPndman::SyncHandle::getBytesToDownload() const
{
  return d->bytesToDownload;
}

void QPndman::SyncHandle::update()
{
  setError(d->handle.error);
  setDone(d->handle.progress.done);
  setBytesDownloaded(static_cast<qint64>(d->handle.progress.download));
  setBytesToDownload(static_cast<qint64>(d->handle.progress.total_to_download));
}


void QPndman::SyncHandle::setError(QString const& error)
{
  if(error != d->error) 
  {
    d->error = error; 
    emit errorChanged(d->error);
  }
}
void QPndman::SyncHandle::setDone(bool const& done)
{
  if(done != d->done) 
  {
    d->done = done; 
    emit doneChanged(d->done);
    if(done)
    {
      emit SyncHandle::done();
    }
  }
}

void QPndman::SyncHandle::setBytesDownloaded(qint64 const value)
{
  if(value != d->bytesDownloaded) 
  {
    d->bytesDownloaded = value; 
    emit bytesDownloadedChanged(d->bytesDownloaded);
  }
}

void QPndman::SyncHandle::setBytesToDownload(qint64 const value)
{
  if(value != d->bytesToDownload) 
  {
    d->bytesToDownload = value; 
    emit bytesDownloadedChanged(d->bytesToDownload);
  }
}
