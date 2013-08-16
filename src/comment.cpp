#include "comment.h"

QPndman::Comment::Comment(const QString username, const QString content, const QDateTime timestamp, QPndman::Version* const version, QObject* parent) :
  QObject(parent),
  username(username),
  content(content),
  timestamp(timestamp),
  commentedVersion(version)
{
  version->setParent(this);
}

QPndman::Comment::Comment(pndman_api_comment_packet const* p, QObject* parent) :
  QObject(parent),
  username(QString::fromUtf8(p->username)),
  content(QString::fromUtf8(p->comment)),
  timestamp(QDateTime::fromTime_t(p->date)),
  commentedVersion(new Version(p->version, this))
{
}

QString QPndman::Comment::getUsername() const
{
  return username;
}

QString QPndman::Comment::getContent() const
{
  return content;
}

QDateTime QPndman::Comment::getTimestamp() const
{
  return timestamp;
}

QPndman::Version* QPndman::Comment::getCommentedVersion() const
{
  return commentedVersion;
}

