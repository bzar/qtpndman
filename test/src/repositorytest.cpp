#include "repositorytest.h"

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

RepositoryTest::RepositoryTest() : QObject(0) 
{
  
}

void RepositoryTest::run()
{
  QPndman::Context context;
  
  QList<QPndman::Repository*> repositories;
  
  QPndman::Repository* localRepo = new QPndman::Repository(context);
  if(localRepo->isNull())
  {
    qDebug() << "Error adding local repository!";
    QCoreApplication::exit(1); return;
  }
  repositories << localRepo;
  
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  if(repo->isNull())
  {
    qDebug() << "Error adding remote repository!";
    QCoreApplication::exit(1); return;
  }
  repositories << repo;
  
  QPndman::Repository* repo2 = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  if(!repo2->isNull())
  {
    qDebug() << "Duplicate repository add succeeded!";
    QCoreApplication::exit(1); return;
  }
  
  time();
  
  QPndman::SyncHandle* handle = repo->sync();
  qDebug() << "Starting sync for repository" << handle->getRepository()->getUrl();
  
  while(!handle->getDone())
  {
    if(QPndman::SyncHandle::sync() < 0)
    {
      qDebug() << "Error syncing repository!";
      QCoreApplication::exit(1); return;
    }
    
    handle->update();
  }
  
  qDebug() << "Synced in" << time() << "msec";

  foreach(const QPndman::Repository* r, repositories)
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
  tmpDevice->loadRepository(repo);
  
  for(pndman_repository* r = context.getPndmanRepositories(); r; r = r->next)
  {
    qDebug() << "Found repository" << r->name;
  }
  
  
  QCoreApplication::exit(0);
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  RepositoryTest test;
  QTimer t;
  t.setSingleShot(true);
  t.connect(&t, SIGNAL(timeout()), &test, SLOT(run()));
  t.start();
  return application.exec();
}
