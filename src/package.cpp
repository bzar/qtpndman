#include "package.h"
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
  applications(), titles(), descriptions(), categories(), installInstances(), flags(p->flags)
{
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
  return d->package;
}

bool QPndman::Package::isNull() const
{
  return !d;
}

QString QPndman::Package::getPath() const
{
  return d->path;
}
QString QPndman::Package::getId() const
{
  return d->id;
}
QString QPndman::Package::getIcon() const
{
  return d->icon;
}
QString QPndman::Package::getInfo() const
{
  return d->info;
}
QString QPndman::Package::getMd5() const
{
  return d->md5;
}
QString QPndman::Package::getUrl() const
{
  return d->url;
}
QString QPndman::Package::getVendor() const
{
  return d->vendor;
}
qint64 QPndman::Package::getSize() const
{
  return d->size;
}
QDateTime QPndman::Package::getModified() const
{
  return d->modified;
}
int QPndman::Package::getRating() const
{
  return d->rating;
}
QPndman::Author QPndman::Package::getAuthor() const
{
  return d->author;
}
QPndman::Version QPndman::Package::getVersion() const
{
  return d->version;
}
QList<QPndman::Application> QPndman::Package::getApplications()
{
  if(d->applications.size() == 0)
  {
    d->applications = makeQList<pndman_application const, Application>(d->package->app);
  }
  return d->applications;
}
QList<QPndman::TranslatedString> QPndman::Package::getTitles()
{
  if(d->titles.size() == 0)
  {
    d->titles = makeQList<pndman_translated const, TranslatedString>(d->package->title);
  }
  return d->titles;
}

QString QPndman::Package::getTitle()
{
  getTitles();
  if(d->titles.size() == 0)
  {
    return "";
  }
  
  return d->titles.at(0).getContent();
}

QList<QPndman::TranslatedString> QPndman::Package::getDescriptions()
{
  if(d->descriptions.size() == 0)
  {
    d->descriptions = makeQList<pndman_translated const, TranslatedString>(d->package->description);
  }
  return d->descriptions;
}
QString QPndman::Package::getDescription()
{
  getDescriptions();
  if(d->descriptions.size() == 0)
  {
    return "";
  }
  
  return d->descriptions.at(0).getContent();
}

QList<QPndman::Category> QPndman::Package::getCategories()
{
  if(d->categories.size() == 0)
  {
    d->categories = makeQList<pndman_category const, Category>(d->package->category);
  }
  return d->categories;
}
QList<QPndman::Package> QPndman::Package::getInstallinstances()
{
  if(d->installInstances.size() == 0)
  {
    for(pndman_package* x = d->package->next_installed; x != 0; x = x->next_installed)
    {
      d->installInstances << Package(x);
    }
  }
  return d->installInstances;
}

unsigned int QPndman::Package::getFlags() const
{
  return d->flags;
}
