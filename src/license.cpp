#include "license.h"

QPndman::License::License(pndman_license const* p, QObject* parent) : QObject(parent),
  name(p->name), url(p->url), sourceCodeUrl(p->sourcecodeurl)
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
