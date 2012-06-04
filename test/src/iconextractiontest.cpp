
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

  pndman_set_verbose(PNDMAN_LEVEL_CRAP);

  QString searchTerm = argv[1];

  QCoreApplication application(argc, argv);
  QPndman::Context* context = new QPndman::Context(&application);

  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QList<QPndman::Device*> devices = QPndman::Device::detectDevices(context);
  devices.append(device);

  QPndman::LocalRepository* local = new QPndman::LocalRepository(context);

  device->loadRepository(local);

  qDebug() << "Crawling";
  context->crawlAllPndmanDevices();

  QPndman::Package* pnd = 0;
  foreach(QPndman::Package* package, local->getPackages())
  {
    if(package->getPath().contains(searchTerm))
    {
      pnd = package;
      break;
    }
  }

  if(pnd == 0)
  {
    qDebug() << "No such PND";
    return 1;
  }

  qDebug() << "Extracting icon from" << pnd->getId();

  QImage icon = pnd->getEmbeddedIcon();
  QString fileName = pnd->getId() + ".png";
  icon.save(fileName);

  qDebug() << "Saved to" << fileName;

  return 0;
}


