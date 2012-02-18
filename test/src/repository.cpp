#include "repository.h"

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

Test::Test() : QObject(0), manager(QPndman::Manager::getManager()) {}
void Test::run()
{
  
  connect(manager, SIGNAL(syncError()), this, SLOT(syncError()));
  connect(manager, SIGNAL(syncFinished()), this, SLOT(syncFinished()));
  if(!manager->addDevice("/tmp"))
  {
    qDebug() << "Error adding device!";
    QCoreApplication::exit(1);
  }
  
  if(!manager->addRepository("http://repo.openpandora.org/includes/get_data.php"))
  {
    qDebug() << "Error adding repository!";
    QCoreApplication::exit(1);
  }
  
  if(manager->addRepository("http://repo.openpandora.org/includes/get_data.php"))
  {
    qDebug() << "Duplicate repository add succeeded!";
    QCoreApplication::exit(1);
  }
  
  time();
  manager->syncAll();
}
  
void Test::syncError()
{
  qDebug() << "Error syncing repositories!";
  QCoreApplication::exit(1);
}
  
void Test::syncFinished()
{
  qDebug() << "Synced in" << time() << "msec";

  QList<QPndman::Repository> repositories = manager->getRepositories();
  qDebug() << "Generated repository list in" << time() << "msec";
  
  foreach(const QPndman::Repository r, repositories)
  {
    qDebug() << "url:       " << r.getUrl();
    qDebug() << "name:      " << r.getName();
    qDebug() << "updates:   " << r.getUpdates();
    qDebug() << "timestamp: " << r.getTimestamp();
    qDebug() << "version:   " << r.getVersion();
    qDebug() << "exists:    " << r.getExists();
    qDebug() << "packages:  " << r.getPackages().size();
    qDebug() << "";
  }
  qDebug() << "Listed repo information in" << time() << "msec";
  QCoreApplication::exit(0);
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  Test test;
  QTimer t;
  t.setSingleShot(true);
  t.connect(&t, SIGNAL(timeout()), &test, SLOT(run()));
  t.start();
  return application.exec();
}