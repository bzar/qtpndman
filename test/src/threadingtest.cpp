#include "qtpndman.h"
#include <QDebug>
#include <QCoreApplication>
#include <QMutex>
#include <QFuture>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

void downloadThread(QPndman::Context* context, QMutex* stopMutex)
{
  int pending = 0;
  timespec ts = { 0, 50 * 1000 * 1000 };
  while(stopMutex->tryLock())
  {
    pending = context->processDownload();
    stopMutex->unlock();
    nanosleep(&ts, 0);
  }

  qDebug() << "downloadThread: cleaning up";

  while(pending > 0)
  {
    pending = context->processDownload();
  }
}

int main(int argc, char** argv)
{
  QCoreApplication application(argc, argv);
  qsrand(QDateTime::currentMSecsSinceEpoch());
  pndman_set_verbose(PNDMAN_LEVEL_CRAP);

  QPndman::Context* context = new QPndman::Context(&application);

  QMutex downloadThreadStopMutex;
  QFuture<void> downloadThreadFuture = QtConcurrent::run(downloadThread, context, &downloadThreadStopMutex);


  QPndman::Device* device = new QPndman::Device(context, "/tmp");
  QPndman::Repository* repo = new QPndman::Repository(context, "http://repo.openpandora.org/client/masterlist");
  repo->loadFrom(device);

  QList<QPndman::Package*> packages = repo->getPackages();

  if(packages.size() == 0)
  {
    qDebug() << "ERROR: no packages";
    downloadThreadStopMutex.lock();
    return 1;
  }

  QPndman::Package* toInstall = packages.at(qrand() % packages.size());
  QPndman::Package* toInstall2 = packages.at(qrand() % packages.size());

  qDebug() << "Installing" << toInstall->getId() << "and" << toInstall2->getId();

  // Start two downloads, cancel and restart them so that one is always running

  QPndman::InstallHandle* h1 = toInstall->install(device, QPndman::Enum::Menu);
  if(!h1)
  {
    qDebug() << "ERROR: h1 is null!";
  }

  QPndman::InstallHandle* h2 = toInstall2->install(device, QPndman::Enum::Menu);
  if(!h2)
  {
    qDebug() << "ERROR: h2 is null!";
  }

  timespec ts = { 0, 200 * 1000 * 1000 };
  for(int i = 0; i < 100 && h1 && h2; ++i)
  {
    h2->cancel();
    delete h2;
    h2 = toInstall2->install(device, QPndman::Enum::Menu);
    nanosleep(&ts, 0);

    h1->cancel();
    delete h1;
    h1 = toInstall->install(device, QPndman::Enum::Menu);
    nanosleep(&ts, 0);
  }

  qDebug() << "cancel both dowloads";
  if(h1)
  {
    h1->cancel();
    delete h1;
  }

  if(h2)
  {
    h2->cancel();
    delete h2;
  }

  qDebug() << "Waiting for download thread to finish";
  downloadThreadStopMutex.lock();
  qDebug() << "Stop mutex locked";
  downloadThreadFuture.waitForFinished();
  qDebug() << "Download thread finished";
  downloadThreadStopMutex.unlock();

  device->saveRepositories();
  return 0;
}



