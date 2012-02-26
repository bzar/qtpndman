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
  path(p->path), id(p->id), icon(p->icon), info(p->info), md5(p->md5), url(p->url), vendor(p->vendor), device(p->device), 
  size(p->size), modified(QDateTime::fromTime_t(p->modified_time)), rating(p->rating), 
  author(&(p->author)), version(&(p->version)), 
  applications(makeQList<pndman_application const, Application>(p->app)), 
  titles(makeQList<pndman_translated const, TranslatedString>(p->title)), 
  descriptions(makeQList<pndman_translated const, TranslatedString>(p->description)), 
  categories(makeQList<pndman_category const, Category>(p->category)), 
  installInstances()
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
QString QPndman::Package::getDevice() const
{
  return isNull() ? "" : d->device;
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
  return isNull() || d->titles.size() == 0 ? "" : d->titles.at(0).getContent();
}

QList<QPndman::TranslatedString> QPndman::Package::getDescriptions() const
{
  return d->descriptions;
}
QString QPndman::Package::getDescription() const
{
  return isNull() || d->descriptions.size() == 0 ? "" : d->descriptions.at(0).getContent();
}

QList<QPndman::Category> QPndman::Package::getCategories() const
{
  return d->categories;
}
QList<QPndman::Package> QPndman::Package::getInstallInstances() const
{
  return d->installInstances;
}

void QPndman::Package::setPath(QString const& path)
{
  if(path != d->path) 
  {
    d->path = path; 
    emit pathChanged(d->path);
  }
}
void QPndman::Package::setId(QString const& id)
{
  if(id != d->id) 
  {
    d->id = id; 
    emit idChanged(d->id);
  }
}
void QPndman::Package::setIcon(QString const& icon)
{
  if(icon != d->icon) 
  {
    d->icon = icon; 
    emit iconChanged(d->icon);
  }
}
void QPndman::Package::setInfo(QString const& info)
{
  if(info != d->info) 
  {
    d->info = info; 
    emit infoChanged(d->info);
  }
}
void QPndman::Package::setMd5(QString const& md5)
{
  if(md5 != d->md5) 
  {
    d->md5 = md5; 
    emit md5Changed(d->md5);
  }
}
void QPndman::Package::setUrl(QString const& url)
{
  if(url != d->url) 
  {
    d->url = url; 
    emit urlChanged(d->url);
  }
}
void QPndman::Package::setVendor(QString const& vendor)
{
  if(vendor != d->vendor) 
  {
    d->vendor = vendor; 
    emit vendorChanged(d->vendor);
  }
}
void QPndman::Package::setDevice(QString const& device)
{
  if(device != d->device) 
  {
    d->device = device; 
    emit deviceChanged(d->device);
  }
}
void QPndman::Package::setSize(qint64 const& size)
{
  if(size != d->size) 
  {
    d->size = size; 
    emit sizeChanged(d->size);
  }
}
void QPndman::Package::setModified(QDateTime const& modified)
{
  if(modified != d->modified) 
  {
    d->modified = modified; 
    emit modifiedChanged(d->modified);
  }
}
void QPndman::Package::setRating(int const& rating)
{
  if(rating != d->rating) 
  {
    d->rating = rating; 
    emit ratingChanged(d->rating);
  }
}
void QPndman::Package::setAuthor(Author const& author)
{
  d->author = author; 
  emit authorChanged(d->author);
}
void QPndman::Package::setVersion(Version const& version)
{
  d->version = version; 
  emit versionChanged(d->version);
}
void QPndman::Package::setApplications(QList<Application> const& applications)
{
  d->applications = applications; 
  emit applicationsChanged(d->applications);
}
void QPndman::Package::setTitles(QList<TranslatedString> const& titles)
{
  d->titles = titles; 
  emit titlesChanged(d->titles);
}
void QPndman::Package::setDescriptions(QList<TranslatedString> const& descriptions)
{
  d->descriptions = descriptions; 
  emit descriptionsChanged(d->descriptions);
}
void QPndman::Package::setCategories(QList<Category> const& categories)
{
  d->categories = categories; 
  emit categoriesChanged(d->categories);
}
void QPndman::Package::setInstallinstances(QList<Package> const& installInstances)
{
  d->installInstances = installInstances; 
  emit installInstancesChanged(d->installInstances);
}
