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

  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  
  QPndman::SyncHandle* handle = repo->sync();
  qDebug() << "Starting sync for repository" << handle->getRepository()->getUrl();
  
  while(!handle->getDone())
  {
    if(context->processDownload() < 0)
    {
      qDebug() << "Error syncing repository!";
      return 1;
    }
    
    handle->update();
  }
  
  qDebug() << "Synced.";

  QList<QPndman::Package*> packages = repo->getPackages();
  foreach(QPndman::Package* p, packages)
  {
    qDebug() << p->getTitle() << "-" << p->getDescription();
  }

  return 0;
}
