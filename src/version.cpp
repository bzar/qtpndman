#include "version.h"

QPndman::Version::Version(QString const& major, QString const& minor, QString const& release, QString const& build, Type const& type, QObject* parent) : QObject(parent), 
  _major(major), _minor(minor), _release(release), _build(build), _type(type)
{
}

QPndman::Version::Version(pndman_version const* p) : QObject(0), 
  _major(p->major), _minor(p->minor), _release(p->release), _build(p->build), _type(Version::ReleaseVersion)
{
  if(p->type == PND_VERSION_BETA)       _type = Version::BetaVersion;
  else if(p->type == PND_VERSION_ALPHA) _type = Version::AlphaVersion;
}

QPndman::Version::Version(Version const& other) : QObject(0), 
  _major(other._major), _minor(other._minor), _release(other._release), _build(other._build), _type(other._type)
{
}

QPndman::Version& QPndman::Version::operator=(Version const& other)
{
  if(&other == this)
    return *this;
  
  _major = other._major;
  _minor = other._minor;
  _release = other._release;
  _build = other._build;
  _type = other._type;
  
  return *this;
}

QString QPndman::Version::getMajor() const
{
  return _major;
}
QString QPndman::Version::getMinor() const
{
  return _minor;
}
QString QPndman::Version::getRelease() const
{
  return _release;
}
QString QPndman::Version::getBuild() const
{
  return _build;
}
QPndman::Version::Type QPndman::Version::getType() const
{
  return _type;
}

void QPndman::Version::setMajor(QString const& major)
{
  if(major != _major) 
  {
    _major = major; 
    emit majorChanged(_major);
  }
}
void QPndman::Version::setMinor(QString const& minor)
{
  if(minor != _minor) 
  {
    _minor = minor; 
    emit minorChanged(_minor);
  }
}
void QPndman::Version::setRelease(QString const& release)
{
  if(release != _release) 
  {
    _release = release; 
    emit releaseChanged(_release);
  }
}
void QPndman::Version::setBuild(QString const& build)
{
  if(build != _build) 
  {
    _build = build; 
    emit buildChanged(_build);
  }
}
void QPndman::Version::setType(Type const& type)
{
  if(type != _type) 
  {
    _type = type; 
    emit typeChanged(_type);
  }
}
