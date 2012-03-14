#ifndef TRANSLATEDSTRING_H
#define TRANSLATEDSTRING_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class TranslatedString : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString language READ getLanguage CONSTANT)
    Q_PROPERTY(QString content READ getContent CONSTANT)

  public:
    TranslatedString(pndman_translated const* p, QObject* parent = 0);

    QString getLanguage() const;
    QString getContent() const;

  private:
    QString language;
    QString content;
  };
}

#endif
