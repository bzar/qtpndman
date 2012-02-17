#include "author.h"

QPndman::Author::Author(QString const& name, QString const& website, QObject* parent) : QObject(parent), 
  _name(name), _website(website)
{
}

QPndman::Author::Author(pndman_author const* p) : QObject(0), 
  _name(p->name), _website(p->website)
{
}

QPndman::Author::Author(Author const& other) : QObject(0), 
  _name(other._name), _website(other._website)
{
}

QPndman::Author& QPndman::Author::operator=(Author const& other)
{
  if(&other == this)
    return *this;
  
  _name = other._name;
  _website = other._website;
  
  return *this;
}

QString QPndman::Author::getName() const
{
  return _name;
}
QString QPndman::Author::getWebsite() const
{
  return _website;
}

void QPndman::Author::setName(QString const& name)
{
  if(name != _name) 
  {
    _name = name; 
    emit nameChanged(_name);
  }
}
void QPndman::Author::setWebsite(QString const& website)
{
  if(website != _website) 
  {
    _website = website; 
    emit websiteChanged(_website);
  }
}
