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
    qDebug() << "Usage: ratingtest <package search term> <username> <repo api key> <rating>";
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
  QString ratingString = argv[4];

  bool ratingIsANumber = false;
  int rating = ratingString.toInt(&ratingIsANumber);

  if(!ratingIsANumber)
  {
    qDebug() << "ERROR: Rating must be a number";
    return 1;
  }

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

  qDebug() << "Getting current rating for" << pnd->getTitle();
  if(!pnd->reloadOwnRating())
  {
    qDebug() << "ERROR: getting current rating failed!";
    return 1;
  }

  while(context->processDownload() > 0);

  qDebug() << "Current rating is:" << pnd->getOwnRating() ;

  qDebug() << "Changing rating to" << rating;
  if(!pnd->rate(rating))
  {
    qDebug() << "ERROR: rating failed!";
    return 1;
  }

  while(context->processDownload() > 0);

  qDebug() << "Getting current rating again for" << pnd->getTitle();
  if(!pnd->reloadOwnRating())
  {
    qDebug() << "ERROR: getting current rating failed!";
    return 1;
  }

  while(context->processDownload() > 0);

  if(pnd->getOwnRating() != rating)
  {
    qDebug() << "ERROR: New rating does not match the one set!" << pnd->getOwnRating() << "!=" << rating;
    return 1;
  }

  qDebug() << "Rating done, new total rating:" << pnd->getRating() ;

  return 0;
}
