#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>
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
  
    Q_ENUMS(QPndman::Enum::Operation QPndman::Enum::InstallLocation)

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged)
    Q_PROPERTY(bool force READ getForce CONSTANT)
    Q_PROPERTY(QPndman::Package* package READ getPackage CONSTANT)
    Q_PROPERTY(QPndman::Device* device READ getDevice CONSTANT)
    Q_PROPERTY(QPndman::Enum::Operation operation READ getOperation CONSTANT)
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged)
    Q_PROPERTY(bool cancelled READ getCancelled NOTIFY cancelledChanged)
    Q_PROPERTY(qint64 bytesDownloaded READ getBytesDownloaded NOTIFY bytesDownloadedChanged)
    Q_PROPERTY(qint64 bytesToDownload READ getBytesToDownload NOTIFY bytesToDownloadChanged)

  
  public:
    Handle(Context*  context, Enum::Operation operation, Package* package, Device* device, bool force = false, QObject* parent = 0);
    ~Handle();
    pndman_package_handle* getPndmanHandle();
    
    static void handleCallback(pndman_curl_code code, pndman_package_handle* handle);
    
    QString getName() const;
    QString getError() const;
    bool getForce() const;
    Package* getPackage() const;
    Device* getDevice() const;
    Enum::Operation getOperation() const;
    bool getDone() const;
    bool getCancelled() const;
    qint64 getBytesDownloaded() const;
    qint64 getBytesToDownload() const;

  public slots:
    virtual bool execute() = 0;
    void update();
    void cancel();

  signals:
    void errorChanged(QString newError);
    void doneChanged(bool newDone);
    void cancelledChanged(bool newCancelled);
    void bytesDownloadedChanged(qint64 newBytesDownloaded);
    void bytesToDownloadChanged(qint64 newBytesToDownload);
    
    void error(QString const error);
    void done();
    void executed();
    void cancelled();
    
  protected:
    void updateHandleFlags();

    void setError(QString const& error);
    void setDone(bool const& done);
    void setBytesDownloaded(qint64 const value);
    void setBytesToDownload(qint64 const value);
    
    Context* context;
    pndman_package_handle handle;
    QString name;
    QString _error;
    bool force;
    Package* package;
    Device* device;
    Enum::Operation operation;
    bool _done;
    bool _cancelled;
    qint64 bytesDownloaded;
    qint64 bytesToDownload;
  };
  
  class InstallHandle : public Handle
  {
    Q_OBJECT
    Q_PROPERTY(QPndman::Enum::InstallLocation installLocation READ getInstallLocation CONSTANT)

  public:
    InstallHandle(Context* context, Package* package, Device* device, Enum::InstallLocation const installLocation, bool force = false, QObject* parent = 0);
    Enum::InstallLocation getInstallLocation() const;
  public slots:
    virtual bool execute();    
  private:
    Enum::InstallLocation installLocation;
  };
  
  class UpgradeHandle : public Handle
  {
    Q_OBJECT
  public:
    UpgradeHandle(Context* context, Package* package, bool force = false, QObject* parent = 0);
  public slots:
    virtual bool execute();
  };
  
  class RemoveHandle : public Handle
  {
    Q_OBJECT
  public:
    RemoveHandle(Context* context, Package* package, Device* device, bool force = false, QObject* parent = 0);
  public slots:
    virtual bool execute();
  };
}

#endif
