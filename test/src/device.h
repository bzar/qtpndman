#include "qtpndman.h"

class Test : public QObject
{
  Q_OBJECT
public:
  Test();
public slots:
  void run();  
private:
  QPndman::Manager* manager;
};


