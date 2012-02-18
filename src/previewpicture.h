#ifndef PREVIEWPICTURE_H
#define PREVIEWPICTURE_H

#include <QObject>
#include <QExplicitlySharedDataPointer>
#include "pndman.h"

namespace QPndman
{
  class PreviewPicture : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString src READ getSrc WRITE setSrc NOTIFY srcChanged);

  public:
    PreviewPicture(pndman_previewpic const* p);
    PreviewPicture(PreviewPicture const& other);
    PreviewPicture& operator=(PreviewPicture const& other);

  public slots:
    QString getSrc() const;

    void setSrc(QString const& src);

  signals:
    void srcChanged(QString newSrc);

  private:
    struct Data : public QSharedData
    {
      Data(pndman_previewpic const* p);
      QString src;
    };
    
    QExplicitlySharedDataPointer<Data> d;
  };
}

#endif
