#ifndef TRANSLATEDSTRING_H
#define TRANSLATEDSTRING_H

#include <QObject>

namespace QPndman
{
  class TranslatedString : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged);
    Q_PROPERTY(QString content READ getContent WRITE setContent NOTIFY contentChanged);

  public:
    TranslatedString(QString const& language, QString const& content, QObject* parent = 0);
    TranslatedString(TranslatedString const& other);
    TranslatedString& operator=(TranslatedString const& other);

  public slots:
    QString getLanguage() const;
    QString getContent() const;

    void setLanguage(QString const& language);
    void setContent(QString const& content);

  signals:
    void languageChanged(QString newLanguage);
    void contentChanged(QString newContent);

  private:
    QString _language;
    QString _content;

  };
}

#endif
