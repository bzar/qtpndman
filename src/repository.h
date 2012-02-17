#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QDateTime>

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
    Q_PROPERTY(QList< QSharedPointer<Package> > packages READ getPackages WRITE setPackages NOTIFY packagesChanged);

  public:
    Repository(QString const& url, QString const& name, QString const& updates, QDateTime const& timestamp, QString const& version, QList< QSharedPointer<Package> > const& packages, bool exists, QObject* parent = 0);
    Repository(pndman_repository const* p);
    Repository(Repository const& other);
    ~Repository();
    Repository& operator=(Repository const& other);

  public slots:
    QString getUrl() const;
    QString getName() const;
    QString getUpdates() const;
    QDateTime getTimestamp() const;
    QString getVersion() const;
    QList< QSharedPointer<Package> > getPackages() const;
    bool getExists() const;

    void setUrl(QString const& url);
    void setName(QString const& name);
    void setUpdates(QString const& updates);
    void setTimestamp(QDateTime const& timestamp);
    void setVersion(QString const& version);
    void setPackages(QList< QSharedPointer<Package> > const& packages);
    void setExists(bool const exists);
    
  signals:
    void urlChanged(QString newUrl);
    void nameChanged(QString newName);
    void updatesChanged(QString newUpdates);
    void timestampChanged(QDateTime newTimestamp);
    void versionChanged(QString newVersion);
    void packagesChanged(QList< QSharedPointer<Package> > newPackages);
    void existsChanged(bool newExists);
    
  private:
    QString _url;
    QString _name;
    QString _updates;
    QDateTime _timestamp;
    QString _version;
    QList< QSharedPointer<Package> > _packages;
    bool _exists;

  };
}

#endif
