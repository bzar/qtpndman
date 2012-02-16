#include "category.h"

QPndman::Category::Category(QString const& main, QString const& sub, QObject* parent) : QObject(parent), 
  _main(main), _sub(sub)
{
}

QPndman::Category::Category(Category const& other) : QObject(0), 
  _main(other._main), _sub(other._sub)
{
}

QPndman::Category& QPndman::Category::operator=(Category const& other)
{
  if(&other == this)
    return *this;
  
  _main = other._main;
  _sub = other._sub;
  
  return *this;
}

QString QPndman::Category::getMain() const
{
  return _main;
}
QString QPndman::Category::getSub() const
{
  return _sub;
}

void QPndman::Category::setMain(QString const& main)
{
  if(main != _main) 
  {
    _main = main; 
    emit mainChanged(_main);
  }
}
void QPndman::Category::setSub(QString const& sub)
{
  if(sub != _sub) 
  {
    _sub = sub; 
    emit subChanged(_sub);
  }
}
