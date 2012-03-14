#ifndef DOCUMENTATIONINFO_H
#define DOCUMENTATIONINFO_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class DocumentationInfo : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString type READ getType CONSTANT)
    Q_PROPERTY(QString src READ getSrc CONSTANT)

  public:
    DocumentationInfo(pndman_info const* p, QObject* parent = 0);

    QString getName() const;
    QString getType() const;
    QString getSrc() const;

  private:
    QString name;
    QString type;
    QString src;
  };
}

#endif
