#include "qtpndman.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  QPndman::Context* context = new QPndman::Context(&application);
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  repo->loadFrom(device);
  repo->update();

  QPndman::LocalRepository* local = new QPndman::LocalRepository(context);
  local->loadFrom(device);
  local->update();
  
  bool noUpgradablePackages = true;
  
  foreach(QPndman::Package package, local->getPackages())
  {
    if(!package.getUpgradeCandidate().isNull())
    {
      noUpgradablePackages = false;
      qDebug() << "Found upgradable package" << package.getId() << "(" 
               << package.getVersion().toString() << "->" 
               << package.getUpgradeCandidate().getVersion().toString() << ")";
    }
  }
  
  if(noUpgradablePackages)
  {
    qDebug() << "Found no upgradable packages";
  }
  
  return 0;
}
  
  