#include "synchandle.h"
#include <QDebug>

QPndman::SyncHandle::SyncHandle() : QObject(0), d(new Data)
{
}
QPndman::SyncHandle::Data::Data() : 
  handle(), error(""), repository(), done(false)
{
}
QPndman::SyncHandle::Data::~Data()
{
  pndman_sync_request_free(&handle);
}
QPndman::SyncHandle::SyncHandle(SyncHandle const& other) : QObject(0), d(other.d)
{
}
QPndman::SyncHandle& QPndman::SyncHandle::operator=(SyncHandle const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

pndman_sync_handle* QPndman::SyncHandle::getPndmanSyncHandle()
{
  return &d->handle;
}

void QPndman::SyncHandle::update()
{
  setError(d->handle.error);
  setDone(d->handle.done);
}

QPndman::Repository QPndman::SyncHandle::getRepository() const
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

void QPndman::SyncHandle::setRepository(Repository repository)
{
  d->repository = repository;
  d->handle.repository = d->repository.getPndmanRepository();
  emit repositoryChanged(d->repository);
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
      d->repository.update();
      emit SyncHandle::done();
    }
  }
}

