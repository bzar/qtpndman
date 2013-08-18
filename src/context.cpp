#include "context.h"
#include "util.h"
#include "package.h"
#include "comment.h"


QPndman::Context::Context(QObject* parent) : QObject(parent),
  localPndmanRepository(0), pndmanRepositories(0), pndmanDevices(0), mutex()
{
  setColor(0);
  setLoggingVerbosity(1);
  localPndmanRepository = pndman_repository_init();
  pndmanRepositories = localPndmanRepository;
}

QPndman::Context::~Context()
{
  pndman_repository_free_all(pndmanRepositories);
  pndman_device_free_all(pndmanDevices);
  pndmanRepositories = 0;
  pndmanDevices = 0;
  localPndmanRepository = 0;
}

pndman_repository* QPndman::Context::addPndmanRepository(QString const& url)
{
  return pndman_repository_add(url.toLocal8Bit().data(), pndmanRepositories);
}

void QPndman::Context::removePndmanRepository(pndman_repository* repository)
{
  for(pndman_repository* r = pndmanRepositories; r; r = r->next)
  {
    if(r == repository)
    {
      pndmanRepositories = pndman_repository_free(repository);
      break;
    }
  }
}

pndman_repository* QPndman::Context::getPndmanRepositories()
{
  return pndmanRepositories;
}

pndman_repository* QPndman::Context::getLastPndmanRepository()
{
  return getLast(pndmanRepositories);
}

pndman_repository* QPndman::Context::getLocalPndmanRepository()
{
  return localPndmanRepository;
}

void QPndman::Context::clearPndmanRepository(pndman_repository* repository)
{
  pndman_repository_clear(repository);
}

void QPndman::Context::checkLocalPndmanRepository()
{
  pndman_repository_check_local(localPndmanRepository);
}

void QPndman::Context::setRepositoryCredentials(pndman_repository *repository, const QString &user, const QString &key, bool const store)
{
  pndman_repository_set_credentials(repository, user.toUtf8().constData(), key.toUtf8().constData(), store);
}


pndman_device* QPndman::Context::addPndmanDevice(QString const& path)
{
  pndman_device* device = pndman_device_add(path.toLocal8Bit().data(), pndmanDevices);
  if(!pndmanDevices)
  {
    pndmanDevices = device;
  }

  return device;
}

void QPndman::Context::removePndmanDevice(pndman_device* device)
{
  for(pndman_device* dev = pndmanDevices; dev; dev = dev->next)
  {
    if(dev == device)
    {
      pndmanDevices = pndman_device_free(device);
      break;
    }
  }
}

pndman_device* QPndman::Context::getPndmanDevices()
{
  return pndmanDevices;
}

pndman_device* QPndman::Context::getLastPndmanDevice()
{
  return getLast(pndmanDevices);
}

pndman_device* QPndman::Context::detectPndmanDevices()
{
  pndman_device* detected = pndman_device_detect(pndmanDevices);
  if(!pndmanDevices)
  {
    pndmanDevices = detected;
  }
  return detected;
}

int QPndman::Context::crawlPndmanDevice(pndman_device* device, bool full)
{
  int packages = pndman_package_crawl(full ? 1 : 0, device, localPndmanRepository);
  emit crawlDone();
  return packages;
}

int QPndman::Context::crawlAllPndmanDevices(bool full)
{
  int packages = 0;
  for(pndman_device* device = pndmanDevices; device; device = device->next)
  {
    packages += pndman_package_crawl(full ? 1 : 0, device, localPndmanRepository);
  }
  emit crawlDone();
  return packages;
}

bool QPndman::Context::crawlPndmanPackage(pndman_package *package, bool full)
{
  bool success = pndman_package_crawl_single_package(full ? 1 : 0, package) == 0;
  emit crawlDone(package);
  return success;
}

bool QPndman::Context::crawlPndmanPackageById(const QString& packageId, bool full)
{
  pndman_package* package;
  for(package = localPndmanRepository->pnd; package != 0; package = package->next)
  {
    if(packageId == package->id)
    {
      break;
    }
  }

  if(package == 0)
  {
    return false;
  }

  bool success = pndman_package_crawl_single_package(full ? 1 : 0, package) == 0;
  emit crawlDone(package);
  return success;
}

bool QPndman::Context::saveRepositories(pndman_device* device)
{
  return pndman_repository_commit_all(pndmanRepositories, device) == 0;
}

bool QPndman::Context::loadRepository(pndman_repository* repository, pndman_device* device)
{
  return pndman_device_read_repository(repository, device) == 0;
}

bool QPndman::Context::performHandle(pndman_package_handle *handle)
{
  mutex.lock();
  bool result = pndman_package_handle_perform(handle) == 0;
  mutex.unlock();
  return result;
}

bool QPndman::Context::commitHandle(pndman_package_handle *handle)
{
  return pndman_package_handle_commit(handle, localPndmanRepository) == 0;
}

void QPndman::Context::freeHandle(pndman_package_handle *handle)
{
  mutex.lock();
  pndman_package_handle_free(handle);
  mutex.unlock();
}

bool QPndman::Context::performSyncHandle(pndman_sync_handle *handle)
{
  mutex.lock();
  bool result = pndman_sync_handle_perform(handle) == 0;
  mutex.unlock();
  return result;
}

void QPndman::Context::freeSyncHandle(pndman_sync_handle *handle)
{
  mutex.lock();
  pndman_sync_handle_free(handle);
  mutex.unlock();
}

