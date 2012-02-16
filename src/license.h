#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>

namespace QPndman
{
  class License : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged);
    Q_PROPERTY(QString sourceCodeUrl READ getSourcecodeurl WRITE setSourcecodeurl NOTIFY sourceCodeUrlChanged);

  public:
    License(QString const& name, QString const& url, QString const& sourceCodeUrl, QObject* parent = 0);
    License(License const& other);
    License& operator=(License const& other);

  public slots:
    QString getName() const;
    QString getUrl() const;
    QString getSourcecodeurl() const;

    void setName(QString const& name);
    void setUrl(QString const& url);
    void setSourcecodeurl(QString const& sourceCodeUrl);

  signals:
    void nameChanged(QString newName);
    void urlChanged(QString newUrl);
    void sourceCodeUrlChanged(QString newSourcecodeurl);

  private:
    QString _name;
    QString _url;
    QString _sourceCodeUrl;

  };
}

#endif
