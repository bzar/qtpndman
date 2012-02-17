#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class Category : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString main READ getMain WRITE setMain NOTIFY mainChanged);
    Q_PROPERTY(QString sub READ getSub WRITE setSub NOTIFY subChanged);

  public:
    Category(QString const& main, QString const& sub, QObject* parent = 0);
    Category(Category const& other);
    Category(pndman_category const* p);
    Category& operator=(Category const& other);

  public slots:
    QString getMain() const;
    QString getSub() const;

    void setMain(QString const& main);
    void setSub(QString const& sub);

  signals:
    void mainChanged(QString newMain);
    void subChanged(QString newSub);

  private:
    QString _main;
    QString _sub;

  };
}

#endif
