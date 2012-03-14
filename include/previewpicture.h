#ifndef PREVIEWPICTURE_H
#define PREVIEWPICTURE_H

#include <QObject>
#include "pndman.h"

namespace QPndman
{
  class PreviewPicture : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString src READ getSrc CONSTANT)

  public:
    explicit PreviewPicture();
    PreviewPicture(pndman_previewpic const* p, QObject* parent = 0);

    QString getSrc() const;

  private:
    QString src;
  };
}

#endif
