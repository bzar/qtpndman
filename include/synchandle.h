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
    Q_PROPERTY(QPndman::Repository* repository READ getRepository CONSTANT)
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged)
    Q_PROPERTY(quint64 bytesDownloaded READ getBytesDownloaded NOTIFY bytesDownloadedChanged)
    Q_PROPERTY(quint64 bytesToDownload READ getBytesToDownload NOTIFY bytesToDownloadChanged)

  public:
    SyncHandle(Repository* repository, bool fullSync = false, QObject* parent = 0);
    ~SyncHandle();
    
    pndman_sync_handle* getPndmanSyncHandle();
    
    static void handleCallback(pndman_curl_code code, struct pndman_sync_handle *handle);

    QString getError() const;
    Repository* getRepository() const;
    bool getDone() const;
    quint64 getBytesDownloaded() const;
    quint64 getBytesToDownload() const;

  public slots:
    void update();

  signals:
    void errorChanged(QString newError);
    void doneChanged(bool newDone);
    void done();
    void bytesDownloadedChanged(quint64 newBytesDownloaded);
    void bytesToDownloadChanged(quint64 newBytesToDownload);
    
    void downloadStarted();
    void downloadFinished();

  private:
    void setError(QString const& newError);
    void setDone(bool const& newDone);
    void setBytesDownloaded(quint64 const value);
    void setBytesToDownload(quint64 const value);

    pndman_sync_handle handle;
    QString error;
    Repository* repository;
    bool _done;
    quint64 bytesDownloaded;
    quint64 bytesToDownload;
  };
}

#endif
