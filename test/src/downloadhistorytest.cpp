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

  if(argc != 3)
  {
    qDebug() << "Usage: downloadhistorytest <username> <repo api key>";
    return 1;
  }

  pndman_set_verbose(PNDMAN_LEVEL_CRAP);

  QString username = argv[1];
  QString key = argv[2];

  QPndman::Context* context = new QPndman::Context(&application);
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/client/masterlist");
  repo->loadFrom(device);

  qDebug() << "Setting credentials";
  repo->setCredentials(username, key);

  qDebug() << "Getting download history";
  if(!repo->reloadDownloadHistory())
  {
    qDebug() << "Error getting download history";
    return 1;
  }

  while(context->processDownload() > 0);

  qDebug() << "Done.";

  foreach(QPndman::DownloadHistoryItem* item, repo->getDownloadHistory())
  {
    qDebug() << item->getId() << item->getDownloadedVersion()->toString() << item->getTimestamp().toString("yyyy-MM-ddThh:mm");
  }
}
