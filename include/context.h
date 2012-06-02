#ifndef QT_PNDMAN_H
#define QT_PNDMAN_H

#include <QObject>
#include "pndman.h"

namespace QPndman
{
  class Context : public QObject
  {
    Q_OBJECT
    
  public:
    Context(QObject* parent = 0);
    ~Context();
    
    pndman_repository* addPndmanRepository(QString const& url);
    void removePndmanRepository(pndman_repository* repository);
    pndman_repository* getPndmanRepositories();
    pndman_repository* getLastPndmanRepository();
    pndman_repository* getLocalPndmanRepository();
    void clearPndmanRepository(pndman_repository* repository);
    void checkLocalPndmanRepository();
    
    pndman_device* addPndmanDevice(QString const& path);
    void removePndmanDevice(pndman_device* device);
    pndman_device* getPndmanDevices();
    pndman_device* getLastPndmanDevice();
    
    pndman_device* detectPndmanDevices();
    int crawlPndmanDevice(pndman_device* device, bool full = false);
    int crawlAllPndmanDevices(bool full = false);
    bool crawlPndmanPackage(pndman_package* package, bool full = false);

    bool saveRepositories(pndman_device* device);
    bool loadRepository(pndman_repository* repository, pndman_device* device);
    void checkUpgrades();
    
    bool commitHandle(pndman_package_handle* handle);
    
    void setLoggingVerbosity(int level);
    int getLoggingVerbosity() const;

    int processDownload();

  signals:
    void crawlDone(pndman_package *package = 0);

  private:
    pndman_repository* localPndmanRepository;
    pndman_repository* pndmanRepositories;
    pndman_device* pndmanDevices;
  };
}

#endif
