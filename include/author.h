#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include "pndman.h"

namespace QPndman
{
  class Author : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString website READ getWebsite CONSTANT)

  public:
    Author(pndman_author const* p, QObject* parent = 0);

    QString getName() const;
    QString getWebsite() const;

  private:
    QString name;
    QString website;
  };
}

#endif
