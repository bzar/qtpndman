#include "documentationinfo.h"

QPndman::DocumentationInfo::DocumentationInfo(QObject* parent): QObject(parent)
{

}

QPndman::DocumentationInfo::DocumentationInfo(pndman_info const* p) : QObject(0), d(new Data(p))
{
}

QPndman::DocumentationInfo::Data::Data(pndman_info const* p) : 
  name(p->name), type(p->type), src(p->src)
{
  
}

QPndman::DocumentationInfo::DocumentationInfo(DocumentationInfo const& other) : QObject(0), d(other.d)
{
}

QPndman::DocumentationInfo& QPndman::DocumentationInfo::operator=(DocumentationInfo const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::DocumentationInfo::getName() const
{
  return d->name;
}
QString QPndman::DocumentationInfo::getType() const
{
  return d->type;
}
QString QPndman::DocumentationInfo::getSrc() const
{
  return d->src;
}

void QPndman::DocumentationInfo::setName(QString const& name)
{
  if(name != d->name) 
  {
    d->name = name; 
    emit nameChanged(d->name);
  }
}
void QPndman::DocumentationInfo::setType(QString const& type)
{
  if(type != d->type) 
  {
    d->type = type; 
    emit typeChanged(d->type);
  }
}
void QPndman::DocumentationInfo::setSrc(QString const& src)
{
  if(src != d->src) 
  {
    d->src = src; 
    emit srcChanged(d->src);
  }
}
