#ifndef EXECUTIONINFO_H
#define EXECUTIONINFO_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class ExecutionInfo : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(bool background READ getBackground WRITE setBackground NOTIFY backgroundChanged);
    Q_PROPERTY(QString startDir READ getStartdir WRITE setStartdir NOTIFY startDirChanged);
    Q_PROPERTY(bool standalone READ getStandalone WRITE setStandalone NOTIFY standaloneChanged);
    Q_PROPERTY(QString command READ getCommand WRITE setCommand NOTIFY commandChanged);
    Q_PROPERTY(QString arguments READ getArguments WRITE setArguments NOTIFY argumentsChanged);
    Q_PROPERTY(ExecX11 x11 READ getX11 WRITE setX11 NOTIFY x11Changed);

  public:
    enum ExecX11 { ExecReq, ExecStop, ExecIgnore};

    ExecutionInfo(bool const& background, QString const& startDir, bool const& standalone, QString const& command, QString const& arguments, ExecX11 const& x11, QObject* parent = 0);
    ExecutionInfo(pndman_exec const* p);
    ExecutionInfo(ExecutionInfo const& other);
    ExecutionInfo& operator=(ExecutionInfo const& other);

  public slots:
    bool getBackground() const;
    QString getStartdir() const;
    bool getStandalone() const;
    QString getCommand() const;
    QString getArguments() const;
    ExecX11 getX11() const;

    void setBackground(bool const& background);
    void setStartdir(QString const& startDir);
    void setStandalone(bool const& standalone);
    void setCommand(QString const& command);
    void setArguments(QString const& arguments);
    void setX11(ExecX11 const& x11);

  signals:
    void backgroundChanged(bool newBackground);
    void startDirChanged(QString newStartdir);
    void standaloneChanged(bool newStandalone);
    void commandChanged(QString newCommand);
    void argumentsChanged(QString newArguments);
    void x11Changed(ExecX11 newX11);

  private:
    bool _background;
    QString _startDir;
    bool _standalone;
    QString _command;
    QString _arguments;
    ExecX11 _x11;

  };
}

#endif
