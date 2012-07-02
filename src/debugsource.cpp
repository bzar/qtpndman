#include "debugsource.h"
#include "pndman.h"
#include <QDebug>

QPndman::DebugSource *QPndman::DebugSource::instance()
{
  static DebugSource ds;
  return &ds;
}

QPndman::DebugSource::DebugSource(QObject *parent) : QObject(parent)
{
  pndman_set_debug_hook(debugCallback);
}

void QPndman::DebugSource::debugCallback(const char *file, int line, const char *function, int verbose_level, const char *str)
{
  emit instance()->message(QString::fromUtf8(file), QString::fromUtf8(function), line, verbose_level, QString::fromUtf8(str));
}
