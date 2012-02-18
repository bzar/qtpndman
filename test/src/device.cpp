#include "device.h"

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

Test::Test() : QObject(0), manager(QPndman::Manager::getManager()) {}
void Test::run()
{
  if(manager->addDevice("/tmp").isNull())
  {
    qDebug() << "Error adding device!";
    QCoreApplication::exit(1);
  }

  if(!manager->addDevice("/tmp").isNull())
  {
    qDebug() << "Duplicate device add succeeded!";
    QCoreApplication::exit(1);
  }

  foreach(QPndman::Device device, manager->detectDevices())
  {
    qDebug() << "Detected device" << device.getDevice();
  }
  
  foreach(const QPndman::Device d, manager->getDevices())
  {
    qDebug() << "mount:    " << d.getMount();
    qDebug() << "device:   " << d.getDevice();
    qDebug() << "size:     " << d.getSize();
    qDebug() << "free:     " << d.getFree();
    qDebug() << "available:" << d.getAvailable();
    qDebug() << "";
  }
  
  QCoreApplication::exit(0);
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  Test test;
  QTimer t;
  t.setSingleShot(true);
  t.connect(&t, SIGNAL(timeout()), &test, SLOT(run()));
  t.start();
  return application.exec();
}
