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
    Q_PROPERTY(quint64 size READ getSize CONSTANT)
    Q_PROPERTY(quint64 free READ getFree NOTIFY freeChanged)
    Q_PROPERTY(quint64 available READ getAvailable NOTIFY availableChanged)
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
    bool loadRepository(Repository* repository, bool autoUpdate = true);
    
    pndman_device* getPndmanDevice() const;
    bool isNull() const;
    int getIdentifier() const;
    
    QString getMount() const;
    quint64 getSize() const;
    quint64 getFree() const;
    quint64 getAvailable() const;
    QString getAppdata() const;

  public slots:
    void update();

  signals:
    void freeChanged(quint64 newFree);
    void availableChanged(quint64 newAvailable);

  private:
    void setFree(quint64 const& newFree);
    void setAvailable(quint64 const& newAvailable);

    int identifier;
    static int nextIdentifier;

    Context* context;

    pndman_device* pndmanDevice;
    QString mount;
    quint64 size;
    quint64 free;
    quint64 available;
    QString appdata;
  };
}

#endif
