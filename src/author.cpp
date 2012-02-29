#include "author.h"

QPndman::Author::Author(QObject* parent): QObject(parent)
{

}

QPndman::Author::Author(pndman_author const* p) : QObject(0), d(new Data(p))
{
  
}

QPndman::Author::Data::Data(pndman_author const* p) : 
  name(p->name), website(p->website)
{
}

QPndman::Author::Author(Author const& other) : QObject(0), d(other.d)
{
}

QPndman::Author& QPndman::Author::operator=(Author const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::Author::getName() const
{
  return d->name;
}
QString QPndman::Author::getWebsite() const
{
  return d->website;
}

void QPndman::Author::setName(QString const& name)
{
  if(name != d->name) 
  {
    d->name = name; 
    emit nameChanged(d->name);
  }
}
void QPndman::Author::setWebsite(QString const& website)
{
  if(website != d->website) 
  {
    d->website = website; 
    emit websiteChanged(d->website);
  }
}
