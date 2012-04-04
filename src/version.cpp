#include "version.h"

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
