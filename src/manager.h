#ifndef QT_PNDMAN_H
#define QT_PNDMAN_H

#include <QObject>
#include <QTimer>
#include "repository.h"
#include "device.h"
#include "handle.h"
#include "synchandle.h"


#include "pndman.h"

namespace QPndman
{
  class Manager : public QObject
  {
    Q_OBJECT
    
  public:
    static Manager* getManager();
    
    Manager(const Manager& other);
    ~Manager();
    
  public slots:
    bool addRepository(QString const& url);
    bool removeRepository(QString const& url);
    bool removeAllRepositories();
    QList<Repository> getRepositories();
    
    bool addDevice(QString const& path);
    bool detectDevices();
    bool removeDevice(QString const& path);
    bool removeAllDevices();
    QList<Device> getDevices();
    
    Handle createHandle(QString const& name);
    
    int download();
    SyncHandle sync(Repository repository);
    QList<SyncHandle> sync(QList<Repository> const& repositories);
    QList<SyncHandle> syncAll();
    bool currentlySyncing() const;
  
  signals:
    void repositoriesChanged(QList<Repository>);
    void devicesChanged(QList<Device>);
    void handleCreated(Handle);
    
    void syncStarted(SyncHandle);
    void syncFinished();
    void syncError();
    
  private slots:
    void continueSyncing();
    
  private:
    Manager();
    Manager& operator=(const Manager& other);
        
    struct Data : public QSharedData
    {
      Data();
      pndman_repository repositories;
      pndman_device devices;
      
      QTimer syncTimer;
    };

    QExplicitlySharedDataPointer<Data> d;
    
  };
}

#endif