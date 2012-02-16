#ifndef PREVIEWPICTURE_H
#define PREVIEWPICTURE_H

#include <QObject>

namespace QPndman
{
  class PreviewPicture : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString src READ getSrc WRITE setSrc NOTIFY srcChanged);

  public:
    PreviewPicture(QString const& src, QObject* parent = 0);
    PreviewPicture(PreviewPicture const& other);
    PreviewPicture& operator=(PreviewPicture const& other);

  public slots:
    QString getSrc() const;

    void setSrc(QString const& src);

  signals:
    void srcChanged(QString newSrc);

  private:
    QString _src;

  };
}

#endif
