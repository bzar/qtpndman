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
  connect(manager, SIGNAL(syncStarted(SyncHandle)), this, SLOT(syncStarted(SyncHandle)));
  connect(manager, SIGNAL(syncError()), this, SLOT(syncError()));
  connect(manager, SIGNAL(syncError(SyncHandle)), this, SLOT(syncError(SyncHandle)));
  connect(manager, SIGNAL(syncFinished()), this, SLOT(syncFinished()));
  
  if(!manager->addRepository("http://repo.openpandora.org/includes/get_data.php"))
  {
    qDebug() << "Error adding repository!";
    QCoreApplication::exit(1);
  }
  
  time();
  manager->syncAll();
}

void Test::syncStarted(QPndman::SyncHandle handle)
{
  qDebug() << "Starting sync for repository" << handle.getRepository().getUrl();
}
void Test::syncing()
{
}

void Test::syncError()
{
  qDebug() << "Error syncing repositories!";
  QCoreApplication::exit(1);
}

void Test::syncError(QPndman::SyncHandle handle)
{
  if(!handle.getRepository().getUrl().isEmpty())
  {
    qDebug() << "Error initiating sync for repository" << handle.getRepository().getUrl();
    QCoreApplication::exit(1);
  }
}

void Test::syncFinished()
{
  qDebug() << "Synced in" << time() << "msec";

  QList<QPndman::Repository> repositories = manager->getRepositories();
  
  foreach(const QPndman::Repository r, repositories)
  {
    QList<QPndman::Package> packages = r.getPackages();
    foreach(QPndman::Package p, packages)
    {
      qDebug() << p.getTitle() << "-" << p.getDescription();
    }
  }
  
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
