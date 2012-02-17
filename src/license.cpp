#include "license.h"

QPndman::License::License(QString const& name, QString const& url, QString const& sourceCodeUrl, QObject* parent) : QObject(parent), 
  _name(name), _url(url), _sourceCodeUrl(sourceCodeUrl)
{
}

QPndman::License::License(pndman_license const* p) : QObject(0), 
  _name(p->name), _url(p->url), _sourceCodeUrl(p->sourcecodeurl)
{
}

QPndman::License::License(License const& other) : QObject(0), 
  _name(other._name), _url(other._url), _sourceCodeUrl(other._sourceCodeUrl)
{
}

QPndman::License& QPndman::License::operator=(License const& other)
{
  if(&other == this)
    return *this;
  
  _name = other._name;
  _url = other._url;
  _sourceCodeUrl = other._sourceCodeUrl;
  
  return *this;
}

QString QPndman::License::getName() const
{
  return _name;
}
QString QPndman::License::getUrl() const
{
  return _url;
}
QString QPndman::License::getSourcecodeurl() const
{
  return _sourceCodeUrl;
}

void QPndman::License::setName(QString const& name)
{
  if(name != _name) 
  {
    _name = name; 
    emit nameChanged(_name);
  }
}
void QPndman::License::setUrl(QString const& url)
{
  if(url != _url) 
  {
    _url = url; 
    emit urlChanged(_url);
  }
}
void QPndman::License::setSourcecodeurl(QString const& sourceCodeUrl)
{
  if(sourceCodeUrl != _sourceCodeUrl) 
  {
    _sourceCodeUrl = sourceCodeUrl; 
    emit sourceCodeUrlChanged(_sourceCodeUrl);
  }
}
