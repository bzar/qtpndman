#include "package.h"
#include "handle.h"
#include "device.h"
#include "util.h"

QPndman::Package::Package() : QObject(0), d()
{
  
}
QPndman::Package::Package(pndman_package* p) : QObject(0), d(new Data(p))
{
  
}
QPndman::Package::Data::Data(pndman_package* p) : package(p),
  path(p->path), id(p->id), icon(p->icon), info(p->info), md5(p->md5), url(p->url), vendor(p->vendor), 
  size(p->size), modified(QDateTime::fromTime_t(p->modified_time)), rating(p->rating), 
  author(&(p->author)), version(&(p->version)), 
  applications(makeQList<pndman_application const, Application>(p->app)), 
  titles(makeQList<pndman_translated const, TranslatedString>(p->title)), 
  descriptions(makeQList<pndman_translated const, TranslatedString>(p->description)), 
  categories(makeQList<pndman_category const, Category>(p->category)), 
  installInstances(), flags(p->flags)
{
  for(pndman_package* x = p->next_installed; x != 0; x = x->next_installed)
  {
    installInstances << Package(x);
  }
}

QPndman::Package::Package(Package const& other) : QObject(0), d(other.d)
{
}

QPndman::Package& QPndman::Package::operator=(Package const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

pndman_package* QPndman::Package::getPndmanPackage() const
{
  return isNull() ? 0 : d->package;
}

bool QPndman::Package::isNull() const
{
  return !d;
}

QPndman::Handle* QPndman::Package::install(Device* device, InstallLocation location, bool force)
{
  return device->install(*this, location, force);
}

QString QPndman::Package::getPath() const
{
  return isNull() ? "" : d->path;
}
QString QPndman::Package::getId() const
{
  return isNull() ? "" : d->id;
}
QString QPndman::Package::getIcon() const
{
  return isNull() ? "" : d->icon;
}
QString QPndman::Package::getInfo() const
{
  return isNull() ? "" : d->info;
}
QString QPndman::Package::getMd5() const
{
  return isNull() ? "" : d->md5;
}
QString QPndman::Package::getUrl() const
{
  return isNull() ? "" : d->url;
}
QString QPndman::Package::getVendor() const
{
  return isNull() ? "" : d->vendor;
}
qint64 QPndman::Package::getSize() const
{
  return isNull() ? 0 : d->size;
}
QDateTime QPndman::Package::getModified() const
{
  return isNull() ? QDateTime() : d->modified;
}
int QPndman::Package::getRating() const
{
  return isNull() ? 0 : d->rating;
}
QPndman::Author QPndman::Package::getAuthor() const
{
  return d->author;
}
QPndman::Version QPndman::Package::getVersion() const
{
  return d->version;
}
QList<QPndman::Application> QPndman::Package::getApplications() const
{
  return d->applications;
}
QList<QPndman::TranslatedString> QPndman::Package::getTitles() const
{
  return d->titles;
}

QString QPndman::Package::getTitle() const
{
  return d->titles.at(0).getContent();
}

QList<QPndman::TranslatedString> QPndman::Package::getDescriptions() const
{
  return d->descriptions;
}
QString QPndman::Package::getDescription() const
{
  return d->descriptions.at(0).getContent();
}

QList<QPndman::Category> QPndman::Package::getCategories() const
{
  return d->categories;
}
QList<QPndman::Package> QPndman::Package::getInstallinstances() const
{
  if(d->installInstances.size() == 0)
  {
  }
  return d->installInstances;
}

unsigned int QPndman::Package::getFlags() const
{
  return d->flags;
}
