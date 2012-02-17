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

  if(manager->addDevice("/tmp"))
  {
    qDebug() << "Duplicate device add succeeded!";
    return 1;
  }

  if(!manager->detectDevices())
  {
    qDebug() << "Error detecting devices!";
    return 1;
  }
  
  foreach(const QSharedPointer<QPndman::Device> d, manager->getDevices())
  {
    qDebug() << "mount:    " << d->getMount();
    qDebug() << "device:   " << d->getDevice();
    qDebug() << "size:     " << d->getSize();
    qDebug() << "free:     " << d->getFree();
    qDebug() << "available:" << d->getAvailable();
    qDebug() << "";
  }
  
  return 0;
}