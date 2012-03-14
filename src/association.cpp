#include "association.h"

QPndman::Association::Association(pndman_association const* p, QObject* parent) : QObject(parent),
  name(p->name), fileType(p->filetype), exec(p->exec)
{
}

QString QPndman::Association::getName() const
{
  return name;
}
QString QPndman::Association::getFiletype() const
{
  return fileType;
}
QString QPndman::Association::getExec() const
{
  return exec;
}
