#include "previewpicture.h"

QPndman::PreviewPicture::PreviewPicture(QObject* parent): QObject(parent)
{

}

QPndman::PreviewPicture::PreviewPicture(pndman_previewpic const* p) : QObject(0), d(new Data(p))
{
}

QPndman::PreviewPicture::Data::Data(pndman_previewpic const* p) :
  src(p->src)
{
  
}
QPndman::PreviewPicture::PreviewPicture(PreviewPicture const& other) : QObject(0), d(other.d)
{
}

QPndman::PreviewPicture& QPndman::PreviewPicture::operator=(PreviewPicture const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::PreviewPicture::getSrc() const
{
  return d->src;
}

void QPndman::PreviewPicture::setSrc(QString const& src)
{
  if(src != d->src) 
  {
    d->src = src; 
    emit srcChanged(d->src);
  }
}
