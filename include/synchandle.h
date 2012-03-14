#ifndef SYNC_HANDLE_H
#define SYNC_HANDLE_H

#include <QObject>
#include "pndman.h"

namespace QPndman
{
  class Repository;
  
  class SyncHandle : public QObject
  {
  Q_OBJECT
  
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged)
    Q_PROPERTY(Repository* repository READ getRepository CONSTANT)
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged)
    Q_PROPERTY(qint64 bytesDownloaded READ getBytesDownloaded NOTIFY bytesDownloadedChanged)
    Q_PROPERTY(qint64 bytesToDownload READ getBytesToDownload NOTIFY bytesToDownloadChanged)

  public:
    SyncHandle(Repository* repository, bool fullSync = false, QObject* parent = 0);
    ~SyncHandle();
    
    pndman_sync_handle* getPndmanSyncHandle();
    
    static int sync();

    QString getError() const;
    Repository* getRepository() const;
    bool getDone() const;
    qint64 getBytesDownloaded() const;
    qint64 getBytesToDownload() const;

  public slots:
    void update();

  signals:
    void errorChanged(QString newError);
    void doneChanged(bool newDone);
    void done();
    void bytesDownloadedChanged(qint64 newBytesDownloaded);
    void bytesToDownloadChanged(qint64 newBytesToDownload);
    
  private:
    void setError(QString const& newError);
    void setDone(bool const& done);
    void setBytesDownloaded(qint64 const value);
    void setBytesToDownload(qint64 const value);

    pndman_sync_handle handle;
    QString error;
    Repository* repository;
    bool _done;
    qint64 bytesDownloaded;
    qint64 bytesToDownload;
  };
}

#endif
