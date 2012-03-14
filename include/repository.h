#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QDateTime>

#include "context.h"
#include "package.h"
#include "pndman.h"
#include "synchandle.h"

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

  public:
    Repository(Context*  c, QString const& url, QObject* parent = 0);
    ~Repository();

    SyncHandle* sync();
    bool loadFrom(Device* device);
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

  public slots:
    virtual void update();
    
  signals:
    void urlChanged(QString newUrl);
    void nameChanged(QString newName);
    void updatesChanged(QString newUpdates);
    void timestampChanged(QDateTime newTimestamp);
    void versionChanged(QString newVersion);
    void packagesChanged(QList<Package*> newPackages);
    
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