bool QPndman::Context::addComment(Package* package, const QString &comment)
{
  mutex.lock();
  bool result = pndman_api_comment_pnd(package, package->getPndmanPackage(), comment.toUtf8().constData(), addCommentCallback) == 0;
  mutex.unlock();
  return result;
}

bool QPndman::Context::deleteComment(Package* package, QPndman::Comment* comment)
{
  PackageComment* pc = new PackageComment;
  pc->package = package;
  pc->comment = comment;
  mutex.lock();
  bool result = pndman_api_comment_pnd_delete(pc, package->getPndmanPackage(), comment->getTimestamp().toTime_t(), deleteCommentCallback) == 0;
  mutex.unlock();
  return result;
}

bool QPndman::Context::reloadComments(Package* package)
{
  mutex.lock();
  bool result = pndman_api_comment_pnd_pull(package, package->getPndmanPackage(), reloadCommentsCallback) == 0;
  mutex.unlock();
  return result;
}

bool QPndman::Context::reloadOwnRating(Package* package)
{
  mutex.lock();
  bool result = pndman_api_get_own_rate_pnd(package, package->getPndmanPackage(), reloadOwnRatingCallback) == 0;
  mutex.unlock();
  return result;
}

bool QPndman::Context::rate(Package* package, const int rating)
{
  mutex.lock();
  bool result = pndman_api_rate_pnd(package, package->getPndmanPackage(), rating, rateCallback) == 0;
  mutex.unlock();
  return result;
}

void QPndman::Context::setColor(int color)
{
  pndman_set_color(color);
}

void QPndman::Context::setLoggingVerbosity(int level)
{
  pndman_set_verbose(level);
}

int QPndman::Context::getLoggingVerbosity() const
{
  return pndman_get_verbose();
}

int QPndman::Context::processDownload()
{
  mutex.lock();
  int pending = pndman_curl_process(0,10000);
  mutex.unlock();
  return pending;
}

void QPndman::Context::checkUpgrades()
{
  pndman_repository_check_updates(pndmanRepositories);
}

void QPndman::Context::addCommentCallback(pndman_curl_code code, const char *info, void *user_data)
{
  Q_UNUSED(info)

  Package* package = static_cast<Package*>(user_data);

  if(code == PNDMAN_CURL_DONE)
  {
    QMetaObject::invokeMethod(package, "handleCommentAdded", Qt::QueuedConnection);
  }
  else if(code == PNDMAN_CURL_FAIL)
  {
    QMetaObject::invokeMethod(package, "handleCommentAddedFail", Qt::QueuedConnection);
  }
}

void QPndman::Context::reloadCommentsCallback(pndman_curl_code code, pndman_api_comment_packet *packet)
{
  Package* package = static_cast<Package*>(packet->user_data);
  if(code != PNDMAN_CURL_FAIL)
  {
    if(packet->pnd)
    {
      QMetaObject::invokeMethod(package, "handleNewComment", Qt::QueuedConnection,
                                Q_ARG(QString, QString::fromUtf8(packet->username)),
                                Q_ARG(QString, QString::fromUtf8(packet->comment)),
                                Q_ARG(QDateTime, QDateTime::fromTime_t(packet->date)),
                                Q_ARG(QString, QString::fromUtf8(packet->version->major)),
                                Q_ARG(QString, QString::fromUtf8(packet->version->minor)),
                                Q_ARG(QString, QString::fromUtf8(packet->version->release)),
                                Q_ARG(QString, QString::fromUtf8(packet->version->build)),
                                Q_ARG(int, Version::encodeVersionType(packet->version->type)));
    }

    if(code == PNDMAN_CURL_DONE)
    {
      QMetaObject::invokeMethod(package, "handleCommentsReloaded", Qt::QueuedConnection);
    }
  }
  else
  {
    QMetaObject::invokeMethod(package, "handleCommentReloadFail", Qt::QueuedConnection);
  }
}

void QPndman::Context::deleteCommentCallback(pndman_curl_code code, const char *info, void *user_data)
{
  Q_UNUSED(info)

  PackageComment* pc = static_cast<PackageComment*>(user_data);

  if(code == PNDMAN_CURL_DONE)
  {
    QMetaObject::invokeMethod(pc->package, "handleCommentDeleted", Qt::QueuedConnection,
                              Q_ARG(QDateTime, pc->comment->getTimestamp()));
    delete pc;
  }
  else if(code == PNDMAN_CURL_FAIL)
  {
    QMetaObject::invokeMethod(pc->package, "handleCommentDeletedFail", Qt::QueuedConnection);
    delete pc;
  }
}

void QPndman::Context::rateCallback(pndman_curl_code code, pndman_api_rate_packet *packet)
{
  Package* package = static_cast<Package*>(packet->user_data);
  if(code == PNDMAN_CURL_DONE)
  {
    QMetaObject::invokeMethod(package, "handleRating", Qt::QueuedConnection,
                              Q_ARG(int, packet->rating),
                              Q_ARG(int, packet->total_rating));
  }
  else if(code == PNDMAN_CURL_FAIL)
  {
    QMetaObject::invokeMethod(package, "handleRatingFail", Qt::QueuedConnection);
  }
}

void QPndman::Context::reloadOwnRatingCallback(pndman_curl_code code, pndman_api_rate_packet *packet)
{
  if(code != PNDMAN_CURL_FAIL)
  {
    Package* package = static_cast<Package*>(packet->user_data);
    QMetaObject::invokeMethod(package, "handleOwnRatingReloaded", Qt::QueuedConnection,
                              Q_ARG(int, packet->rating));
  }
}
