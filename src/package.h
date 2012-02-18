#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QDateTime>
#include <QSharedPointer>

#include "author.h"
#include "version.h"
#include "application.h"
#include "translatedstring.h"
#include "category.h"

#include "pndman.h"

namespace QPndman
{
  class Package : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString path READ getPath NOTIFY pathChanged);
    Q_PROPERTY(QString id READ getId NOTIFY idChanged);
    Q_PROPERTY(QString icon READ getIcon NOTIFY iconChanged);
    Q_PROPERTY(QString info READ getInfo NOTIFY infoChanged);
    Q_PROPERTY(QString md5 READ getMd5 NOTIFY md5Changed);
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged);
    Q_PROPERTY(QString vendor READ getVendor NOTIFY vendorChanged);
    Q_PROPERTY(qint64 size READ getSize NOTIFY sizeChanged);
    Q_PROPERTY(QDateTime modified READ getModified NOTIFY modifiedChanged);
    Q_PROPERTY(int rating READ getRating NOTIFY ratingChanged);
    Q_PROPERTY(Author author READ getAuthor NOTIFY authorChanged);
    Q_PROPERTY(Version version READ getVersion NOTIFY versionChanged);
    Q_PROPERTY(QList<Application> applications READ getApplications NOTIFY applicationsChanged);
    Q_PROPERTY(QList<TranslatedString> titles READ getTitles NOTIFY titlesChanged);
    Q_PROPERTY(QString title READ getTitle NOTIFY titlesChanged);
    Q_PROPERTY(QList<TranslatedString> descriptions READ getDescriptions NOTIFY descriptionsChanged);
    Q_PROPERTY(QString description READ getDescription NOTIFY descriptionsChanged);
    Q_PROPERTY(QList<Category> categories READ getCategories NOTIFY categoriesChanged);
    Q_PROPERTY(QList<Package> installInstances READ getInstallinstances NOTIFY installInstancesChanged);
    Q_PROPERTY(unsigned int flags READ getFlags NOTIFY flagsChanged);

  public:
    Package();
    Package(pndman_package* p);
    Package(Package const& other);
    
    Package& operator=(Package const& other);

    pndman_package* getPndmanPackage() const;
    bool isNull() const;
    
  public slots:
    QString getPath() const;
    QString getId() const;
    QString getIcon() const;
    QString getInfo() const;
    QString getMd5() const;
    QString getUrl() const;
    QString getVendor() const;
    qint64 getSize() const;
    QDateTime getModified() const;
    int getRating() const;
    Author getAuthor() const;
    Version getVersion() const;
    QList<Application> getApplications();
    QList<TranslatedString> getTitles();
    QString getTitle();
    QList<TranslatedString> getDescriptions();
    QString getDescription();
    QList<Category> getCategories();
    QList<Package> getInstallinstances();
    unsigned int getFlags() const;

  signals:
    void pathChanged(QString newPath);
    void idChanged(QString newId);
    void iconChanged(QString newIcon);
    void infoChanged(QString newInfo);
    void md5Changed(QString newMd5);
    void urlChanged(QString newUrl);
    void vendorChanged(QString newVendor);
    void sizeChanged(qint64 newSize);
    void modifiedChanged(QDateTime newModified);
    void ratingChanged(int newRating);
    void authorChanged(Author newAuthor);
    void versionChanged(Version newVersion);
    void applicationsChanged(QList<Application> newApplications);
    void titlesChanged(QList<TranslatedString> newTitles);
    void descriptionsChanged(QList<TranslatedString> newDescriptions);
    void categoriesChanged(QList<Category> newCategories);
    void installInstancesChanged(QList<Package> newInstallinstances);
    void flagsChanged(unsigned int newFlags);

  private:
    struct Data
    {
      Data(pndman_package* p);
      pndman_package* package;
    
      QString path;
      QString id;
      QString icon;
      QString info;
      QString md5;
      QString url;
      QString vendor;
      qint64 size;
      QDateTime modified;
      int rating;
      Author author;
      Version version;
      QList<Application> applications;
      QList<TranslatedString> titles;
      QList<TranslatedString> descriptions;
      QList<Category> categories;
      QList<Package> installInstances;
      unsigned int flags;
    };

    QSharedPointer<Data> d;

  };
}

#endif
