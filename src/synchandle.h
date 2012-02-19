#ifndef SYNC_HANDLE_H
#define SYNC_HANDLE_H

#include <QObject>
#include <QSharedPointer>
#include "pndman.h"

namespace QPndman
{
  class Repository;
  
  class SyncHandle : public QObject
  {
  Q_OBJECT
  
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged);
    Q_PROPERTY(Repository* repository READ getRepository NOTIFY repositoryChanged);
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged);

  public:
    SyncHandle(Repository* repository);
    
    pndman_sync_handle* getPndmanSyncHandle();
    
    static int sync();


  public slots:
    void update();
    QString getError() const;
    Repository* getRepository() const;
    bool getDone() const;

  signals:
    void errorChanged(QString newError);
    void repositoryChanged(Repository* newRepository);
    void doneChanged(bool newDone);
    void done();
    
  private:
    void setError(QString const& error);
    void setDone(bool const& done);

    struct Data
    {
      Data(Repository* repository);
      ~Data();
      pndman_sync_handle handle;
      QString error;
      Repository* repository;
      bool done;
    };

    QSharedPointer<Data> d;
  };
}

#endif
