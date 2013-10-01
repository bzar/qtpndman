#include "documentationinfo.h"

QPndman::DocumentationInfo::DocumentationInfo(pndman_info const* p, QObject* parent) : QObject(parent),
  name(!p->name ? "" : QString::fromUtf8(p->name)),
  type(!p->type ? "" : QString::fromUtf8(p->type)),
  src(!p->src ? "" : QString::fromUtf8(p->src))
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
