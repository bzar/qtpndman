#ifndef DOWNLOADHISTORYITEM_H
#define DOWNLOADHISTORYITEM_H

#include <QObject>
#include <QDateTime>
#include "version.h"
#include "pndman.h"

namespace QPndman
{
  class DownloadHistoryItem : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString id READ getId CONSTANT)
    Q_PROPERTY(QDateTime timestamp READ getTimestamp CONSTANT)
    Q_PROPERTY(Version* downloadedVersion READ getDownloadedVersion CONSTANT)
  public:
    DownloadHistoryItem(pndman_api_history_packet const* p, QObject* parent = 0);

    QString getId() const;
    QDateTime getTimestamp() const;
    Version* getDownloadedVersion() const;

  private:
    QString id;
    QDateTime timestamp;
    Version* downloadedVersion;
  };
}

#endif
