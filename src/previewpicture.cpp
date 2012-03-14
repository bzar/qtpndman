#include "previewpicture.h"


QPndman::PreviewPicture::PreviewPicture(pndman_previewpic const* p, QObject* parent) : QObject(parent),
  src(p->src)
{
}

QString QPndman::PreviewPicture::getSrc() const
{
  return src;
}
