#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSharedPointer>

#include "pndman.h"
#include "context.h"
#include "handle.h"
#include "enums.h"

namespace QPndman
{
  
  class Device : public QObject
  {
  Q_OBJECT
  Q_ENUMS(Operation InstallLocation)

    Q_PROPERTY(QString mount READ getMount WRITE setMount NOTIFY mountChanged);
    Q_PROPERTY(QString device READ getDevice WRITE setDevice NOTIFY deviceChanged);
    Q_PROPERTY(qint64 size READ getSize WRITE setSize NOTIFY sizeChanged);
    Q_PROPERTY(qint64 free READ getFree WRITE setFree NOTIFY freeChanged);
    Q_PROPERTY(qint64 available READ getAvailable WRITE setAvailable NOTIFY availableChanged);
    Q_PROPERTY(QString appdata READ getAppdata WRITE setAppdata NOTIFY appdataChanged);

  public:

    static QList<Device*> detectDevices(Context& c, QObject* parent = 0);
    
    Device(Context& c, QString const& path, QObject* parent = 0);
    Device(pndman_device* p, QObject* parent = 0);
    
    Handle* install(Package package, InstallLocation location);
    Handle* remove(Package package);
    
    pndman_device* getPndmanDevice() const;
    bool isNull() const;
    int getIdentifier() const;
    
    QString getMount() const;
    QString getDevice() const;
    qint64 getSize() const;
    qint64 getFree() const;
    qint64 getAvailable() const;
    QString getAppdata() const;

  public slots:
    void update();
    void setMount(QString const& mount);
    void setDevice(QString const& device);
    void setSize(qint64 const& size);
    void setFree(qint64 const& free);
    void setAvailable(qint64 const& available);
    void setAppdata(QString const& appdata);

  signals:
    void mountChanged(QString newMount);
    void deviceChanged(QString newDevice);
    void sizeChanged(qint64 newSize);
    void freeChanged(qint64 newFree);
    void availableChanged(qint64 newAvailable);
    void appdataChanged(QString newAppdata);

  private:
    struct Data
    {
      Data(pndman_device* p);
      ~Data();
      
      int identifier;
      pndman_device* pndmanDevice;
      QString mount;
      QString device;
      qint64 size;
      qint64 free;
      qint64 available;
      QString appdata;
      
      static int nextIdentifier;
    };

    QSharedPointer<Data> d;
  };
}

#endif
