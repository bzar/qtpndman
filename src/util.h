#ifndef QPNDMAN_UTIL_H
#define QPNDMAN_UTIL_H

#include <QList>

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