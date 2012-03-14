#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

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
  Q_ENUMS(QPndman::Enum::InstallLocation)

    Q_PROPERTY(QString mount READ getMount CONSTANT)
    Q_PROPERTY(QString device READ getDevice CONSTANT)
    Q_PROPERTY(qint64 size READ getSize CONSTANT)
    Q_PROPERTY(qint64 free READ getFree NOTIFY freeChanged)
    Q_PROPERTY(qint64 available READ getAvailable NOTIFY availableChanged)
    Q_PROPERTY(QString appdata READ getAppdata CONSTANT)

  public:
    static QList<Device*> detectDevices(Context* c, QObject* parent = 0);
    
    Device(Context* c, QString const& path, QObject* parent = 0);
    Device(Context* c, pndman_device* p, QObject* parent = 0);
    ~Device();

    InstallHandle* install(Package* package, Enum::InstallLocation location, bool force = false);
    bool remove(Package* package);
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
    void freeChanged(qint64 newFree);
    void availableChanged(qint64 newAvailable);

  private:
    void setFree(qint64 const& newFree);
    void setAvailable(qint64 const& newAvailable);

    int identifier;
    static int nextIdentifier;

    Context* context;

    pndman_device* pndmanDevice;
    QString mount;
    QString device;
    qint64 size;
    qint64 free;
    qint64 available;
    QString appdata;
  };
}

#endif
