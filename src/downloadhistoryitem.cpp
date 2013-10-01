#include "downloadhistoryitem.h"

QPndman::DownloadHistoryItem::DownloadHistoryItem(pndman_api_history_packet const* p, QObject* parent) :
  QObject(parent),
  id(!p->id ? "" : QString::fromUtf8(p->id)),
  timestamp(QDateTime::fromTime_t(p->download_date)),
  downloadedVersion(new Version(p->version, this))
{
}

QString QPndman::DownloadHistoryItem::getId() const
{
  return id;
}

QDateTime QPndman::DownloadHistoryItem::getTimestamp() const
{
  return timestamp;
}

QPndman::Version* QPndman::DownloadHistoryItem::getDownloadedVersion() const
{
  return downloadedVersion;
}

