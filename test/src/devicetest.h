#include "qtpndman.h"

class DeviceTest : public QObject
{
  Q_OBJECT
public:
  DeviceTest();
public slots:
  void run();  
private:
  QPndman::Context context;
};


