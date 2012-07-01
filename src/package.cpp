#include "package.h"
#include "handle.h"
#include "device.h"
#include "util.h"
#include "context.h"
#include "repository.h"

#include <QDebug>

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

bool QPndman::Package::addComment(const QString &comment)
{
  Repository* repository = qobject_cast<Repository*>(parent());
  if(repository)
  {
    return pndman_api_comment_pnd(this, package, repository->getPndmanRepository(), comment.toUtf8().constData(), addCommentCallback) == 0;
  }

  qDebug() << "QPndman::Package parent not a QPndman::Repository!";
  return false;
}

bool QPndman::Package::deleteComment(QPndman::Comment* comment)
{
  Repository* repository = qobject_cast<Repository*>(parent());

  if(!repository || !comments.contains(comment) ||
     pndman_api_comment_pnd_delete(this, package, comment->getTimestamp().toTime_t(),
                                   repository->getPndmanRepository(), deleteCommentCallback) != 0)
  {
    return false;
  }

  comments.removeOne(comment);
  comment->deleteLater();
  emit commentsChanged();
  return true;
}

void QPndman::Package::reloadComments()
{
  Repository* repository = qobject_cast<Repository*>(parent());
  if(repository)
  {
    foreach(Comment* comment, comments)
    {
      comment->deleteLater();
    }

    comments.clear();
    emit commentsChanged();

    pndman_api_comment_pnd_pull(this, package, repository->getPndmanRepository(), reloadCommentsCallback);
  }
  else
  {
    qDebug() << "QPndman::Package parent not a QPndman::Repository!";
  }
}

bool QPndman::Package::rate(const int rating)
{
  Repository* repository = qobject_cast<Repository*>(parent());
  if(!repository)
  {
    return false;
  }

  return pndman_api_rate_pnd(this, package, repository->getPndmanRepository(), rating, rateCallback) == 0;
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

QList<QPndman::Comment *> QPndman::Package::getComments() const
{
  return comments;
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

void QPndman::Package::addCommentCallback(pndman_curl_code code, const char *info, void *user_data)
{
  Q_UNUSED(info)

  Package* package = static_cast<Package*>(user_data);
  if(code == PNDMAN_CURL_DONE)
  {
    emit package->addCommentDone();
  }
  else if(code == PNDMAN_CURL_FAIL)
  {
    emit package->addCommentFail();
  }
}

void QPndman::Package::reloadCommentsCallback(pndman_curl_code code, pndman_api_comment_packet *packet)
{
  if(code != PNDMAN_CURL_FAIL)
  {
    Package* package = static_cast<Package*>(packet->user_data);
    package->comments.append(new Comment(packet, package));
    emit package->commentsChanged();
  }
}

void QPndman::Package::deleteCommentCallback(pndman_curl_code code, const char *info, void *user_data)
{

}

void QPndman::Package::rateCallback(pndman_curl_code code, const char *info, void *user_data)
{
  Q_UNUSED(info)

  if(code == PNDMAN_CURL_DONE)
  {
    Package* package = static_cast<Package*>(user_data);
    emit package->ratingChanged();
  }
}
