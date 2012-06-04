#include "package.h"
#include "handle.h"
#include "device.h"
#include "util.h"
#include "context.h"


QPndman::Package::Package(Context* context, pndman_package* p, QObject* parent, bool initUpgradeCandidate) : QObject(parent), package(p), context(context),
  path(QString::fromUtf8(p->path)), id(QString::fromUtf8(p->id)), icon(QString::fromUtf8(p->icon)), info(QString::fromUtf8(p->info)), md5(QString::fromUtf8(p->md5)),
  url(QString::fromUtf8(p->url)), vendor(QString::fromUtf8(p->vendor)), mount(QString::fromUtf8(p->mount)),
  size(p->size), modified(QDateTime::fromTime_t(p->modified_time)), rating(p->rating),
  author(new Author(&p->author, this)),
  version(new Version(&p->version, this)),
  applications(makeQListPtr<pndman_application const, Application>(p->app, this)),
  titles(makeQListPtr<pndman_translated const, TranslatedString>(p->title, this)),
  descriptions(makeQListPtr<pndman_translated const, TranslatedString>(p->description, this)),
  categories(makeQListPtr<pndman_category const, Category>(p->category, this)),
  previewPictures(makeQListPtr<pndman_previewpic const, PreviewPicture>(p->previewpic, this)),
    installInstances(), upgradeCandidate(0)
{
  for(pndman_package* x = p->next_installed; x != 0; x = x->next_installed)
  {
    installInstances << new Package(context, x, this);
  }
  if(initUpgradeCandidate && p->update)
  {
    upgradeCandidate = new Package(context, p->update, this, false);
  }
}

pndman_package* QPndman::Package::getPndmanPackage() const
{
  return package;
}

QPndman::InstallHandle* QPndman::Package::install(Device* device, Enum::InstallLocation location, bool force)
{
  return device->install(this, location, force);
}

QPndman::UpgradeHandle* QPndman::Package::upgrade(bool force)
{
  UpgradeHandle* handle = new UpgradeHandle(context, upgradeCandidate, force, this);
  if(!handle->execute())
  {
    delete handle;
    handle = 0;
  }
  return handle;
}

bool QPndman::Package::crawl(bool full)
{
  return context->crawlPndmanPackage(package, full);
}

QString QPndman::Package::getPath() const
{
  return path;
}
QString QPndman::Package::getId() const
{
  return id;
}
QString QPndman::Package::getIcon() const
{
  return icon;
}
QString QPndman::Package::getInfo() const
{
  return info;
}
QString QPndman::Package::getMd5() const
{
  return md5;
}
QString QPndman::Package::getUrl() const
{
  return url;
}
QString QPndman::Package::getVendor() const
{
  return vendor;
}
QString QPndman::Package::getMount() const
{
  return mount;
}
qint64 QPndman::Package::getSize() const
{
  return size;
}
QDateTime QPndman::Package::getModified() const
{
  return modified;
}
int QPndman::Package::getRating() const
{
  return rating;
}
QPndman::Author* QPndman::Package::getAuthor() const
{
  return author;
}
QPndman::Version* QPndman::Package::getVersion() const
{
  return version;
}
QList<QPndman::Application*> QPndman::Package::getApplications() const
{
  return applications;
}
QList<QPndman::TranslatedString*> QPndman::Package::getTitles() const
{
  return titles;
}

QString QPndman::Package::getTitle() const
{
  return titles.size() == 0 ? "" : titles.at(0)->getContent();
}

QList<QPndman::TranslatedString*> QPndman::Package::getDescriptions() const
{
  return descriptions;
}
QString QPndman::Package::getDescription() const
{
  return descriptions.size() == 0 ? "" : descriptions.at(0)->getContent();
}

QList<QPndman::Category*> QPndman::Package::getCategories() const
{
  return categories;
}
QList<QPndman::PreviewPicture*> QPndman::Package::getPreviewPictures() const
{
  return previewPictures;
}
QList<QPndman::Package*> QPndman::Package::getInstallInstances() const
{
  return installInstances;
}

QPndman::Package* QPndman::Package::getUpgradeCandidate() const
{
  return upgradeCandidate;
}

QImage QPndman::Package::getEmbeddedIcon() const
{
  int const MAX_ICON_SIZE = 1024 * 1024;
  QByteArray buf(MAX_ICON_SIZE, '0');

  size_t imageSize = pndman_package_get_embedded_png(package, buf.data(), MAX_ICON_SIZE);

  if(!imageSize)
  {
    return QImage();
  }

  return QImage::fromData(buf);
}
