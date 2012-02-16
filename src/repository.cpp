#include "repository.h"

QPndman::Repository::Repository(QString const& url, QString const& name, QString const& updates, QDateTime const& timestamp, QString const& version, QList<Package> const& packages, bool exists, QObject* parent) : QObject(parent), 
  _url(url), _name(name), _updates(updates), _timestamp(timestamp), _version(version), _packages(packages), _exists(exists)
{
}

QPndman::Repository::Repository(Repository const& other) : QObject(0), 
  _url(other._url), _name(other._name), _updates(other._updates), _timestamp(other._timestamp), _version(other._version), _packages(other._packages), _exists(other._exists)
{
}

QPndman::Repository& QPndman::Repository::operator=(Repository const& other)
{
  if(&other == this)
    return *this;
  
  _url = other._url;
  _name = other._name;
  _updates = other._updates;
  _timestamp = other._timestamp;
  _version = other._version;
  _packages = other._packages;
  
  return *this;
}

QString QPndman::Repository::getUrl() const
{
  return _url;
}
QString QPndman::Repository::getName() const
{
  return _name;
}
QString QPndman::Repository::getUpdates() const
{
  return _updates;
}
QDateTime QPndman::Repository::getTimestamp() const
{
  return _timestamp;
}
QString QPndman::Repository::getVersion() const
{
  return _version;
}
QList<QPndman::Package> QPndman::Repository::getPackages() const
{
  return _packages;
}
bool QPndman::Repository::getExists() const
{
  return _exists;
}

void QPndman::Repository::setUrl(QString const& url)
{
  if(url != _url) 
  {
    _url = url; 
    emit urlChanged(_url);
  }
}
void QPndman::Repository::setName(QString const& name)
{
  if(name != _name) 
  {
    _name = name; 
    emit nameChanged(_name);
  }
}
void QPndman::Repository::setUpdates(QString const& updates)
{
  if(updates != _updates) 
  {
    _updates = updates; 
    emit updatesChanged(_updates);
  }
}
void QPndman::Repository::setTimestamp(QDateTime const& timestamp)
{
  if(timestamp != _timestamp) 
  {
    _timestamp = timestamp; 
    emit timestampChanged(_timestamp);
  }
}
void QPndman::Repository::setVersion(QString const& version)
{
  if(version != _version) 
  {
    _version = version; 
    emit versionChanged(_version);
  }
}
void QPndman::Repository::setPackages(QList<Package> const& packages)
{
  _packages = packages; 
  emit packagesChanged(_packages);
}
void QPndman::Repository::setExists(bool const exists)
{
  if(exists != _exists) 
  {
    _exists = exists; 
    emit existsChanged(_exists);
  }
}
