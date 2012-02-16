#include "handle.h"

QPndman::Handle::Handle(QString const& main, QString const& error, QString const& url, unsigned int const& flags, bool const& done, QObject* parent) : QObject(parent), 
  _main(main), _error(error), _url(url), _flags(flags), _done(done)
{
}

QPndman::Handle::Handle(Handle const& other) : QObject(0), 
  _main(other._main), _error(other._error), _url(other._url), _flags(other._flags), _done(other._done)
{
}

QPndman::Handle& QPndman::Handle::operator=(Handle const& other)
{
  if(&other == this)
    return *this;
  
  _main = other._main;
  _error = other._error;
  _url = other._url;
  _flags = other._flags;
  _done = other._done;
  
  return *this;
}

QString QPndman::Handle::getMain() const
{
  return _main;
}
QString QPndman::Handle::getError() const
{
  return _error;
}
QString QPndman::Handle::getUrl() const
{
  return _url;
}
unsigned int QPndman::Handle::getFlags() const
{
  return _flags;
}
bool QPndman::Handle::getDone() const
{
  return _done;
}

void QPndman::Handle::setMain(QString const& main)
{
  if(main != _main) 
  {
    _main = main; 
    emit mainChanged(_main);
  }
}
void QPndman::Handle::setError(QString const& error)
{
  if(error != _error) 
  {
    _error = error; 
    emit errorChanged(_error);
  }
}
void QPndman::Handle::setUrl(QString const& url)
{
  if(url != _url) 
  {
    _url = url; 
    emit urlChanged(_url);
  }
}
void QPndman::Handle::setFlags(unsigned int const& flags)
{
  if(flags != _flags) 
  {
    _flags = flags; 
    emit flagsChanged(_flags);
  }
}
void QPndman::Handle::setDone(bool const& done)
{
  if(done != _done) 
  {
    _done = done; 
    emit doneChanged(_done);
  }
}
