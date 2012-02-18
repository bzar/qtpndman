#include "executioninfo.h"

QPndman::ExecutionInfo::ExecutionInfo(pndman_exec const* p) : QObject(0), d(new Data(p))
{
  
}
QPndman::ExecutionInfo::Data::Data(pndman_exec const* p) :  
  background(p->background), startDir(p->startdir), standalone(p->standalone), command(p->command), 
  arguments(p->arguments), x11(ExecutionInfo::ExecReq)
{
  if(p->x11 == PND_EXEC_STOP) x11 = ExecStop;
  else if(p->x11 == PND_EXEC_IGNORE) x11 = ExecIgnore;
}

QPndman::ExecutionInfo::ExecutionInfo(ExecutionInfo const& other) : QObject(0), d(other.d)
{
}

QPndman::ExecutionInfo& QPndman::ExecutionInfo::operator=(ExecutionInfo const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

bool QPndman::ExecutionInfo::getBackground() const
{
  return d->background;
}
QString QPndman::ExecutionInfo::getStartdir() const
{
  return d->startDir;
}
bool QPndman::ExecutionInfo::getStandalone() const
{
  return d->standalone;
}
QString QPndman::ExecutionInfo::getCommand() const
{
  return d->command;
}
QString QPndman::ExecutionInfo::getArguments() const
{
  return d->arguments;
}
QPndman::ExecutionInfo::ExecX11 QPndman::ExecutionInfo::getX11() const
{
  return d->x11;
}

void QPndman::ExecutionInfo::setBackground(bool const& background)
{
  if(background != d->background) 
  {
    d->background = background; 
    emit backgroundChanged(d->background);
  }
}
void QPndman::ExecutionInfo::setStartdir(QString const& startDir)
{
  if(startDir != d->startDir) 
  {
    d->startDir = startDir; 
    emit startDirChanged(d->startDir);
  }
}
void QPndman::ExecutionInfo::setStandalone(bool const& standalone)
{
  if(standalone != d->standalone) 
  {
    d->standalone = standalone; 
    emit standaloneChanged(d->standalone);
  }
}
void QPndman::ExecutionInfo::setCommand(QString const& command)
{
  if(command != d->command) 
  {
    d->command = command; 
    emit commandChanged(d->command);
  }
}
void QPndman::ExecutionInfo::setArguments(QString const& arguments)
{
  if(arguments != d->arguments) 
  {
    d->arguments = arguments; 
    emit argumentsChanged(d->arguments);
  }
}
void QPndman::ExecutionInfo::setX11(ExecX11 const& x11)
{
  if(x11 != d->x11) 
  {
    d->x11 = x11; 
    emit x11Changed(d->x11);
  }
}
