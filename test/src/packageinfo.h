#include "qtpndman.h"

class PackageInfoTest : public QObject
{
  Q_OBJECT
public:
  PackageInfoTest();
public slots:
  void run(); 
private:
  QPndman::Context context;
};


