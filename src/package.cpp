#include "package.h"
#include "util.h"

QPndman::Package::Package(QString const& path, QString const& id, QString const& icon, QString const& info, QString const& md5, QString const& url, QString const& vendor, qint64 const& size, QDateTime const& modified, int const& rating, Author const& author, Version const& version, QList< QSharedPointer<Application> > const& applications, QList< QSharedPointer<TranslatedString> > const& titles, QList< QSharedPointer<TranslatedString> > const& descriptions, QList< QSharedPointer<Category> > const& categories, unsigned int const& flags, QList< QSharedPointer<Package> > const& installInstances, QObject* parent) : QObject(parent), 
  _path(path), _id(id), _icon(icon), _info(info), _md5(md5), _url(url), _vendor(vendor), _size(size), _modified(modified), _rating(rating), _author(author), _version(version), _applications(applications), _titles(titles), _descriptions(descriptions), _categories(categories), _flags(flags), _installInstances(installInstances)
{
}


QPndman::Package::Package(pndman_package const* p) : QObject(0), 
  _path(p->path), _id(p->id), _icon(p->icon), _info(p->info), _md5(p->md5), _url(p->url), _vendor(p->vendor), _size(p->size), _modified(QDateTime::fromTime_t(p->modified_time)), _rating(p->rating), 
  _author(&(p->author)), _version(&(p->version)), 
  _applications(makeQList<pndman_application, Application>(p->app)), 
  _titles(makeQList<pndman_translated, TranslatedString>(p->title)), 
  _descriptions(makeQList<pndman_translated, TranslatedString>(p->description)), 
  _categories(makeQList<pndman_category, Category>(p->category)), _flags(p->flags), 
  _installInstances(/*makeQList<pndman_package, Package>(p->next_installed)*/)
{
}

QPndman::Package::Package(Package const& other) : QObject(0), 
  _path(other._path), _id(other._id), _icon(other._icon), _info(other._info), _md5(other._md5), _url(other._url), _vendor(other._vendor), _size(other._size), 
  _modified(other._modified), _rating(other._rating), _author(other._author), _version(other._version), _applications(other._applications), _titles(other._titles), 
  _descriptions(other._descriptions), _categories(other._categories), _flags(other._flags), _installInstances(other._installInstances)
{
}

QPndman::Package& QPndman::Package::operator=(Package const& other)
{
  if(&other == this)
    return *this;
  
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
  _flags = other._flags;
  _installInstances = other._installInstances;
  
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
QList< QSharedPointer<QPndman::Application> > QPndman::Package::getApplications() const
{
  return _applications;
}
QList< QSharedPointer<QPndman::TranslatedString> > QPndman::Package::getTitles() const
{
  return _titles;
}
QList< QSharedPointer<QPndman::TranslatedString> > QPndman::Package::getDescriptions() const
{
  return _descriptions;
}
QList< QSharedPointer<QPndman::Category> > QPndman::Package::getCategories() const
{
  return _categories;
}
unsigned int QPndman::Package::getFlags() const
{
  return _flags;
}
QList< QSharedPointer<QPndman::Package> > QPndman::Package::getInstallinstances() const
{
  return _installInstances;
}

void QPndman::Package::setPath(QString const& path)
{
  if(path != _path) 
  {
    _path = path; 
    emit pathChanged(_path);
  }
}
void QPndman::Package::setId(QString const& id)
{
  if(id != _id) 
  {
    _id = id; 
    emit idChanged(_id);
  }
}
void QPndman::Package::setIcon(QString const& icon)
{
  _icon = icon; 
  emit iconChanged(_icon);
}
void QPndman::Package::setInfo(QString const& info)
{
  _info = info; 
  emit infoChanged(_info);
}
void QPndman::Package::setMd5(QString const& md5)
{
  if(md5 != _md5) 
  {
    _md5 = md5; 
    emit md5Changed(_md5);
  }
}
void QPndman::Package::setUrl(QString const& url)
{
  if(url != _url) 
  {
    _url = url; 
    emit urlChanged(_url);
  }
}
void QPndman::Package::setVendor(QString const& vendor)
{
  if(vendor != _vendor) 
  {
    _vendor = vendor; 
    emit vendorChanged(_vendor);
  }
}
void QPndman::Package::setSize(qint64 const& size)
{
  if(size != _size) 
  {
    _size = size; 
    emit sizeChanged(_size);
  }
}
void QPndman::Package::setModified(QDateTime const& modified)
{
  if(modified != _modified) 
  {
    _modified = modified; 
    emit modifiedChanged(_modified);
  }
}
void QPndman::Package::setRating(int const& rating)
{
  if(rating != _rating) 
  {
    _rating = rating; 
    emit ratingChanged(_rating);
  }
}
void QPndman::Package::setAuthor(Author const& author)
{
  _author = author; 
  emit authorChanged(_author);
}
void QPndman::Package::setVersion(Version const& version)
{
  _version = version; 
  emit versionChanged(_version);
}
void QPndman::Package::setApplications(QList< QSharedPointer<Application> > const& applications)
{
  _applications = applications; 
  emit applicationsChanged(_applications);
}
void QPndman::Package::setTitles(QList< QSharedPointer<TranslatedString> > const& titles)
{
  _titles = titles; 
  emit titlesChanged(_titles);
}
void QPndman::Package::setDescriptions(QList< QSharedPointer<TranslatedString> > const& descriptions)
{
  _descriptions = descriptions; 
  emit descriptionsChanged(_descriptions);
}
void QPndman::Package::setCategories(QList< QSharedPointer<Category> > const& categories)
{
  _categories = categories; 
  emit categoriesChanged(_categories);
}
void QPndman::Package::setFlags(unsigned int const& flags)
{
  if(flags != _flags) 
  {
    _flags = flags; 
    emit flagsChanged(_flags);
  }
}
void QPndman::Package::setInstallinstances(QList< QSharedPointer<Package> > const& installInstances)
{
  _installInstances = installInstances; 
  emit installInstancesChanged(_installInstances);
}
