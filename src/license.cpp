#include "license.h"

QPndman::License::License(pndman_license const* p) : QObject(0), d(new Data(p))
{
  
}
QPndman::License::Data::Data(pndman_license const* p) :
  name(p->name), url(p->url), sourceCodeUrl(p->sourcecodeurl)
{
}

QPndman::License::License(License const& other) : QObject(0), d(other.d)
{
}

QPndman::License& QPndman::License::operator=(License const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::License::getName() const
{
  return d->name;
}
QString QPndman::License::getUrl() const
{
  return d->url;
}
QString QPndman::License::getSourcecodeurl() const
{
  return d->sourceCodeUrl;
}

void QPndman::License::setName(QString const& name)
{
  if(name != d->name) 
  {
    d->name = name; 
    emit nameChanged(d->name);
  }
}
void QPndman::License::setUrl(QString const& url)
{
  if(url != d->url) 
  {
    d->url = url; 
    emit urlChanged(d->url);
  }
}
void QPndman::License::setSourcecodeurl(QString const& sourceCodeUrl)
{
  if(sourceCodeUrl != d->sourceCodeUrl) 
  {
    d->sourceCodeUrl = sourceCodeUrl; 
    emit sourceCodeUrlChanged(d->sourceCodeUrl);
  }
}
