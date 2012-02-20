#include "packageinfo.h"

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

PackageInfoTest::PackageInfoTest() : QObject(0), context() {}

void PackageInfoTest::run()
{
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/includes/get_data.php");
  
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
  
  qDebug() << "Synced.";

  QList<QPndman::Package> packages = repo->getPackages();
  foreach(QPndman::Package p, packages)
  {
    qDebug() << p.getTitle() << "-" << p.getDescription();
  }

  QCoreApplication::exit(0);
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  PackageInfoTest test;
  QTimer t;
  t.setSingleShot(true);
  t.connect(&t, SIGNAL(timeout()), &test, SLOT(run()));
  t.start();
  return application.exec();
}
