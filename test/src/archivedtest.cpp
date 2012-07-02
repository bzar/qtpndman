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
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/client/masterlist");
  repo->loadFrom(device);

  QString searchTerm = argv[1];
  QPndman::Package* pnd = 0;
  foreach(QPndman::Package* package, repo->getPackages())
  {
    if(package->getTitle().contains(searchTerm) || package->getId().contains(searchTerm))
    {
      pnd = package;
      break;
    }
  }

  if(pnd == 0)
  {
    qDebug() << "No such PND";
    return 1;
  }

  qDebug() << "Getting archived versions for" << pnd->getTitle();

  pnd->reloadArchived();

  while(context->processDownload() > 0);

  qDebug() << "Done.";

  foreach(QPndman::Package* p, pnd->getArchived())
  {
    qDebug() << p->getVersion()->toString();
  }

  return 0;
}
