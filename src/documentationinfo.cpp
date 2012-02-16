#include "documentationinfo.h"

QPndman::DocumentationInfo::DocumentationInfo(QString const& name, QString const& type, QString const& src, QObject* parent) : QObject(parent), 
  _name(name), _type(type), _src(src)
{
}

QPndman::DocumentationInfo::DocumentationInfo(DocumentationInfo const& other) : QObject(0), 
  _name(other._name), _type(other._type), _src(other._src)
{
}

QPndman::DocumentationInfo& QPndman::DocumentationInfo::operator=(DocumentationInfo const& other)
{
  if(&other == this)
    return *this;
  
  _name = other._name;
  _type = other._type;
  _src = other._src;
  
  return *this;
}

QString QPndman::DocumentationInfo::getName() const
{
  return _name;
}
QString QPndman::DocumentationInfo::getType() const
{
  return _type;
}
QString QPndman::DocumentationInfo::getSrc() const
{
  return _src;
}

void QPndman::DocumentationInfo::setName(QString const& name)
{
  if(name != _name) 
  {
    _name = name; 
    emit nameChanged(_name);
  }
}
void QPndman::DocumentationInfo::setType(QString const& type)
{
  if(type != _type) 
  {
    _type = type; 
    emit typeChanged(_type);
  }
}
void QPndman::DocumentationInfo::setSrc(QString const& src)
{
  if(src != _src) 
  {
    _src = src; 
    emit srcChanged(_src);
  }
}
