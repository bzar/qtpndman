#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class License : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString url READ getUrl CONSTANT)
    Q_PROPERTY(QString sourceCodeUrl READ getSourcecodeurl CONSTANT)

  public:
    License(pndman_license const* p, QObject* parent = 0);

    QString getName() const;
    QString getUrl() const;
    QString getSourcecodeurl() const;

  private:
    QString name;
    QString url;
    QString sourceCodeUrl;
  };
}

#endif
