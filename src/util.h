#ifndef QPNDMAN_UTIL_H
#define QPNDMAN_UTIL_H

#include <QList>
#include <QSharedPointer>

namespace QPndman
{
  template<typename Src, typename Dst>
  QList< QSharedPointer<Dst> > makeQList(Src const* s)
  {
    QList< QSharedPointer<Dst> > result;
    for(Src const* x = s; x != 0; x = x->next)
    {
      QSharedPointer<Dst> d(new Dst(x));
      result << d;
    }
    return result;
  }
}
#endif