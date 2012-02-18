#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>
#include <QExplicitlySharedDataPointer>
#include "pndman.h"

#include "package.h"
#include "device.h"

namespace QPndman
{
  class Handle : public QObject
  {
  Q_OBJECT
  Q_ENUMS(Operation InstallLocation)
  
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged);
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged);
    Q_PROPERTY(bool force READ getForce WRITE setForce NOTIFY forceChanged);
    Q_PROPERTY(Package package READ getPackage WRITE setPackage NOTIFY packageChanged);
    Q_PROPERTY(Device device READ getDevice WRITE setDevice NOTIFY deviceChanged);
    Q_PROPERTY(Operation operation READ getOperation WRITE setOperation NOTIFY operationChanged);
    Q_PROPERTY(InstallLocation installLocation READ getInstallLocation WRITE setInstallLocation NOTIFY installLocationChanged);
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged);
    Q_PROPERTY(bool cancelled READ getCancelled NOTIFY cancelledChanged);

  
  
  public:
    enum Operation { Install, Remove };
    enum InstallLocation { Desktop, Menu, DesktopAndMenu };
    
    Handle();
    Handle(Handle const& other);
    Handle& operator=(Handle const& other);

    pndman_handle* getPndmanHandle();
    
  public slots:
    bool execute();
    void update();
    bool cancel();

    QString getName() const;
    QString getError() const;
    bool getForce() const;
    Package getPackage() const;
    Device getDevice() const;
    Operation getOperation() const;
    InstallLocation getInstallLocation() const;
    bool getDone() const;
    bool getCancelled() const;

    void setForce(bool const& force);
    void setPackage(Package package);
    void setDevice(Device device);
    void setOperation(Operation const operation);
    void setInstallLocation(InstallLocation const installLocation);

  signals:
    void nameChanged(QString newName);
    void errorChanged(QString newError);
    void forceChanged(bool newForce);
    void packageChanged(Package newPackage);
    void deviceChanged(Device newDevice);
    void operationChanged(Operation newOperation);
    void installLocationChanged(InstallLocation newInstallLocation);
    void doneChanged(bool newDone);
    void cancelledChanged(bool newCancelled);
    
    void error(QString error);
    void done();
    void executed();
    void cancelled();
    
  private:
    void updateHandleFlags();

    void setName(QString const& name);
    void setError(QString const& error);
    void setDone(bool const& done);

    struct Data : public QSharedData
    {
      Data();
      pndman_handle handle;
      QString name;
      QString error;
      bool force;
      Package package;
      Device device;
      Operation operation;
      InstallLocation installLocation;
      bool done;
      bool cancelled;
    };

    QExplicitlySharedDataPointer<Data> d;
  };
}

#endif
