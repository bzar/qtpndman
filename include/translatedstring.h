#ifndef TRANSLATEDSTRING_H
#define TRANSLATEDSTRING_H

#include <QObject>
#include <QSharedPointer>
#include <QMetaType>

#include "pndman.h"

namespace QPndman
{
  class TranslatedString : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged);
    Q_PROPERTY(QString content READ getContent WRITE setContent NOTIFY contentChanged);

  public:
    explicit TranslatedString(QObject* parent = 0);
    TranslatedString(pndman_translated const* p);
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
    struct Data
    {
      Data(pndman_translated const* p);
      QString language;
      QString content;
    };
    
    QSharedPointer<Data> d;
  };
}

Q_DECLARE_METATYPE(QPndman::TranslatedString);

#endif
