#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

namespace QPndman
{
  class Device : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString mount READ getMount WRITE setMount NOTIFY mountChanged);
    Q_PROPERTY(QString device READ getDevice WRITE setDevice NOTIFY deviceChanged);
    Q_PROPERTY(qint64 size READ getSize WRITE setSize NOTIFY sizeChanged);
    Q_PROPERTY(qint64 free READ getFree WRITE setFree NOTIFY freeChanged);
    Q_PROPERTY(qint64 available READ getAvailable WRITE setAvailable NOTIFY availableChanged);
    Q_PROPERTY(QString appdata READ getAppdata WRITE setAppdata NOTIFY appdataChanged);

  public:
    Device(QString const& mount, QString const& device, qint64 const& size, qint64 const& free, qint64 const& available, QString const& appdata, QObject* parent = 0);
    Device(Device const& other);
    Device& operator=(Device const& other);

  public slots:
    QString getMount() const;
    QString getDevice() const;
    qint64 getSize() const;
    qint64 getFree() const;
    qint64 getAvailable() const;
    QString getAppdata() const;

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
    QString _mount;
    QString _device;
    qint64 _size;
    qint64 _free;
    qint64 _available;
    QString _appdata;

  };
}

#endif
