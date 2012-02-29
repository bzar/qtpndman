#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QSharedPointer>
#include <QMetaType>

#include "pndman.h"

namespace QPndman
{
  class Category : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString main READ getMain WRITE setMain NOTIFY mainChanged);
    Q_PROPERTY(QString sub READ getSub WRITE setSub NOTIFY subChanged);

  public:
    explicit Category(QObject* parent = 0);
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
    struct Data
    {
      Data(pndman_category const* p);
      QString main;
      QString sub;
    };
    
    QSharedPointer<Data> d;
  };
}

Q_DECLARE_METATYPE(QPndman::Category);

#endif
