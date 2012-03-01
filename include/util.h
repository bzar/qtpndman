#ifndef QPNDMAN_UTIL_H
#define QPNDMAN_UTIL_H

#include <QList>
#include <QObject>

namespace QPndman
{
  template<typename Src, typename Dst>
  QList<Dst> makeQList(Src* s)
  {
    QList<Dst> result;
    for(Src* x = s; x != 0; x = x->next)
    {
      result << Dst(x);
    }
    return result;
  }

  template<typename Src, typename Dst>
  QList<Dst*> makeQListPtr(Src* s, QObject* parent)
  {
    QList<Dst*> result;
    for(Src* x = s; x != 0; x = x->next)
    {
      result << new Dst(x, parent);
    }
    return result;
  }

  template<typename T>
  T* getLast(T* s)
  {
    T* last = s;
    while(last->next)
    {
      last = last->next;
    }
    return last;
  }
}
#endif