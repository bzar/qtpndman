#include "qtpndman.h"
using QPndman::SyncHandle;

class RepositoryTest : public QObject
{
  Q_OBJECT
public:
  RepositoryTest();
public slots:
  void run(); 
private:
  QPndman::Context context;
};


