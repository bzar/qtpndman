#ifndef VERSION_H
#define VERSION_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class Version : public QObject
  {
  Q_OBJECT
    Q_ENUMS(Type)
    Q_PROPERTY(QString major READ getMajor CONSTANT)
    Q_PROPERTY(QString minor READ getMinor CONSTANT)
    Q_PROPERTY(QString release READ getRelease CONSTANT)
    Q_PROPERTY(QString build READ getBuild CONSTANT)
    Q_PROPERTY(Type type READ getType CONSTANT)

  public:
    enum Type { ReleaseVersion, BetaVersion, AlphaVersion };

    Version(pndman_version const* p, QObject* parent = 0);

    Q_INVOKABLE QString toString() const;
    
    QString getMajor() const;
    QString getMinor() const;
    QString getRelease() const;
    QString getBuild() const;
    Type getType() const;

    bool operator==(Version const& other) const;
    bool operator!=(Version const& other) const;

  private:
    QString _major;
    QString _minor;
    QString release;
    QString build;
    Type type;
  };
}

#endif
