#ifndef COMMENT_H
#define COMMENT_H

#include <QObject>
#include <QMetaType>
#include <QDateTime>
#include "version.h"
#include "pndman.h"

namespace QPndman
{
  class Comment : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString username READ getUsername CONSTANT)
    Q_PROPERTY(QString content READ getContent CONSTANT)
    Q_PROPERTY(QDateTime timestamp READ getTimestamp CONSTANT)
    Q_PROPERTY(QPndman::Version* commentedVersion READ getCommentedVersion CONSTANT)
  public:
    Comment(QString const username, QString const content, QDateTime const timestamp, Version* const version, QObject* parent = 0);
    Comment(pndman_api_comment_packet const* p, QObject* parent = 0);

    QString getUsername() const;
    QString getContent() const;
    QDateTime getTimestamp() const;
    Version* getCommentedVersion() const;

  private:
    QString username;
    QString content;
    QDateTime timestamp;
    Version* commentedVersion;
  };
}

#endif
