#include "qtpndman.h"

#include <QDebug>
#include <QDateTime>
#include <QCoreApplication>
#include <QTimer>

qint64 time()
{
  static qint64 t = QDateTime::currentMSecsSinceEpoch();
  qint64 d = QDateTime::currentMSecsSinceEpoch() - t;
  t = QDateTime::currentMSecsSinceEpoch();
  return d;
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  QPndman::Context* context = new QPndman::Context(&application);
  
  QList<QPndman::Device*> devices;
  
  QPndman::Device* tmpDevice = new QPndman::Device(context, "/tmp");
  if(tmpDevice->isNull())
  {
    qDebug() << "Error adding device!";
    return 1;
  }
  devices << tmpDevice;
  
  QPndman::Device* tmpDevice2 = new QPndman::Device(context, "/tmp");
  if(!tmpDevice2->isNull())
  {
    qDebug() << "Duplicate device add succeeded!";
    return 1;
  }

  foreach(QPndman::Device* device, QPndman::Device::detectDevices(context))
  {
    devices << device;
    qDebug() << "Detected device" << device->getMount();
  }
  
  foreach(const QPndman::Device* d, devices)
  {
    qDebug() << "mount:    " << d->getMount();
    qDebug() << "size:     " << d->getSize();
    qDebug() << "free:     " << d->getFree();
    qDebug() << "available:" << d->getAvailable();
    qDebug() << "";
  }

  return 0;
}
