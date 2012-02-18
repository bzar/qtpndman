#ifndef VERSION_H
#define VERSION_H

#include <QObject>
#include <QExplicitlySharedDataPointer>

#include "pndman.h"

namespace QPndman
{
  class Version : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString major READ getMajor WRITE setMajor NOTIFY majorChanged);
    Q_PROPERTY(QString minor READ getMinor WRITE setMinor NOTIFY minorChanged);
    Q_PROPERTY(QString release READ getRelease WRITE setRelease NOTIFY releaseChanged);
    Q_PROPERTY(QString build READ getBuild WRITE setBuild NOTIFY buildChanged);
    Q_PROPERTY(Type type READ getType WRITE setType NOTIFY typeChanged);

  public:
    enum Type { ReleaseVersion, BetaVersion, AlphaVersion };

    Version(pndman_version const* p);
    Version(Version const& other);
    Version& operator=(Version const& other);

  public slots:
    QString getMajor() const;
    QString getMinor() const;
    QString getRelease() const;
    QString getBuild() const;
    Type getType() const;

    void setMajor(QString const& major);
    void setMinor(QString const& minor);
    void setRelease(QString const& release);
    void setBuild(QString const& build);
    void setType(Type const& type);

  signals:
    void majorChanged(QString newMajor);
    void minorChanged(QString newMinor);
    void releaseChanged(QString newRelease);
    void buildChanged(QString newBuild);
    void typeChanged(Type newType);

  private:
    struct Data : public QSharedData
    {
      Data(pndman_version const* p);
      QString _major;
      QString _minor;
      QString release;
      QString build;
      Type type;
    };

    QExplicitlySharedDataPointer<Data> d;

  };
}

#endif
