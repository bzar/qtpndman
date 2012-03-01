#ifndef DOCUMENTATIONINFO_H
#define DOCUMENTATIONINFO_H

#include <QObject>
#include <QSharedPointer>
#include <QMetaType>

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
    explicit DocumentationInfo(QObject* parent = 0);
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
    struct Data
    {
      Data(pndman_info const* p);
      QString name;
      QString type;
      QString src;
    };
    
    QSharedPointer<Data> d;
  };
}

Q_DECLARE_METATYPE(QPndman::DocumentationInfo);

#endif
