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
    Repository addRepository(QString const& url);
    bool removeRepository(Repository repository);
    bool removeAllRepositories();
    QList<Repository> getRepositories();
    
    Device addDevice(QString const& path);
    QList<QPndman::Device> detectDevices();
    bool removeDevice(Device device);
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
    void repositoriesChanged();
    void devicesChanged();
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
    struct Data
    {
      Data();
      pndman_repository pndmanRepositories;
      pndman_device pndmanDevices;
      
      QList<Handle> handles;
      QList<SyncHandle> syncHandles;
      
      QList<Repository> repositories;
      QList<Device> devices;
      
      QTimer syncTimer;
      QTimer cleanTimer;
    };

    Manager();
    Manager& operator=(const Manager& other);
    
    bool initSyncHandle(SyncHandle& handle, Repository repository);
    
    QSharedPointer<Data> d;
    
  };
}

#endif