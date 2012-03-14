#include "documentationinfo.h"

QPndman::DocumentationInfo::DocumentationInfo(pndman_info const* p, QObject* parent) : QObject(parent),
  name(p->name), type(p->type), src(p->src)
{
}

QString QPndman::DocumentationInfo::getName() const
{
  return name;
}
QString QPndman::DocumentationInfo::getType() const
{
  return type;
}
QString QPndman::DocumentationInfo::getSrc() const
{
  return src;
}
