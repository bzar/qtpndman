#ifndef QT_PNDMAN_H
#define QT_PNDMAN_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include "pndman.h"

namespace QPndman
{
  class Context : public QObject
  {
    Q_OBJECT
    
  public:
    Context();
    Context& operator=(const Context& other);
    Context(const Context& other);
    ~Context();
    
    pndman_repository* addPndmanRepository(QString const& url);
    void removePndmanRepository(pndman_repository* repository);
    pndman_repository* getPndmanRepositories();
    pndman_repository* getLastPndmanRepository();
    pndman_repository* getLocalPndmanRepository();

    pndman_device* addPndmanDevice(QString const& path);
    void removePndmanDevice(pndman_device* device);
    pndman_device* getPndmanDevices();
    pndman_device* getLastPndmanDevice();
    
    pndman_device* detectPndmanDevices();
    bool crawlPndmanDevice(pndman_device* device);
    
    bool saveRepositories(pndman_device* device);
    bool loadRepository(pndman_repository* repository, pndman_device* device);
    
  private:
    struct Data
    {
      Data();
      ~Data();
      pndman_repository* localPndmanRepository;
      pndman_repository* pndmanRepositories;
      pndman_device* pndmanDevices;
    };
        
    QSharedPointer<Data> d;
  };
    
}

#endif