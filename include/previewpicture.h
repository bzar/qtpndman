#ifndef PREVIEWPICTURE_H
#define PREVIEWPICTURE_H

#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include "pndman.h"

namespace QPndman
{
  class PreviewPicture : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString src READ getSrc WRITE setSrc NOTIFY srcChanged);

  public:
    explicit PreviewPicture(QObject* parent = 0);
    PreviewPicture(pndman_previewpic const* p);
    PreviewPicture(PreviewPicture const& other);
    PreviewPicture& operator=(PreviewPicture const& other);

  public slots:
    QString getSrc() const;

    void setSrc(QString const& src);

  signals:
    void srcChanged(QString newSrc);

  private:
    struct Data
    {
      Data(pndman_previewpic const* p);
      QString src;
    };
    
    QSharedPointer<Data> d;
  };
}

Q_DECLARE_METATYPE(QPndman::PreviewPicture);

#endif
