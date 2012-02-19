#include "qtpndman.h"
using QPndman::SyncHandle;

class Test : public QObject
{
  Q_OBJECT
public:
  Test();
public slots:
  void run(); 
  void syncStarted(SyncHandle*);
  void syncError();
  void syncError(SyncHandle*);
  void syncFinished();
private:
  QPndman::Manager* manager;
};


