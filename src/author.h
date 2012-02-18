#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include <QSharedPointer>

#include "pndman.h"

namespace QPndman
{
  class Author : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString website READ getWebsite WRITE setWebsite NOTIFY websiteChanged);

  public:
    Author(pndman_author const* p);
    Author(Author const& other);
    Author& operator=(Author const& other);

  public slots:
    QString getName() const;
    QString getWebsite() const;

    void setName(QString const& name);
    void setWebsite(QString const& website);

  signals:
    void nameChanged(QString newName);
    void websiteChanged(QString newWebsite);

  private:
    struct Data
    {
      Data(pndman_author const* p);
      QString name;
      QString website;
    };
    
    QSharedPointer<Data> d;
  };
}

#endif
