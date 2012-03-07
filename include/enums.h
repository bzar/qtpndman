#ifndef QPNDMAN_ENUMS_H
#define QPNDMAN_ENUMS_H

#include <QObject>

namespace QPndman
{
  class Enum : public QObject
  {
    Q_OBJECT
  public:
    enum Operation { Install, Remove, Upgrade };
    enum InstallLocation { Desktop, Menu, DesktopAndMenu };

    Q_ENUMS(Operation InstallLocation)
  };
}

#endif
