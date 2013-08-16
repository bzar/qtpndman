#ifndef QT_PNDMAN_H
#define QT_PNDMAN_H

#include <QObject>
#include <QMutex>
#include "pndman.h"

namespace QPndman
{
  class Package;
  class Comment;

  class Context : public QObject
  {
    Q_OBJECT

  public:
    Context(QObject* parent = 0);
    ~Context();

    pndman_repository* addPndmanRepository(QString const& url);
    void removePndmanRepository(pndman_repository* repository);
    pndman_repository* getPndmanRepositories();
    pndman_repository* getLastPndmanRepository();
    pndman_repository* getLocalPndmanRepository();
    void clearPndmanRepository(pndman_repository* repository);
    void checkLocalPndmanRepository();
    void setRepositoryCredentials(pndman_repository* repository, QString const& user, QString const& key, const bool store);

    pndman_device* addPndmanDevice(QString const& path);
    void removePndmanDevice(pndman_device* device);
    pndman_device* getPndmanDevices();
    pndman_device* getLastPndmanDevice();

    pndman_device* detectPndmanDevices();
    int crawlPndmanDevice(pndman_device* device, bool full = false);
    int crawlAllPndmanDevices(bool full = false);
    bool crawlPndmanPackage(pndman_package* package, bool full = false);
    bool crawlPndmanPackageById(QString const& packageId, bool full = false);

    bool saveRepositories(pndman_device* device);
    bool loadRepository(pndman_repository* repository, pndman_device* device);
    void checkUpgrades();

    bool performHandle(pndman_package_handle* handle);
    bool commitHandle(pndman_package_handle* handle);
    void freeHandle(pndman_package_handle* handle);

    bool performSyncHandle(pndman_sync_handle* handle);
    void freeSyncHandle(pndman_sync_handle* handle);

    bool addComment(Package* package, QString const& comment);
    bool deleteComment(Package* package, Comment *comment);
    bool reloadComments(Package* package);
    bool reloadOwnRating(Package* package);
    bool rate(Package* package, int const rating);

    void setColor(int color);

    void setLoggingVerbosity(int level);
    int getLoggingVerbosity() const;

    int processDownload();

  signals:
    void crawlDone(pndman_package *package = 0);

  private:
    struct PackageComment
    {
      Package* package;
      Comment* comment;
    };

    static void addCommentCallback(pndman_curl_code code, const char *info, void *user_data);
    static void reloadCommentsCallback(pndman_curl_code code, pndman_api_comment_packet *packet);
    static void deleteCommentCallback(pndman_curl_code code, const char *info, void *user_data);
    static void rateCallback(pndman_curl_code code, pndman_api_rate_packet *packet);
    static void reloadOwnRatingCallback(pndman_curl_code code, struct pndman_api_rate_packet *packet);

    pndman_repository* localPndmanRepository;
    pndman_repository* pndmanRepositories;
    pndman_device* pndmanDevices;
    QMutex mutex;
  };
}

#endif
