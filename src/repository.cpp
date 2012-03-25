#include "repository.h"
#include "util.h"

#include <QDebug>
#include "device.h"

QPndman::LocalRepository::LocalRepository(Context*  c, QObject* parent) : Repository(c, c->getLocalPndmanRepository(), parent ? parent : c) {}

bool QPndman::LocalRepository::hasPackageInstalled(Package* package)
{
  foreach(Package const* installed, packages)
  {
    if(installed->getId() == package->getId())
    {
      return true;
    }
  }
  
  return false;
}

void QPndman::LocalRepository::update()
{
  context->checkLocalPndmanRepository();
  context->checkUpgrades();
  Repository::update();
}

int QPndman::Repository::nextIdentifier = 1;

QPndman::Repository::Repository(Context* c, QString const& url, QObject* parent) : 
  QObject(parent ? parent : c), identifier(nextIdentifier++), context(c), pndmanRepository(c->addPndmanRepository(url)),
  url(), name(), updates(), timestamp(), version(), packages()
{
  if(pndmanRepository)
  {
    update();
  }
}

QPndman::Repository::~Repository()
{
  context->removePndmanRepository(pndmanRepository);
}

QPndman::Repository::Repository(Context*  c, pndman_repository* p, QObject* parent) :
  QObject(parent ? parent : c), identifier(nextIdentifier++), context(c), pndmanRepository(p),
  url(), name(), updates(), timestamp(), version(), packages()
{
  update();
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
  context->clearPndmanRepository(pndmanRepository);
  update();
}

pndman_repository* QPndman::Repository::getPndmanRepository() const
{
  return pndmanRepository;
}

bool QPndman::Repository::isNull() const
{
  return pndmanRepository == 0;
}

int QPndman::Repository::getIdentifier() const
{
  return identifier;
}

QString QPndman::Repository::getUrl() const
{
  return url;
}
QString QPndman::Repository::getName() const
{
  return name;
}
QString QPndman::Repository::getUpdates() const
{
  return updates;
}
QDateTime QPndman::Repository::getTimestamp() const
{
  return timestamp;
}
QString QPndman::Repository::getVersion() const
{
  return version;
}
QList<QPndman::Package*> QPndman::Repository::getPackages() const
{
  return packages;
}

void QPndman::Repository::update()
{
  setUrl(pndmanRepository->url);
  setName(pndmanRepository->name);
  setUpdates(pndmanRepository->updates);
  setTimestamp(QDateTime::fromTime_t(pndmanRepository->timestamp));
  setVersion(pndmanRepository->version);
  
  QList<Package*> newPackages;
  for(pndman_package* x = pndmanRepository->pnd; x != 0; x = x->next)
  {
    newPackages << new Package(context, x, this);
  }

  foreach(Package* package, packages)
  {
    package->deleteLater();
  }

  setPackages(newPackages);
}

void QPndman::Repository::setUrl(QString const& newUrl)
{
  if(url != newUrl)
  {
    url = newUrl;
    emit urlChanged(url);
  }
}
void QPndman::Repository::setName(QString const& newName)
{
  if(name != newName)
  {
    name = newName;
    emit nameChanged(name);
  }
}
void QPndman::Repository::setUpdates(QString const& newUpdates)
{
  if(updates != newUpdates)
  {
    updates = newUpdates;
    emit updatesChanged(updates);
  }
}
void QPndman::Repository::setTimestamp(QDateTime const& newTimestamp)
{
  if(timestamp != newTimestamp)
  {
    timestamp = newTimestamp;
    emit timestampChanged(timestamp);
  }
}
void QPndman::Repository::setVersion(QString const& newVersion)
{
  if(version != newVersion)
  {
    version = newVersion;
    emit versionChanged(version);
  }
}
void QPndman::Repository::setPackages(QList<Package*> const& newPackages)
{
  foreach(Package const* package, packages)
  {
    delete package;
  }
  packages = newPackages;
  emit packagesChanged(packages);
}
