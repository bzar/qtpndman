#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>
#include <QSharedPointer>
#include "pndman.h"

#include "package.h"
#include "context.h"

#include "enums.h"

namespace QPndman
{
  class Device;
  
  class Handle : public QObject
  {
  Q_OBJECT
  
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged);
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged);
    Q_PROPERTY(bool force READ getForce WRITE setForce NOTIFY forceChanged);
    Q_PROPERTY(Package package READ getPackage NOTIFY packageChanged);
    Q_PROPERTY(Device* device READ getDevice NOTIFY deviceChanged);
    Q_PROPERTY(Operation operation READ getOperation NOTIFY operationChanged);
    Q_PROPERTY(InstallLocation installLocation READ getInstallLocation WRITE setInstallLocation NOTIFY installLocationChanged);
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged);
    Q_PROPERTY(bool cancelled READ getCancelled NOTIFY cancelledChanged);
    Q_PROPERTY(qint64 bytesDownloaded READ getBytesDownloaded NOTIFY bytesDownloadedChanged);
    Q_PROPERTY(qint64 bytesToDownload READ getBytesToDownload NOTIFY bytesToDownloadChanged);

  
  
  public:
    Handle(Context*  context, Operation operation, Package package, Device* device, bool force = false);
    pndman_handle* getPndmanHandle();
    
    static int download();
    
    QString getName() const;
    QString getError() const;
    bool getForce() const;
    Package getPackage() const;
    Device* getDevice() const;
    Operation getOperation() const;
    InstallLocation getInstallLocation() const;
    bool getDone() const;
    bool getCancelled() const;
    qint64 getBytesDownloaded() const;
    qint64 getBytesToDownload() const;

  public slots:
    virtual bool execute() = 0;
    void update();
    bool cancel();

    void setForce(bool const& force);
    void setInstallLocation(InstallLocation const installLocation);

  signals:
    void nameChanged(QString newName);
    void errorChanged(QString newError);
    void forceChanged(bool newForce);
    void packageChanged(Package newPackage);
    void deviceChanged(Device* newDevice);
    void operationChanged(Operation newOperation);
    void installLocationChanged(InstallLocation newInstallLocation);
    void doneChanged(bool newDone);
    void cancelledChanged(bool newCancelled);
    void bytesDownloadedChanged(qint64 newBytesDownloaded);
    void bytesToDownloadChanged(qint64 newBytesToDownload);
    
    void error(QString error);
    void done();
    void executed();
    void cancelled();
    
  protected:
    void updateHandleFlags();

    void setName(QString const& name);
    void setError(QString const& error);
    void setDone(bool const& done);
    void setBytesDownloaded(qint64 const value);
    void setBytesToDownload(qint64 const value);
    
    struct Data
    {
      Data(Context*  context, Operation operation, Package package, Device* device, bool force);
      ~Data();
      Context* context;
      pndman_handle handle;
      QString name;
      QString error;
      bool force;
      Package package;
      Device* device;
      Operation operation;
      InstallLocation installLocation;
      bool done;
      bool cancelled;
      qint64 bytesDownloaded;
      qint64 bytesToDownload;
    };

    QSharedPointer<Data> d;
  };
  
  class InstallHandle : public Handle
  {
    Q_OBJECT
  public:
    InstallHandle(Context* context, Package package, Device* device, InstallLocation const installLocation, bool force = false);
  public slots:
    virtual bool execute();
  };
  
  class RemoveHandle : public Handle
  {
    Q_OBJECT
  public:
    RemoveHandle(Context* context, Package package, Device* device, bool force = false);
  public slots:
    virtual bool execute();
  };

}

#endif
