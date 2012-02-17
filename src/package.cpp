#include "package.h"
#include "util.h"

QPndman::Package::Package(pndman_package const* p) : QObject(0), _pndman_package(p),
  _path(p->path), _id(p->id), _icon(p->icon), _info(p->info), _md5(p->md5), _url(p->url), _vendor(p->vendor), _size(p->size), 
  _modified(QDateTime::fromTime_t(p->modified_time)), _rating(p->rating), 
  _author(&(p->author)), _version(&(p->version)), 
  _applications(), _titles(), _descriptions(), _categories(), _installInstances(), _flags(p->flags)
{
}

QPndman::Package::Package(Package const& other) : QObject(0), _pndman_package(other._pndman_package),
  _path(other._path), _id(other._id), _icon(other._icon), _info(other._info), _md5(other._md5), _url(other._url), _vendor(other._vendor), _size(other._size), 
  _modified(other._modified), _rating(other._rating), _author(other._author), _version(other._version), _applications(other._applications), _titles(other._titles), 
  _descriptions(other._descriptions), _categories(other._categories), _installInstances(other._installInstances), _flags(other._flags)
{
}

QPndman::Package& QPndman::Package::operator=(Package const& other)
{
  if(&other == this)
    return *this;
  
  _pndman_package = other._pndman_package;
  _path = other._path;
  _id = other._id;
  _icon = other._icon;
  _info = other._info;
  _md5 = other._md5;
  _url = other._url;
  _vendor = other._vendor;
  _size = other._size;
  _modified = other._modified;
  _rating = other._rating;
  _author = other._author;
  _version = other._version;
  _applications = other._applications;
  _titles = other._titles;
  _descriptions = other._descriptions;
  _categories = other._categories;
  _installInstances = other._installInstances;
  _flags = other._flags;
  
  return *this;
}

QString QPndman::Package::getPath() const
{
  return _path;
}
QString QPndman::Package::getId() const
{
  return _id;
}
QString QPndman::Package::getIcon() const
{
  return _icon;
}
QString QPndman::Package::getInfo() const
{
  return _info;
}
QString QPndman::Package::getMd5() const
{
  return _md5;
}
QString QPndman::Package::getUrl() const
{
  return _url;
}
QString QPndman::Package::getVendor() const
{
  return _vendor;
}
qint64 QPndman::Package::getSize() const
{
  return _size;
}
QDateTime QPndman::Package::getModified() const
{
  return _modified;
}
int QPndman::Package::getRating() const
{
  return _rating;
}
QPndman::Author QPndman::Package::getAuthor() const
{
  return _author;
}
QPndman::Version QPndman::Package::getVersion() const
{
  return _version;
}
QList< QSharedPointer<QPndman::Application> > QPndman::Package::getApplications()
{
  if(_applications.size() == 0)
  {
    _applications = makeQList<pndman_application, Application>(_pndman_package->app);
  }
  return _applications;
}
QList< QSharedPointer<QPndman::TranslatedString> > QPndman::Package::getTitles()
{
  if(_titles.size() == 0)
  {
    _titles = makeQList<pndman_translated, TranslatedString>(_pndman_package->title);
  }
  return _titles;
}
QList< QSharedPointer<QPndman::TranslatedString> > QPndman::Package::getDescriptions()
{
  if(_descriptions.size() == 0)
  {
    _descriptions = makeQList<pndman_translated, TranslatedString>(_pndman_package->description);
  }
  return _descriptions;
}
QList< QSharedPointer<QPndman::Category> > QPndman::Package::getCategories()
{
  if(_categories.size() == 0)
  {
    _categories = makeQList<pndman_category, Category>(_pndman_package->category);
  }
  return _categories;
}
QList< QSharedPointer<QPndman::Package> > QPndman::Package::getInstallinstances()
{
  if(_installInstances.size() == 0)
  {
    for(pndman_package const* x = _pndman_package->next_installed; x != 0; x = x->next_installed)
    {
      _installInstances << QSharedPointer<Package>(new Package(x));
    }
  }
  return _installInstances;
}

unsigned int QPndman::Package::getFlags() const
{
  return _flags;
}
