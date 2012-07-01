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

  if(argc != 5)
  {
    qDebug() << "Usage: commentaddtest <package search term> <username> <repo api key> <comment>";
    return 1;
  }

  pndman_set_verbose(PNDMAN_LEVEL_CRAP);

  QPndman::Context* context = new QPndman::Context(&application);
  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/client/masterlist");
  repo->loadFrom(device);

  QString searchTerm = argv[1];
  QString username = argv[2];
  QString key = argv[3];
  QString comment = argv[4];

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

  qDebug() << "Setting credentials";
  repo->setCredentials(username, key);

  qDebug() << "Adding comment for" << pnd->getTitle();
  pnd->addComment(comment);
  while(context->processDownload() > 0);

  qDebug() << "Checking if comment was added...";
  pnd->reloadComments();
  while(context->processDownload() > 0);

  if(pnd->getComments().size() == 0 || pnd->getComments().first()->getContent() != comment)
  {
    qDebug() << "ERROR: Comment was not added!";
    return 1;
  }

  qDebug() << "Comment added succesfully";

  return 0;
}
