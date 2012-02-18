#include "category.h"

QPndman::Category::Category(pndman_category const* p) : QObject(0), d(new Data(p))
{
}
QPndman::Category::Data::Data(pndman_category const* p) : 
  main(p->main), sub(p->sub)
{
}

QPndman::Category::Category(Category const& other) : QObject(0), d(other.d)
{
}

QPndman::Category& QPndman::Category::operator=(Category const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::Category::getMain() const
{
  return d->main;
}
QString QPndman::Category::getSub() const
{
  return d->sub;
}

void QPndman::Category::setMain(QString const& main)
{
  if(main != d->main) 
  {
    d->main = main; 
    emit mainChanged(d->main);
  }
}
void QPndman::Category::setSub(QString const& sub)
{
  if(sub != d->sub) 
  {
    d->sub = sub; 
    emit subChanged(d->sub);
  }
}
