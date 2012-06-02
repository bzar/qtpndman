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

  pndman_set_verbose(PNDMAN_LEVEL_CRAP);

  QPndman::Context* context = new QPndman::Context(&application);

  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/client/masterlist");
  
  QPndman::SyncHandle* handle = repo->sync();
  qDebug() << "Starting sync for repository" << handle->getRepository()->getUrl();
  
  while(context->processDownload() > 0);
  
  qDebug() << "Synced.";

  QList<QPndman::Package*> packages = repo->getPackages();
  foreach(QPndman::Package* p, packages)
  {
    qDebug() << p->getTitle() << "-" << p->getDescription();
  }

  return 0;
}
