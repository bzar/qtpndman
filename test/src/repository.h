#include "qtpndman.h"
using QPndman::SyncHandle;

class Test : public QObject
{
  Q_OBJECT
public:
  Test();
public slots:
  void run(); 
private:
  QPndman::Context context;
};


