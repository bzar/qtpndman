#ifndef QT_PNDMAN_H
#define QT_PNDMAN_H

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include "repository.h"
#include "device.h"
#include "handle.h"


#include "pndman.h"

namespace QPndman
{
  class Manager : public QObject
  {
    Q_OBJECT
    
  public:
    static Manager* getManager();
    
    ~Manager();
    
  public slots:
    bool addRepository(QString const& url);
    bool removeRepository(QString const& url);
    bool removeAllRepositories();
    QList< QSharedPointer<Repository> > getRepositories();
    
    bool addDevice(QString const& path);
    bool detectDevices();
    bool removeDevice(QString const& path);
    bool removeAllDevices();
    QList< QSharedPointer<Device> > getDevices();
    
    Handle* createHandle(QString const& name);
    bool performHandle(Handle* handle);
    bool removeHandle(Handle* handle);
    
    int download();
    bool sync(Repository* repository);
    int sync(QList<Repository*> const& repositories);
    int syncAll();
  
  signals:
    void repositoriesChanged(QList< QSharedPointer<Repository> >);
    void devicesChanged(QList< QSharedPointer<Device> >);
    void handleCreated(Handle*);
    
  private:
    Manager();
    Manager(const Manager& other);
    Manager& operator=(const Manager& other);
    
    static QScopedPointer<Manager> _manager;
    
    pndman_repository _repositories;
    pndman_device _devices;
  };
}

#endif