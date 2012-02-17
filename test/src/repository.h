#include "qtpndman.h"

class Test : public QObject
{
  Q_OBJECT
public:
  Test();
public slots:
  void run();  
  void syncError();  
  void syncFinished();
private:
  QPndman::Manager* manager;
};


