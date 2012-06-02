#include "qtpndman.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);

  pndman_set_verbose(PNDMAN_LEVEL_CRAP);

  QPndman::Context* context = new QPndman::Context(&application);
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/client/masterlist");
  if(!repo->loadFrom(device))
  {
    qDebug() << "Error loading remote repository information from device!";
    return 1;
  }

  QPndman::LocalRepository* local = new QPndman::LocalRepository(context);
  if(!local->loadFrom(device))
  {
    qDebug() << "Error loading local repository information from device!";
    return 1;
  }

  qDebug() << "Crawling";
  device->crawl();
  qDebug() << "Checking for removed packages";
  context->checkLocalPndmanRepository();
  qDebug() << "Checking for upgrades";
  context->checkUpgrades();

  local->update();

  QPndman::Package* toUpgrade = 0;

  qDebug() << "Finding an upgradable package from" << local->getPackages().count() << "local packages";

  foreach(QPndman::Package* package, local->getPackages())
  {
    if(package->getUpgradeCandidate() != 0)
    {
      toUpgrade = package;
      break;
    }
    else
    {
      qDebug() << "No upgrade for" << package->getId();
    }
  }
  
  if(!toUpgrade)
  {
    qDebug() << "Found no upgradable packages";
    return 1;
  }

  qDebug() << "Found upgradable package" << toUpgrade->getId() << "("
           << toUpgrade->getVersion()->toString() << "->"
           << toUpgrade->getUpgradeCandidate()->getVersion()->toString() << ")";

  QPndman::UpgradeHandle* handle = toUpgrade->upgrade();

  if(!handle)
  {
    qDebug() << "ERROR: Could not initiate upgrade!";
    return 1;
  }
  qDebug() << "Downloading...";
  int counter = 0;
  while(context->processDownload() > 0)
  {
    if(handle->getBytesToDownload() != 0)
    {
      int percentage = 100 * handle->getBytesDownloaded() / handle->getBytesToDownload();
      if(counter + 10 <= percentage)
      {
        counter += 10;
        qDebug() << percentage << "%";
      }
    }
    else
    {
      if(counter + 1024*100 <= handle->getBytesDownloaded())
      {
        counter += 1024*100;
        qDebug() << handle->getBytesDownloaded() / 1024 << "KiB";
      }
    }

  }


  qDebug() << "Crawling";
  device->crawl();
  qDebug() << "Checking for removed packages";
  context->checkLocalPndmanRepository();
  qDebug() << "Checking for upgrades";
  context->checkUpgrades();
  qDebug() << "Done";
  device->saveRepositories();

  return 0;
}
  
  
