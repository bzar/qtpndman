#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QDateTime>
#include <QSharedPointer>

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

    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged);
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged);
    Q_PROPERTY(QString updates READ getUpdates NOTIFY updatesChanged);
    Q_PROPERTY(QDateTime timestamp READ getTimestamp NOTIFY timestampChanged);
    Q_PROPERTY(QString version READ getVersion NOTIFY versionChanged);
    Q_PROPERTY(QList<Package> packages READ getPackages NOTIFY packagesChanged);

  public:
    Repository(Context*  c, QString const& url, QObject* parent = 0);
    
    SyncHandle* sync();
    bool loadFrom(Device* device);
    
    pndman_repository* getPndmanRepository() const;
    bool isNull() const;
    int getIdentifier() const;
    
    QString getUrl() const;
    QString getName() const;
    QString getUpdates() const;
    QDateTime getTimestamp() const;
    QString getVersion() const;
    QList<Package> getPackages();

  public slots:
    void update();
    
  signals:
    void urlChanged(QString newUrl);
    void nameChanged(QString newName);
    void updatesChanged(QString newUpdates);
    void timestampChanged(QDateTime newTimestamp);
    void versionChanged(QString newVersion);
    void packagesChanged(QList<Package> newPackages);
    
  protected:
    Repository(Context*  c, pndman_repository* p, QObject* parent = 0);

  private:
    void setUrl(QString const& url);
    void setName(QString const& name);
    void setUpdates(QString const& updates);
    void setTimestamp(QDateTime const& timestamp);
    void setVersion(QString const& version);
    void setPackages(QList<Package> const& packages);

    struct Data
    {
      Data(Context*  c, pndman_repository* p);
      ~Data();
      
      int identifier;
      Context* context;

      pndman_repository* pndmanRepository;
      QString url;
      QString name;
      QString updates;
      QDateTime timestamp;
      QString version;
      QList<Package> packages;
      
      static int nextIdentifier;
    };

    QSharedPointer<Data> d;    
  };
  
  class LocalRepository : public Repository
  {
    Q_OBJECT
  public:
    LocalRepository(Context*  c, QObject* parent = 0);

  };
}

#endif
