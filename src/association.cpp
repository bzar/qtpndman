#include "association.h"

QPndman::Association::Association(QString const& name, QString const& fileType, QString const& exec, QObject* parent) : QObject(parent), 
  _name(name), _fileType(fileType), _exec(exec)
{
}

QPndman::Association::Association(Association const& other) : QObject(0), 
  _name(other._name), _fileType(other._fileType), _exec(other._exec)
{
}

QPndman::Association& QPndman::Association::operator=(Association const& other)
{
  if(&other == this)
    return *this;
  
  _name = other._name;
  _fileType = other._fileType;
  _exec = other._exec;
  
  return *this;
}

QString QPndman::Association::getName() const
{
  return _name;
}
QString QPndman::Association::getFiletype() const
{
  return _fileType;
}
QString QPndman::Association::getExec() const
{
  return _exec;
}

void QPndman::Association::setName(QString const& name)
{
  if(name != _name) 
  {
    _name = name; 
    emit nameChanged(_name);
  }
}
void QPndman::Association::setFiletype(QString const& fileType)
{
  if(fileType != _fileType) 
  {
    _fileType = fileType; 
    emit fileTypeChanged(_fileType);
  }
}
void QPndman::Association::setExec(QString const& exec)
{
  if(exec != _exec) 
  {
    _exec = exec; 
    emit execChanged(_exec);
  }
}
