#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QDateTime>

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
    Q_PROPERTY(QList< QSharedPointer<Application> > applications READ getApplications NOTIFY applicationsChanged);
    Q_PROPERTY(QList< QSharedPointer<TranslatedString> > titles READ getTitles NOTIFY titlesChanged);
    Q_PROPERTY(QList< QSharedPointer<TranslatedString> > descriptions READ getDescriptions NOTIFY descriptionsChanged);
    Q_PROPERTY(QList< QSharedPointer<Category> > categories READ getCategories NOTIFY categoriesChanged);
    Q_PROPERTY(QList< QSharedPointer<Package> > installInstances READ getInstallinstances NOTIFY installInstancesChanged);
    Q_PROPERTY(unsigned int flags READ getFlags NOTIFY flagsChanged);

  public:
    Package(pndman_package const* p);
    Package(Package const& other);
    
    Package& operator=(Package const& other);

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
    QList< QSharedPointer<Application> > getApplications();
    QList< QSharedPointer<TranslatedString> > getTitles();
    QList< QSharedPointer<TranslatedString> > getDescriptions();
    QList< QSharedPointer<Category> > getCategories();
    QList< QSharedPointer<Package> > getInstallinstances();
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
    void applicationsChanged(QList< QSharedPointer<Application> > newApplications);
    void titlesChanged(QList< QSharedPointer<TranslatedString> > newTitles);
    void descriptionsChanged(QList< QSharedPointer<TranslatedString> > newDescriptions);
    void categoriesChanged(QList< QSharedPointer<Category> > newCategories);
    void installInstancesChanged(QList< QSharedPointer<Package> > newInstallinstances);
    void flagsChanged(unsigned int newFlags);

  private:
    pndman_package const* _pndman_package;
    
    QString _path;
    QString _id;
    QString _icon;
    QString _info;
    QString _md5;
    QString _url;
    QString _vendor;
    qint64 _size;
    QDateTime _modified;
    int _rating;
    Author _author;
    Version _version;
    QList< QSharedPointer<Application> > _applications;
    QList< QSharedPointer<TranslatedString> > _titles;
    QList< QSharedPointer<TranslatedString> > _descriptions;
    QList< QSharedPointer<Category> > _categories;
    QList< QSharedPointer<Package> > _installInstances;
    unsigned int _flags;

  };
}

#endif
