#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class Category : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString main READ getMain CONSTANT)
    Q_PROPERTY(QString sub READ getSub CONSTANT)

  public:
    Category(pndman_category const* p, QObject* parent = 0);

    QString getMain() const;
    QString getSub() const;

  private:
    QString main;
    QString sub;
  };
}

#endif
