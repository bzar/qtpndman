#include "repository.h"
#include "util.h"

#include <QDebug>

QPndman::Repository::Repository() : QObject(0), d()
{
  
}
QPndman::Repository::Repository(pndman_repository* p) : QObject(0), d(new Data(p))
{
  
}

int QPndman::Repository::Data::nextIdentifier = 1;

QPndman::Repository::Data::Data(pndman_repository* p) : identifier(nextIdentifier++),
  repository(p), 
  url(p->url), name(p->name), updates(p->updates), 
  timestamp(QDateTime::fromTime_t(p->timestamp)), version(p->version), 
  packages(makeQList<pndman_package, Package>(p->pnd)), exists(p->exist)
{
}

QPndman::Repository::Repository(Repository const& other) : QObject(0), d(other.d)
{
}

QPndman::Repository& QPndman::Repository::operator=(Repository const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

pndman_repository* QPndman::Repository::getPndmanRepository() const
{
  return d->repository;
}

bool QPndman::Repository::isNull() const
{
  return !d;
}

int QPndman::Repository::getIdentifier() const
{
  return isNull() ? 0 : d->identifier;
}

QString QPndman::Repository::getUrl() const
{
  return isNull() ? "" : d->url;
}
QString QPndman::Repository::getName() const
{
  return isNull() ? "" : d->name;
}
QString QPndman::Repository::getUpdates() const
{
  return isNull() ? "" : d->updates;
}
QDateTime QPndman::Repository::getTimestamp() const
{
  return isNull() ? QDateTime() : d->timestamp;
}
QString QPndman::Repository::getVersion() const
{
  return isNull() ? "" : d->version;
}
QList<QPndman::Package> QPndman::Repository::getPackages() const
{
  return isNull() ? QList<Package>() : d->packages;
}
bool QPndman::Repository::getExists() const
{
  return isNull() ? false : d->exists;
}

void QPndman::Repository::update()
{
  setUrl(d->repository->url);
  setName(d->repository->name);
  setUpdates(d->repository->updates);
  setTimestamp(QDateTime::fromTime_t(d->repository->timestamp));
  setVersion(d->repository->version);
  setPackages(makeQList<pndman_package, Package>(d->repository->pnd));
  setExists(d->repository->exist);
}
void QPndman::Repository::setUrl(QString const& url)
{
  if(!isNull() && url != d->url) 
  {
    d->url = url; 
    emit urlChanged(d->url);
  }
}
void QPndman::Repository::setName(QString const& name)
{
  if(!isNull() && name != d->name) 
  {
    d->name = name; 
    emit nameChanged(d->name);
  }
}
void QPndman::Repository::setUpdates(QString const& updates)
{
  if(!isNull() && updates != d->updates) 
  {
    d->updates = updates; 
    emit updatesChanged(d->updates);
  }
}
void QPndman::Repository::setTimestamp(QDateTime const& timestamp)
{
  if(!isNull() && timestamp != d->timestamp) 
  {
    d->timestamp = timestamp; 
    emit timestampChanged(d->timestamp);
  }
}
void QPndman::Repository::setVersion(QString const& version)
{
  if(!isNull() && version != d->version) 
  {
    d->version = version; 
    emit versionChanged(d->version);
  }
}
void QPndman::Repository::setPackages(QList<Package> const& packages)
{
  if(!isNull())
  {
    d->packages = packages; 
    emit packagesChanged(d->packages);
  }
}
void QPndman::Repository::setExists(bool const exists)
{
  if(!isNull() && exists != d->exists) 
  {
    d->exists = exists; 
    emit existsChanged(d->exists);
  }
}
