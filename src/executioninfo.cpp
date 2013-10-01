#include "executioninfo.h"

QPndman::ExecutionInfo::ExecutionInfo(pndman_exec const* p, QObject* parent) : QObject(parent),
  background(p->background),
  startDir(!p->startdir ? "" : QString::fromUtf8(p->startdir)), standalone(p->standalone),
  command(!p->command ? "" : QString::fromUtf8(p->command)),
  arguments(!p->arguments ? "" : QString::fromUtf8(p->arguments)), x11(ExecutionInfo::ExecReq)
{
  
}

bool QPndman::ExecutionInfo::getBackground() const
{
  return background;
}
QString QPndman::ExecutionInfo::getStartdir() const
{
  return startDir;
}
bool QPndman::ExecutionInfo::getStandalone() const
{
  return standalone;
}
QString QPndman::ExecutionInfo::getCommand() const
{
  return command;
}
QString QPndman::ExecutionInfo::getArguments() const
{
  return arguments;
}
QPndman::ExecutionInfo::ExecX11 QPndman::ExecutionInfo::getX11() const
{
  return x11;
}
