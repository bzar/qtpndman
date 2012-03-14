#include "qtpndman.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  QPndman::Context* context = new QPndman::Context(&application);
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
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
  
  bool noUpgradablePackages = true;
  
  foreach(QPndman::Package* package, local->getPackages())
  {
    if(package->getUpgradeCandidate() != 0)
    {
      noUpgradablePackages = false;
      qDebug() << "Found upgradable package" << package->getId() << "("
               << package->getVersion()->toString() << "->"
               << package->getUpgradeCandidate()->getVersion()->toString() << ")";
    }
  }
  
  if(noUpgradablePackages)
  {
    qDebug() << "Found no upgradable packages";
  }
  
  return 0;
}
  
  
