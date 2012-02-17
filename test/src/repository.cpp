#include "qtpndman.h"

#include <QDebug>

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
  
  int syncNum = manager->syncAll();
  qDebug() << "Number of repositories:   " << syncNum;
  qDebug() << "";
  
  foreach(const QSharedPointer<QPndman::Repository> r, manager->getRepositories())
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
  
  return 0;
}