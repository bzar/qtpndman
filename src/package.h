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

    Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged);
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged);
    Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
    Q_PROPERTY(QString info READ getInfo WRITE setInfo NOTIFY infoChanged);
    Q_PROPERTY(QString md5 READ getMd5 WRITE setMd5 NOTIFY md5Changed);
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged);
    Q_PROPERTY(QString vendor READ getVendor WRITE setVendor NOTIFY vendorChanged);
    Q_PROPERTY(qint64 size READ getSize WRITE setSize NOTIFY sizeChanged);
    Q_PROPERTY(QDateTime modified READ getModified WRITE setModified NOTIFY modifiedChanged);
    Q_PROPERTY(int rating READ getRating WRITE setRating NOTIFY ratingChanged);
    Q_PROPERTY(Author author READ getAuthor WRITE setAuthor NOTIFY authorChanged);
    Q_PROPERTY(Version version READ getVersion WRITE setVersion NOTIFY versionChanged);
    Q_PROPERTY(QList< QSharedPointer<Application> > applications READ getApplications WRITE setApplications NOTIFY applicationsChanged);
    Q_PROPERTY(QList< QSharedPointer<TranslatedString> > titles READ getTitles WRITE setTitles NOTIFY titlesChanged);
    Q_PROPERTY(QList< QSharedPointer<TranslatedString> > descriptions READ getDescriptions WRITE setDescriptions NOTIFY descriptionsChanged);
    Q_PROPERTY(QList< QSharedPointer<Category> > categories READ getCategories WRITE setCategories NOTIFY categoriesChanged);
    Q_PROPERTY(unsigned int flags READ getFlags WRITE setFlags NOTIFY flagsChanged);
    Q_PROPERTY(QList< QSharedPointer<Package> > installInstances READ getInstallinstances WRITE setInstallinstances NOTIFY installInstancesChanged);

  public:
    Package(QString const& path, QString const& id, QString const& icon, QString const& info, QString const& md5, QString const& url, QString const& vendor, 
            qint64 const& size, QDateTime const& modified, int const& rating, Author const& author, Version const& version, QList< QSharedPointer<Application> > const& applications, 
            QList< QSharedPointer<TranslatedString> > const& titles, QList< QSharedPointer<TranslatedString> > const& descriptions, QList< QSharedPointer<Category> > const& categories, unsigned int const& flags, 
            QList< QSharedPointer<Package> > const& installInstances, QObject* parent = 0);
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
    QList< QSharedPointer<Application> > getApplications() const;
    QList< QSharedPointer<TranslatedString> > getTitles() const;
    QList< QSharedPointer<TranslatedString> > getDescriptions() const;
    QList< QSharedPointer<Category> > getCategories() const;
    unsigned int getFlags() const;
    QList< QSharedPointer<Package> > getInstallinstances() const;

    void setPath(QString const& path);
    void setId(QString const& id);
    void setIcon(QString const& icon);
    void setInfo(QString const& info);
    void setMd5(QString const& md5);
    void setUrl(QString const& url);
    void setVendor(QString const& vendor);
    void setSize(qint64 const& size);
    void setModified(QDateTime const& modified);
    void setRating(int const& rating);
    void setAuthor(Author const& author);
    void setVersion(Version const& version);
    void setApplications(QList< QSharedPointer<Application> > const& applications);
    void setTitles(QList< QSharedPointer<TranslatedString> > const& titles);
    void setDescriptions(QList< QSharedPointer<TranslatedString> > const& descriptions);
    void setCategories(QList< QSharedPointer<Category> > const& categories);
    void setFlags(unsigned int const& flags);
    void setInstallinstances(QList< QSharedPointer<Package> > const& installInstances);

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
    void flagsChanged(unsigned int newFlags);
    void installInstancesChanged(QList< QSharedPointer<Package> > newInstallinstances);

  private:
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
    unsigned int _flags;
    QList< QSharedPointer<Package> > _installInstances;

  };
}

#endif
