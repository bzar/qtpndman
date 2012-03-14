#ifndef EXECUTIONINFO_H
#define EXECUTIONINFO_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class ExecutionInfo : public QObject
  {
  Q_OBJECT
    Q_ENUMS(ExecX11)
    Q_PROPERTY(bool background READ getBackground CONSTANT)
    Q_PROPERTY(QString startDir READ getStartdir CONSTANT)
    Q_PROPERTY(bool standalone READ getStandalone CONSTANT)
    Q_PROPERTY(QString command READ getCommand CONSTANT)
    Q_PROPERTY(QString arguments READ getArguments CONSTANT)
    Q_PROPERTY(ExecX11 x11 READ getX11 CONSTANT)

  public:
    enum ExecX11 { ExecReq, ExecStop, ExecIgnore};

    ExecutionInfo(pndman_exec const* p, QObject* parent = 0);

    bool getBackground() const;
    QString getStartdir() const;
    bool getStandalone() const;
    QString getCommand() const;
    QString getArguments() const;
    ExecX11 getX11() const;

  private:
    bool background;
    QString startDir;
    bool standalone;
    QString command;
    QString arguments;
    ExecX11 x11;
  };
}

#endif
