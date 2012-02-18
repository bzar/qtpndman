#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QExplicitlySharedDataPointer>

#include "pndman.h"

namespace QPndman
{
  class Category : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString main READ getMain WRITE setMain NOTIFY mainChanged);
    Q_PROPERTY(QString sub READ getSub WRITE setSub NOTIFY subChanged);

  public:
    Category(pndman_category const* p);
    Category(Category const& other);
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
    struct Data : public QSharedData
    {
      Data(pndman_category const* p);
      QString main;
      QString sub;
    };
    
    QExplicitlySharedDataPointer<Data> d;
  };
}

#endif
