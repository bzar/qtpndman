#include "association.h"

QPndman::Association::Association(pndman_association const* p) : QObject(0), d(new Data(p))
{
}

QPndman::Association::Data::Data(pndman_association const* p) : 
  name(p->name), fileType(p->filetype), exec(p->exec)
{
}

QPndman::Association::Association(Association const& other) : QObject(0), d(other.d)
{
}

QPndman::Association& QPndman::Association::operator=(Association const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::Association::getName() const
{
  return d->name;
}
QString QPndman::Association::getFiletype() const
{
  return d->fileType;
}
QString QPndman::Association::getExec() const
{
  return d->exec;
}

void QPndman::Association::setName(QString const& name)
{
  if(name != d->name) 
  {
    d->name = name; 
    emit nameChanged(d->name);
  }
}
void QPndman::Association::setFiletype(QString const& fileType)
{
  if(fileType != d->fileType) 
  {
    d->fileType = fileType; 
    emit fileTypeChanged(d->fileType);
  }
}
void QPndman::Association::setExec(QString const& exec)
{
  if(exec != d->exec) 
  {
    d->exec = exec; 
    emit execChanged(d->exec);
  }
}
