#include "association.h"

QPndman::Association::Association(pndman_association const* p, QObject* parent) : QObject(parent),
  name(QString::fromUtf8(p->name)), fileType(QString::fromUtf8(p->filetype)), exec(QString::fromUtf8(p->exec))
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
