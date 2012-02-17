#include "executioninfo.h"

QPndman::ExecutionInfo::ExecutionInfo(bool const& background, QString const& startDir, bool const& standalone, QString const& command, QString const& arguments, ExecX11 const& x11, QObject* parent) : QObject(parent), 
  _background(background), _startDir(startDir), _standalone(standalone), _command(command), _arguments(arguments), _x11(x11)
{
}

QPndman::ExecutionInfo::ExecutionInfo(ExecutionInfo const& other) : QObject(0), 
  _background(other._background), _startDir(other._startDir), _standalone(other._standalone), _command(other._command), _arguments(other._arguments), _x11(other._x11)
{
}

QPndman::ExecutionInfo::ExecutionInfo(pndman_exec const* p) : QObject(0), 
  _background(p->background), _startDir(p->startdir), _standalone(p->standalone), _command(p->command), _arguments(p->arguments), _x11(ExecutionInfo::ExecReq)
{
  if(p->x11 == PND_EXEC_STOP) _x11 = ExecStop;
  else if(p->x11 == PND_EXEC_IGNORE) _x11 = ExecIgnore;
}

QPndman::ExecutionInfo& QPndman::ExecutionInfo::operator=(ExecutionInfo const& other)
{
  if(&other == this)
    return *this;
  
  _background = other._background;
  _startDir = other._startDir;
  _standalone = other._standalone;
  _command = other._command;
  _arguments = other._arguments;
  _x11 = other._x11;
  
  return *this;
}

bool QPndman::ExecutionInfo::getBackground() const
{
  return _background;
}
QString QPndman::ExecutionInfo::getStartdir() const
{
  return _startDir;
}
bool QPndman::ExecutionInfo::getStandalone() const
{
  return _standalone;
}
QString QPndman::ExecutionInfo::getCommand() const
{
  return _command;
}
QString QPndman::ExecutionInfo::getArguments() const
{
  return _arguments;
}
QPndman::ExecutionInfo::ExecX11 QPndman::ExecutionInfo::getX11() const
{
  return _x11;
}

void QPndman::ExecutionInfo::setBackground(bool const& background)
{
  if(background != _background) 
  {
    _background = background; 
    emit backgroundChanged(_background);
  }
}
void QPndman::ExecutionInfo::setStartdir(QString const& startDir)
{
  if(startDir != _startDir) 
  {
    _startDir = startDir; 
    emit startDirChanged(_startDir);
  }
}
void QPndman::ExecutionInfo::setStandalone(bool const& standalone)
{
  if(standalone != _standalone) 
  {
    _standalone = standalone; 
    emit standaloneChanged(_standalone);
  }
}
void QPndman::ExecutionInfo::setCommand(QString const& command)
{
  if(command != _command) 
  {
    _command = command; 
    emit commandChanged(_command);
  }
}
void QPndman::ExecutionInfo::setArguments(QString const& arguments)
{
  if(arguments != _arguments) 
  {
    _arguments = arguments; 
    emit argumentsChanged(_arguments);
  }
}
void QPndman::ExecutionInfo::setX11(ExecX11 const& x11)
{
  if(x11 != _x11) 
  {
    _x11 = x11; 
    emit x11Changed(_x11);
  }
}
