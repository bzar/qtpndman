#include "previewpicture.h"

QPndman::PreviewPicture::PreviewPicture(QString const& src, QObject* parent) : QObject(parent), 
  _src(src)
{
}

QPndman::PreviewPicture::PreviewPicture(pndman_previewpic const* p) : QObject(0), 
  _src(p->src)
{
}

QPndman::PreviewPicture::PreviewPicture(PreviewPicture const& other) : QObject(0), 
  _src(other._src)
{
}

QPndman::PreviewPicture& QPndman::PreviewPicture::operator=(PreviewPicture const& other)
{
  if(&other == this)
    return *this;
  
  _src = other._src;
  
  return *this;
}

QString QPndman::PreviewPicture::getSrc() const
{
  return _src;
}

void QPndman::PreviewPicture::setSrc(QString const& src)
{
  if(src != _src) 
  {
    _src = src; 
    emit srcChanged(_src);
  }
}
