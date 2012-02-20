#include "qtpndman.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  
  QPndman::Context context;
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  
  repo->loadFrom(device);
  QPndman::SyncHandle* synchandle = repo->sync();
  while(synchandle->sync()) synchandle->update();
  device->saveRepositories();
  
  QList<QPndman::Package> packages = repo->getPackages();
  
  if(packages.size() == 0)
  {
    qDebug() << "ERROR: No packages to install!";
    return 1;
  }
  
  qsrand(QDateTime::currentMSecsSinceEpoch());
  QPndman::Package toInstall = packages.at(qrand() % packages.size());
  
  qDebug() << "Installing:" << toInstall.getTitle();  
  QPndman::Handle* handle = toInstall.install(device, QPndman::Menu, true);

  if(!handle)
  {
    qDebug() << "ERROR: Could not initiate install!";
    return 1;    
  }
  qDebug() << "Downloading...";
  while(!handle->getDone())
  {
    if(handle->download() < 0)
    {
      qDebug() << "ERROR: Could not download package!";
      return 1;      
    }
    handle->update();
  }
  device->saveRepositories();
  qDebug() << "Done";
  
  qDebug() << "Crawling:";
  device->crawl();
  QPndman::Repository* localRepo = new QPndman::LocalRepository(context);
  
  qDebug() << "Installed packages:";
  foreach(QPndman::Package installed, localRepo->getPackages())
  {
    qDebug() << installed.getTitle();
  }
  
  device->saveRepositories();
  return 0;
}
  
  