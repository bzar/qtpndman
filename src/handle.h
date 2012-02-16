#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>
#include "pndman.h"

namespace QPndman
{
  class Handle : public QObject
  {
  Q_OBJECT
  Q_ENUMS(Operation InstallLocation)
  
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged);
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged);
    Q_PROPERTY(bool force READ getForce WRITE setForce NOTIFY forceChanged);
    Q_PROPERTY(Operation operation READ getOperation WRITE setOperation NOTIFY operationChanged);
    Q_PROPERTY(InstallLocation installLocation READ getInstallLocation WRITE setInstallLocation NOTIFY installLocationChanged);
    Q_PROPERTY(bool done READ getDone NOTIFY doneChanged);

  
  
  public:
    enum Operation { Install, Remove };
    enum InstallLocation { Desktop, Menu, DesktopAndMenu };
    
    Handle();

    pndman_handle* getPndmanHandle();
    void update();
    
  public slots:
    QString getName() const;
    QString getError() const;
    bool getForce() const;
    Operation getOperation() const;
    InstallLocation getInstallLocation() const;
    bool getDone() const;

    void setForce(bool const& force);
    void setOperation(Operation const operation);
    void setInstallLocation(InstallLocation const installLocation);

  signals:
    void nameChanged(QString newName);
    void errorChanged(QString newError);
    void forceChanged(bool newForce);
    void operationChanged(Operation newOperation);
    void installLocationChanged(InstallLocation newInstallLocation);
    
    void doneChanged(bool newDone);
    void done();
    
  private:
    void updateHandleFlags();

    void setName(QString const& name);
    void setError(QString const& error);
    void setDone(bool const& done);

    pndman_handle _handle;
    QString _name;
    QString _error;
    bool _force;
    Operation _operation;
    InstallLocation _installLocation;
    bool _done;

  };
}

#endif
