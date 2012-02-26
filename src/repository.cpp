#include "repository.h"
#include "util.h"

#include <QDebug>
#include "device.h"

QPndman::LocalRepository::LocalRepository(Context*  c, QObject* parent) : Repository(c, c->getLocalPndmanRepository(), parent ? parent : c) {}

bool QPndman::LocalRepository::hasPackageInstalled(Package package)
{
  foreach(Package installed, d->packages)
  {
    if(installed.getId() == package.getId())
    {
      return true;
    }
  }
  
  return false;
}

void QPndman::LocalRepository::update()
{
  d->context->checkLocalPndmanRepository();
  Repository::update();
}

QPndman::Repository::Repository(Context* c, QString const& url, QObject* parent) : 
  QObject(parent ? parent : c), d()
{
  pndman_repository* repo = c->addPndmanRepository(url);
  if(repo)
  {
    d = QSharedPointer<Data>(new Data(c, repo));
  }
}
QPndman::Repository::Repository(Context*  c, pndman_repository* p, QObject* parent) : QObject(parent), d(new Data(c, p))
{  
}

int QPndman::Repository::Data::nextIdentifier = 1;

QPndman::Repository::Data::Data(Context*  c, pndman_repository* p) : identifier(nextIdentifier++),
  context(c), pndmanRepository(p),
  url(p->url), name(p->name), updates(p->updates), 
  timestamp(QDateTime::fromTime_t(p->timestamp)), version(p->version), 
  packages(makeQList<pndman_package, Package>(p->pnd))
{
}
QPndman::Repository::Data::~Data()
{
  context->removePndmanRepository(pndmanRepository);
}

QPndman::SyncHandle* QPndman::Repository::sync()
{
  SyncHandle* handle = new SyncHandle(this);
  handle->setParent(this);
  connect(handle, SIGNAL(done()), this, SLOT(update()));
  return handle;
}

bool QPndman::Repository::loadFrom(Device* device)
{
  return device->loadRepository(this);
}

void QPndman::Repository::clear()
{
  d->context->clearPndmanRepository(d->pndmanRepository);
  update();
}

pndman_repository* QPndman::Repository::getPndmanRepository() const
{
  return d->pndmanRepository;
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

void QPndman::Repository::update()
{
  setUrl(d->pndmanRepository->url);
  setName(d->pndmanRepository->name);
  setUpdates(d->pndmanRepository->updates);
  setTimestamp(QDateTime::fromTime_t(d->pndmanRepository->timestamp));
  setVersion(d->pndmanRepository->version);
  setPackages(makeQList<pndman_package, Package>(d->pndmanRepository->pnd));
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
