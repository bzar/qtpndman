#include "author.h"

QPndman::Author::Author(pndman_author const* p, QObject* parent) : QObject(parent),
  name(!p->name ? "" : QString::fromUtf8(p->name)),
  website(!p->website ? "" : QString::fromUtf8(p->website))
{
  
}

QString QPndman::Author::getName() const
{
  return name;
}
QString QPndman::Author::getWebsite() const
{
  return website;
}
