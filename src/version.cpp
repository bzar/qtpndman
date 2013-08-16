#include "version.h"

QPndman::Version::Version(const QString majorVersion, const QString minorVersion, const QString release, const QString build, const QPndman::Version::Type type, QObject* parent) :
  QObject(parent),
  _major(majorVersion), _minor(minorVersion), release(release), build(build), type(type)
{
}

QPndman::Version::Version(pndman_version const* p, QObject* parent) : QObject(parent),
  _major(QString::fromUtf8(p->major)), _minor(QString::fromUtf8(p->minor)),
  release(QString::fromUtf8(p->release)), build(QString::fromUtf8(p->build)),
  type(Version::ReleaseVersion)
{
  if(p->type == PND_VERSION_BETA)       type = Version::BetaVersion;
  else if(p->type == PND_VERSION_ALPHA) type = Version::AlphaVersion;
}

QString QPndman::Version::toString() const
{
  QString format = "%1.%2.%3.%4";
  if(type == AlphaVersion)
  {
    format.append(" alpha");
  }
  else if(type == BetaVersion)
  {
    format.append(" beta");
  }
  
  return format.arg(_major).arg(_minor).arg(release).arg(build);
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
  return release;
}
QString QPndman::Version::getBuild() const
{
  return build;
}
QPndman::Version::Type QPndman::Version::getType() const
{
  return type;
}

bool QPndman::Version::operator ==(const QPndman::Version &other) const
{
  return _major == other._major
      && _minor == other._minor
      && release == other.release
      && build == other.build
      && type == other.type;
}

bool QPndman::Version::operator !=(const QPndman::Version &other) const
{
  return !operator==(other);
}

bool QPndman::Version::operator <(const QPndman::Version &other) const
{
  if(_major == other._major)
    if(_minor == other._minor)
      if(release == other.release)
        if(build == other.build)
          return type < other.type;
        else return build < other.build;
      else return release < other.release;
    else return _minor < other._minor;
  else return _major < other._major;
}

bool QPndman::Version::operator >(const QPndman::Version &other) const
{
  return !operator<(other) && !operator==(other);
}

bool QPndman::Version::operator <=(const QPndman::Version &other) const
{
  return !operator>(other);
}

bool QPndman::Version::operator >=(const QPndman::Version &other) const
{
  return !operator<(other);
}

int QPndman::Version::encodeVersionType(const pndman_version_type type)
{
  if(type == PND_VERSION_RELEASE)
  {
    return 0;
  }
  else if(type == PND_VERSION_BETA)
  {
    return 1;
  }
  else if(type == PND_VERSION_ALPHA)
  {
    return 2;
  }
}

QPndman::Version::Type QPndman::Version::decodeVersionType(const int type)
{
  if(type == 0)
  {
    return ReleaseVersion;
  }
  else if(type == 1)
  {
    return BetaVersion;
  }
  else
  {
    return AlphaVersion;
  }
}

