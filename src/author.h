#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>

namespace QPndman
{
  class Author : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString website READ getWebsite WRITE setWebsite NOTIFY websiteChanged);

  public:
    Author(QString const& name, QString const& website, QObject* parent = 0);
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
    QString _name;
    QString _website;

  };
}

#endif
