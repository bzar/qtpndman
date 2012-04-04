#include "license.h"

QPndman::License::License(pndman_license const* p, QObject* parent) : QObject(parent),
  name(QString::fromUtf8(p->name)), url(QString::fromUtf8(p->url)), sourceCodeUrl(QString::fromUtf8(p->sourcecodeurl))
{
  
}

QString QPndman::License::getName() const
{
  return name;
}
QString QPndman::License::getUrl() const
{
  return url;
}
QString QPndman::License::getSourcecodeurl() const
{
  return sourceCodeUrl;
}
