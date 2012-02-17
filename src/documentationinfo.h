#ifndef DOCUMENTATIONINFO_H
#define DOCUMENTATIONINFO_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class DocumentationInfo : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged);
    Q_PROPERTY(QString src READ getSrc WRITE setSrc NOTIFY srcChanged);

  public:
    DocumentationInfo(QString const& name, QString const& type, QString const& src, QObject* parent = 0);
    DocumentationInfo(pndman_info const* p);
    DocumentationInfo(DocumentationInfo const& other);
    DocumentationInfo& operator=(DocumentationInfo const& other);

  public slots:
    QString getName() const;
    QString getType() const;
    QString getSrc() const;

    void setName(QString const& name);
    void setType(QString const& type);
    void setSrc(QString const& src);

  signals:
    void nameChanged(QString newName);
    void typeChanged(QString newType);
    void srcChanged(QString newSrc);

  private:
    QString _name;
    QString _type;
    QString _src;

  };
}

#endif
