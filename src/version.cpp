#include "version.h"

QPndman::Version::Version(pndman_version const* p) : QObject(0), d(new Data(p))
{
}

QPndman::Version::Data::Data(pndman_version const* p) : 
  _major(p->major), _minor(p->minor), release(p->release), build(p->build), type(Version::ReleaseVersion)
{
  if(p->type == PND_VERSION_BETA)       type = Version::BetaVersion;
  else if(p->type == PND_VERSION_ALPHA) type = Version::AlphaVersion;
}

QPndman::Version::Version(Version const& other) : QObject(0), d(other.d)
{
}

QPndman::Version& QPndman::Version::operator=(Version const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::Version::toString() const
{
  QString format = "%1.%2.%3.%4";
  if(d->type == AlphaVersion)
  {
    format.append(" alpha");
  }
  else if(d->type == BetaVersion)
  {
    format.append(" beta");
  }
  
  return format.arg(d->_major).arg(d->_minor).arg(d->release).arg(d->build);
}

QString QPndman::Version::getMajor() const
{
  return d->_major;
}
QString QPndman::Version::getMinor() const
{
  return d->_minor;
}
QString QPndman::Version::getRelease() const
{
  return d->release;
}
QString QPndman::Version::getBuild() const
{
  return d->build;
}
QPndman::Version::Type QPndman::Version::getType() const
{
  return d->type;
}

void QPndman::Version::setMajor(QString const& _major)
{
  if(_major != d->_major) 
  {
    d->_major = _major; 
    emit majorChanged(d->_major);
  }
}
void QPndman::Version::setMinor(QString const& _minor)
{
  if(_minor != d->_minor) 
  {
    d->_minor = _minor; 
    emit minorChanged(d->_minor);
  }
}
void QPndman::Version::setRelease(QString const& release)
{
  if(release != d->release) 
  {
    d->release = release; 
    emit releaseChanged(d->release);
  }
}
void QPndman::Version::setBuild(QString const& build)
{
  if(build != d->build) 
  {
    d->build = build; 
    emit buildChanged(d->build);
  }
}
void QPndman::Version::setType(Type const& type)
{
  if(type != d->type) 
  {
    d->type = type; 
    emit typeChanged(d->type);
  }
}
