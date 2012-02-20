#include "devicetest.h"

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

DeviceTest::DeviceTest() : QObject(0), context() {}
void DeviceTest::run()
{
  QList<QPndman::Device*> devices;
  
  QPndman::Device* tmpDevice = new QPndman::Device(context, "/tmp");
  if(tmpDevice->isNull())
  {
    qDebug() << "Error adding device!";
    QCoreApplication::exit(1); return;
  }
  devices << tmpDevice;
  
  QPndman::Device* tmpDevice2 = new QPndman::Device(context, "/tmp");
  if(!tmpDevice2->isNull())
  {
    qDebug() << "Duplicate device add succeeded!";
    QCoreApplication::exit(1); return;
  }

  foreach(QPndman::Device* device, QPndman::Device::detectDevices(context))
  {
    devices << device;
    qDebug() << "Detected device" << device->getDevice();
  }
  
  foreach(const QPndman::Device* d, devices)
  {
    qDebug() << "mount:    " << d->getMount();
    qDebug() << "device:   " << d->getDevice();
    qDebug() << "size:     " << d->getSize();
    qDebug() << "free:     " << d->getFree();
    qDebug() << "available:" << d->getAvailable();
    qDebug() << "";
  }

  QCoreApplication::exit(0);
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  DeviceTest test;
  QTimer t;
  t.setSingleShot(true);
  t.connect(&t, SIGNAL(timeout()), &test, SLOT(run()));
  t.start();
  return application.exec();
}
