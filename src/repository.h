#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QDateTime>
#include <QExplicitlySharedDataPointer>

#include "package.h"
#include "pndman.h"

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
    Repository();
    Repository(pndman_repository* p);
    Repository(Repository const& other);
    Repository& operator=(Repository const& other);

    pndman_repository* getPndmanRepository() const;
    bool isNull() const;
    
  public slots:
    QString getUrl() const;
    QString getName() const;
    QString getUpdates() const;
    QDateTime getTimestamp() const;
    QString getVersion() const;
    QList<Package> getPackages() const;
    bool getExists() const;

    void setUrl(QString const& url);
    void setName(QString const& name);
    void setUpdates(QString const& updates);
    void setTimestamp(QDateTime const& timestamp);
    void setVersion(QString const& version);
    void setPackages(QList<Package> const& packages);
    void setExists(bool const exists);
    
  signals:
    void urlChanged(QString newUrl);
    void nameChanged(QString newName);
    void updatesChanged(QString newUpdates);
    void timestampChanged(QDateTime newTimestamp);
    void versionChanged(QString newVersion);
    void packagesChanged(QList<Package> newPackages);
    void existsChanged(bool newExists);
    
  private:
    struct Data : public QSharedData
    {
      Data(pndman_repository* p);
      pndman_repository* repository;
      QString url;
      QString name;
      QString updates;
      QDateTime timestamp;
      QString version;
      QList<Package> packages;
      bool exists;
    };

    QExplicitlySharedDataPointer<Data> d;

  };
}

#endif
