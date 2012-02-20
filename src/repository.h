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
  class Repository : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged);
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString updates READ getUpdates WRITE setUpdates NOTIFY updatesChanged);
    Q_PROPERTY(QDateTime timestamp READ getTimestamp WRITE setTimestamp NOTIFY timestampChanged);
    Q_PROPERTY(QString version READ getVersion WRITE setVersion NOTIFY versionChanged);
    Q_PROPERTY(QList<Package> packages READ getPackages WRITE setPackages NOTIFY packagesChanged);

  public:
    Repository(Context& c, QObject* parent = 0);
    Repository(Context& c, QString const& url, QObject* parent = 0);
    Repository(Context& c, pndman_repository* p, QObject* parent = 0);
    
    SyncHandle* sync();
    
    pndman_repository* getPndmanRepository() const;
    bool isNull() const;
    int getIdentifier() const;
    
    QString getUrl() const;
    QString getName() const;
    QString getUpdates() const;
    QDateTime getTimestamp() const;
    QString getVersion() const;
    QList<Package> getPackages() const;

  public slots:
    void update();
    void setUrl(QString const& url);
    void setName(QString const& name);
    void setUpdates(QString const& updates);
    void setTimestamp(QDateTime const& timestamp);
    void setVersion(QString const& version);
    void setPackages(QList<Package> const& packages);
    
  signals:
    void urlChanged(QString newUrl);
    void nameChanged(QString newName);
    void updatesChanged(QString newUpdates);
    void timestampChanged(QDateTime newTimestamp);
    void versionChanged(QString newVersion);
    void packagesChanged(QList<Package> newPackages);
    
  private:
    struct Data
    {
      Data(Context& c, pndman_repository* p);
      ~Data();
      
      int identifier;
      Context context;

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
}

#endif
