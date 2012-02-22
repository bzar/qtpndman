#include "qtpndman.h"

#include <QDebug>
#include <QDateTime>
#include <QCoreApplication>

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

  QList<QPndman::Repository*> repositories;
  
  QPndman::Repository* localRepo = new QPndman::LocalRepository(context);
  if(localRepo->isNull())
  {
    qDebug() << "Error adding local repository!";
    return 1;
  }
  repositories << localRepo;
  
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  if(repo->isNull())
  {
    qDebug() << "Error adding remote repository!";
    return 1;
  }
  repositories << repo;
  
  QPndman::Repository* repo2 = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  if(!repo2->isNull())
  {
    qDebug() << "Duplicate repository add succeeded!";
    return 1;
  }
  
  time();
  
  QPndman::SyncHandle* handle = repo->sync();
  qDebug() << "Starting sync for repository" << handle->getRepository()->getUrl();
  
  int counter = 0;
  while(!handle->getDone())
  {
    if(handle->sync() < 0)
    {
      qDebug() << "Error syncing repository!";
      return 1;
    }
    
    handle->update();
    
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
  
  qDebug() << "Synced in" << time() << "msec";

  foreach(QPndman::Repository* r, repositories)
  {
    qDebug() << "url:       " << r->getUrl();
    qDebug() << "name:      " << r->getName();
    qDebug() << "updates:   " << r->getUpdates();
    qDebug() << "timestamp: " << r->getTimestamp();
    qDebug() << "version:   " << r->getVersion();
    qDebug() << "packages:  " << r->getPackages().size();
    qDebug() << "";
  }
  qDebug() << "Listed repo information in" << time() << "msec";
  
  
  qDebug() << "Saving repositories to /tmp";
  QPndman::Device* tmpDevice = new QPndman::Device(context, "/tmp");
  tmpDevice->saveRepositories();
  
  qDebug() << "Deleting repositories";
  delete repo;
  delete repo2;
  
  qDebug() << "Loading repositories from /tmp";
  repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  repo->loadFrom(tmpDevice);
  
  qDebug() << "name:" << repo->getName() << " packages:" << repo->getPackages().size();
  
  return 0;
}
