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
    
    Handle install(Package package, Device device, Handle::InstallLocation location);
    Handle remove(Package package, Device device);
    
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
    void syncing();
    void syncFinished();
    void syncError();
    void syncError(SyncHandle);
    
  private slots:
    void continueSyncing();
    void cleanUp();
    
  private:
    struct Data : public QSharedData
    {
      Data();
      pndman_repository repositories;
      pndman_device devices;
      
      QList<Handle> handles;
      QList<SyncHandle> syncHandles;
      
      QTimer syncTimer;
      QTimer cleanTimer;
    };

    Manager();
    Manager& operator=(const Manager& other);
    
    bool initSyncHandle(SyncHandle& handle, pndman_repository* r);
    
    QExplicitlySharedDataPointer<Data> d;
    
  };
}

#endif