#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QDateTime>

#include "context.h"
#include "package.h"
#include "pndman.h"
#include "synchandle.h"
#include "downloadhistoryitem.h"

namespace QPndman
{
  class Device;
  
  class Repository : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QString updates READ getUpdates NOTIFY updatesChanged)
    Q_PROPERTY(QDateTime timestamp READ getTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(QString version READ getVersion NOTIFY versionChanged)
    Q_PROPERTY(QList<QPndman::Package*> packages READ getPackages NOTIFY packagesChanged)
    Q_PROPERTY(QList<QPndman::DownloadHistoryItem*> downloadHistory READ getDownloadHistory NOTIFY downloadHistoryChanged)

  public:


    Repository(Context*  c, QString const& url, QObject* parent = 0);
    ~Repository();

    SyncHandle* sync(bool fullSync = true);
    bool loadFrom(Device* device, bool autoUpdate = true);
    void clear();
    
    pndman_repository* getPndmanRepository() const;
    bool isNull() const;
    int getIdentifier() const;
    
    QString getUrl() const;
    QString getName() const;
    QString getUpdates() const;
    QDateTime getTimestamp() const;
    QString getVersion() const;
    QList<Package*> getPackages() const;
    QList<DownloadHistoryItem*> getDownloadHistory() const;

    void setCredentials(QString const& user, QString const& key, bool const store = false);

    Context* getContext() const;

  public slots:
    virtual void update();
    bool reloadDownloadHistory();

  signals:
    void urlChanged(QString newUrl);
    void nameChanged(QString newName);
    void updatesChanged(QString newUpdates);
    void timestampChanged(QDateTime newTimestamp);
    void versionChanged(QString newVersion);
    void packagesChanged(QList<Package*> newPackages);
    void downloadHistoryChanged(QList<DownloadHistoryItem*> newDownloadHistory);

  protected:
    Repository(Context*  c, pndman_repository* p, QObject* parent = 0);

  protected:
    void setUrl(QString const& newUrl);
    void setName(QString const& newName);
    void setUpdates(QString const& newUpdates);
    void setTimestamp(QDateTime const& newTimestamp);
    void setVersion(QString const& newVersion);
    void setPackages(QList<Package*> const& newPackages);

    int identifier;
    static int nextIdentifier;

    Context* context;

    pndman_repository* pndmanRepository;
    QString url;
    QString name;
    QString updates;
    QDateTime timestamp;
    QString version;
    QList<Package*> packages;
    QList<DownloadHistoryItem*> downloadHistory;

    static void reloadDownloadHistoryCallback(pndman_curl_code code, struct pndman_api_history_packet *packet);
  };
  
  class LocalRepository : public Repository
  {
    Q_OBJECT
  public:
    LocalRepository(Context*  c, QObject* parent = 0);
    bool hasPackageInstalled(Package* package);
    
  public slots:
    void update();

  };
}

#endif
