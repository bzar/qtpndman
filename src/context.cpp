#include "context.h"
#include "util.h"

#include <QDebug>

QPndman::Context::Context(QObject* parent) : QObject(parent),
  localPndmanRepository(0), pndmanRepositories(0), pndmanDevices(0)
{
  setLoggingVerbosity(1);
  localPndmanRepository = pndman_repository_init();
  pndmanRepositories = localPndmanRepository;
}

QPndman::Context::~Context()
{
  pndman_repository_free_all(pndmanRepositories);
  pndman_device_free_all(pndmanDevices);
  pndmanRepositories = 0;
  pndmanDevices = 0;
  localPndmanRepository = 0;
}

pndman_repository* QPndman::Context::addPndmanRepository(QString const& url)
{
  return pndman_repository_add(url.toLocal8Bit().data(), pndmanRepositories);
}

void QPndman::Context::removePndmanRepository(pndman_repository* repository)
{
  for(pndman_repository* r = pndmanRepositories; r; r = r->next)
  {
    if(r == repository)
    {
      pndmanRepositories = pndman_repository_free(repository);
      break;
    }
  }
}

pndman_repository* QPndman::Context::getPndmanRepositories()
{
  return pndmanRepositories;
}

pndman_repository* QPndman::Context::getLastPndmanRepository()
{
  return getLast(pndmanRepositories);
}

pndman_repository* QPndman::Context::getLocalPndmanRepository()
{
  return localPndmanRepository;
}

void QPndman::Context::clearPndmanRepository(pndman_repository* repository)
{
  pndman_repository_clear(repository);
}

void QPndman::Context::checkLocalPndmanRepository()
{
  pndman_repository_check_local(localPndmanRepository);
}


pndman_device* QPndman::Context::addPndmanDevice(QString const& path)
{
  pndman_device* device = pndman_device_add(path.toLocal8Bit().data(), pndmanDevices);
  if(!pndmanDevices)
  {
    pndmanDevices = device;
  }
  
  return device;
}

void QPndman::Context::removePndmanDevice(pndman_device* device)
{
  for(pndman_device* dev = pndmanDevices; dev; dev = dev->next)
  {
    if(dev == device)
    {
      pndmanDevices = pndman_device_free(device);
      break;
    }
  }
}

pndman_device* QPndman::Context::getPndmanDevices()
{
  return pndmanDevices;
}

pndman_device* QPndman::Context::getLastPndmanDevice()
{
  return getLast(pndmanDevices);
}

pndman_device* QPndman::Context::detectPndmanDevices()
{
  pndman_device* detected = pndman_device_detect(pndmanDevices);
  if(!pndmanDevices)
  {
    pndmanDevices = detected;
  }
  return detected;
}

bool QPndman::Context::crawlPndmanDevice(pndman_device* device, bool full)
{
  return pndman_package_crawl(full ? 1 : 0, device, localPndmanRepository) == 0;
}

bool QPndman::Context::crawlPndmanPackage(pndman_package *package, bool full)
{
  return pndman_package_crawl_single_package(full ? 1 : 0, package) == 0;
}

bool QPndman::Context::saveRepositories(pndman_device* device)
{
  return pndman_repository_commit_all(pndmanRepositories, device) == 0;
}

bool QPndman::Context::loadRepository(pndman_repository* repository, pndman_device* device)
{
  return pndman_device_read_repository(repository, device) == 0;
}

bool QPndman::Context::commitHandle(pndman_package_handle *handle)
{
  return pndman_package_handle_commit(handle, localPndmanRepository) == 0;
}

void QPndman::Context::setLoggingVerbosity(int level)
{
  pndman_set_verbose(level);
}

int QPndman::Context::getLoggingVerbosity() const
{
  return pndman_get_verbose();
}

int QPndman::Context::processDownload()
{
  return pndman_curl_process();
}

void QPndman::Context::checkUpgrades()
{
  pndman_repository_check_updates(pndmanRepositories);
}
