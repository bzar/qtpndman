#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSharedPointer>
#include <QMetaType>

#include "pndman.h"
#include "context.h"
#include "handle.h"
#include "enums.h"

namespace QPndman
{
  class Repository;
  
  class Device : public QObject
  {
  Q_OBJECT
  Q_ENUMS(Operation InstallLocation)

    Q_PROPERTY(QString mount READ getMount NOTIFY mountChanged);
    Q_PROPERTY(QString device READ getDevice NOTIFY deviceChanged);
    Q_PROPERTY(qint64 size READ getSize NOTIFY sizeChanged);
    Q_PROPERTY(qint64 free READ getFree NOTIFY freeChanged);
    Q_PROPERTY(qint64 available READ getAvailable NOTIFY availableChanged);
    Q_PROPERTY(QString appdata READ getAppdata NOTIFY appdataChanged);

  public:
    static QList<Device*> detectDevices(Context* c, QObject* parent = 0);
    
    explicit Device(QObject* parent = 0);
    Device(Device const& other);
    Device(Context* c, QString const& path, QObject* parent = 0);
    Device(Context* c, pndman_device* p, QObject* parent = 0);
    
    InstallHandle* install(Package package, InstallLocation location, bool force = false);
    bool remove(Package package);
    bool crawl(bool full = false);
    bool saveRepositories();
    bool loadRepository(Repository* repository);
    
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

  signals:
    void mountChanged(QString newMount);
    void deviceChanged(QString newDevice);
    void sizeChanged(qint64 newSize);
    void freeChanged(qint64 newFree);
    void availableChanged(qint64 newAvailable);
    void appdataChanged(QString newAppdata);

  private:
    void setMount(QString const& mount);
    void setDevice(QString const& device);
    void setSize(qint64 const& size);
    void setFree(qint64 const& free);
    void setAvailable(qint64 const& available);
    void setAppdata(QString const& appdata);

    struct Data
    {
      Data(Context* c, pndman_device* p);
      ~Data();
      
      int identifier;
      Context* context;

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

Q_DECLARE_METATYPE(QPndman::Device);

#endif
