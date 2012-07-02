#ifndef QPNDMAN_DEBUGSOURCE_HH
#define QPNDMAN_DEBUGSOURCE_HH

#include <QObject>

namespace QPndman
{
  class DebugSource : public QObject
  {
    Q_OBJECT

  public:
    static DebugSource* instance();

  signals:
    void message(QString file, QString function, int line, int verbosity, QString message);

  private:
    DebugSource(QObject* parent = 0);

    static void debugCallback(const char *file, int line, const char *function, int verbose_level, const char *str);
  };

}

#endif
