#include "qtpndman.h"

#include <QDebug>
#include <QDateTime>

qint64 time()
{
  static qint64 t = QDateTime::currentMSecsSinceEpoch();
  qint64 d = QDateTime::currentMSecsSinceEpoch() - t;
  t = QDateTime::currentMSecsSinceEpoch();
  return d;
}

int main()
{
  QPndman::Manager* manager = QPndman::Manager::getManager();
  if(!manager->addDevice("/tmp"))
  {
    qDebug() << "Error adding device!";
    return 1;
  }
  
  if(!manager->addRepository("http://repo.openpandora.org/includes/get_data.php"))
  {
    qDebug() << "Error adding repository!";
    return 1;
  }
  
  if(manager->addRepository("http://repo.openpandora.org/includes/get_data.php"))
  {
    qDebug() << "Duplicate repository add succeeded!";
    return 1;
  }
  
  time();
  if(!manager->syncAll())
  {
    qDebug() << "Error syncing repositories!";
    return 1;    
  }
  qDebug() << "Synced in" << time() << "msec";
  
  QList< QSharedPointer<QPndman::Repository> > repositories = manager->getRepositories();
  qDebug() << "Generated repository list in" << time() << "msec";
  
  foreach(const QSharedPointer<QPndman::Repository> r, repositories)
  {
    qDebug() << "url:       " << r->getUrl();
    qDebug() << "name:      " << r->getName();
    qDebug() << "updates:   " << r->getUpdates();
    qDebug() << "timestamp: " << r->getTimestamp();
    qDebug() << "version:   " << r->getVersion();
    qDebug() << "exists:    " << r->getExists();
    qDebug() << "packages:  " << r->getPackages().size();
    qDebug() << "";
  }
  qDebug() << "Listed repo information in" << time() << "msec";
  
  return 0;
}