#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class Association : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString fileType READ getFiletype CONSTANT)
    Q_PROPERTY(QString exec READ getExec CONSTANT)

  public:
    Association(pndman_association const* p, QObject* parent = 0);

    QString getName() const;
    QString getFiletype() const;
    QString getExec() const;


  private:
    QString name;
    QString fileType;
    QString exec;
  };
}

#endif
