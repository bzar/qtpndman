#include "qtpndman.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    qDebug() << "Usage:" << argv[0] << "<pnd filename to remove>";
    return 1;
  }

  QString searchTerm = argv[1];

  QCoreApplication application(argc, argv);
  QPndman::Context* context = new QPndman::Context(&application);

  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QList<QPndman::Device*> devices = QPndman::Device::detectDevices(context);
  devices.append(device);

  QPndman::LocalRepository* local = new QPndman::LocalRepository(context);

  device->loadRepository(local);

  qDebug() << "Crawling";
  foreach(QPndman::Device* d, devices)
  {
    d->crawl();
  }

  QPndman::Package* toRemove = 0;
  foreach(QPndman::Package* package, local->getPackages())
  {
    if(package->getPath().contains(searchTerm))
    {
      toRemove = package;
      break;
    }
  }

  if(toRemove == 0)
  {
    qDebug() << "No such PND";
    return 1;
  }

  qDebug() << "Removing" << toRemove->getPath();

  QPndman::Device* packageDevice = 0;
  foreach(QPndman::Device* d, devices)
  {
    if(d->getMount() == toRemove->getMount())
    {
      packageDevice = d;
      break;
    }
  }

  if(packageDevice == 0)
  {
    qDebug() << "PND device not found?";
    return 1;
  }

  if(!packageDevice->remove(toRemove))
  {
    qDebug() << "Error removing PND";
    return 1;
  }

  qDebug() << "Remove successful";

  qDebug() << "Crawling";
  foreach(QPndman::Device* d, devices)
  {
    d->crawl();
  }

  device->saveRepositories();
  
  return 0;
}
  
  
