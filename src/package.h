#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QDateTime>

#include "documentationinfo.h"
#include "author.h"
#include "version.h"
#include "application.h"
#include "translatedstring.h"
#include "previewpicture.h"
#include "category.h"

namespace QPndman
{
  class Package : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged);
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged);
    Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
    Q_PROPERTY(DocumentationInfo documentationInfo READ getDocumentationinfo WRITE setDocumentationinfo NOTIFY documentationInfoChanged);
    Q_PROPERTY(QString md5 READ getMd5 WRITE setMd5 NOTIFY md5Changed);
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged);
    Q_PROPERTY(QString vendor READ getVendor WRITE setVendor NOTIFY vendorChanged);
    Q_PROPERTY(qint64 size READ getSize WRITE setSize NOTIFY sizeChanged);
    Q_PROPERTY(QDateTime modified READ getModified WRITE setModified NOTIFY modifiedChanged);
    Q_PROPERTY(int rating READ getRating WRITE setRating NOTIFY ratingChanged);
    Q_PROPERTY(Author author READ getAuthor WRITE setAuthor NOTIFY authorChanged);
    Q_PROPERTY(Version version READ getVersion WRITE setVersion NOTIFY versionChanged);
    Q_PROPERTY(QList<Application> applications READ getApplications WRITE setApplications NOTIFY applicationsChanged);
    Q_PROPERTY(QList<TranslatedString> titles READ getTitles WRITE setTitles NOTIFY titlesChanged);
    Q_PROPERTY(QList<TranslatedString> descriptions READ getDescriptions WRITE setDescriptions NOTIFY descriptionsChanged);
    Q_PROPERTY(QList<PreviewPicture> previewPictures READ getPreviewpictures WRITE setPreviewpictures NOTIFY previewPicturesChanged);
    Q_PROPERTY(QList<Category> categories READ getCategories WRITE setCategories NOTIFY categoriesChanged);
    Q_PROPERTY(unsigned int flags READ getFlags WRITE setFlags NOTIFY flagsChanged);
    Q_PROPERTY(QList<Package> installInstances READ getInstallinstances WRITE setInstallinstances NOTIFY installInstancesChanged);

  public:
    Package(QString const& path, QString const& id, QString const& icon, DocumentationInfo const& documentationInfo, QString const& md5, QString const& url, QString const& vendor, qint64 const& size, QDateTime const& modified, int const& rating, Author const& author, Version const& version, QList<Application> const& applications, QList<TranslatedString> const& titles, QList<TranslatedString> const& descriptions, QList<PreviewPicture> const& previewPictures, QList<Category> const& categories, unsigned int const& flags, QList<Package> const& installInstances, QObject* parent = 0);
    Package(Package const& other);
    Package& operator=(Package const& other);

  public slots:
    QString getPath() const;
    QString getId() const;
    QString getIcon() const;
    DocumentationInfo getDocumentationinfo() const;
    QString getMd5() const;
    QString getUrl() const;
    QString getVendor() const;
    qint64 getSize() const;
    QDateTime getModified() const;
    int getRating() const;
    Author getAuthor() const;
    Version getVersion() const;
    QList<Application> getApplications() const;
    QList<TranslatedString> getTitles() const;
    QList<TranslatedString> getDescriptions() const;
    QList<PreviewPicture> getPreviewpictures() const;
    QList<Category> getCategories() const;
    unsigned int getFlags() const;
    QList<Package> getInstallinstances() const;

    void setPath(QString const& path);
    void setId(QString const& id);
    void setIcon(QString const& icon);
    void setDocumentationinfo(DocumentationInfo const& documentationInfo);
    void setMd5(QString const& md5);
    void setUrl(QString const& url);
    void setVendor(QString const& vendor);
    void setSize(qint64 const& size);
    void setModified(QDateTime const& modified);
    void setRating(int const& rating);
    void setAuthor(Author const& author);
    void setVersion(Version const& version);
    void setApplications(QList<Application> const& applications);
    void setTitles(QList<TranslatedString> const& titles);
    void setDescriptions(QList<TranslatedString> const& descriptions);
    void setPreviewpictures(QList<PreviewPicture> const& previewPictures);
    void setCategories(QList<Category> const& categories);
    void setFlags(unsigned int const& flags);
    void setInstallinstances(QList<Package> const& installInstances);

  signals:
    void pathChanged(QString newPath);
    void idChanged(QString newId);
    void iconChanged(QString newIcon);
    void documentationInfoChanged(DocumentationInfo newDocumentationinfo);
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
    void previewPicturesChanged(QList<PreviewPicture> newPreviewpictures);
    void categoriesChanged(QList<Category> newCategories);
    void flagsChanged(unsigned int newFlags);
    void installInstancesChanged(QList<Package> newInstallinstances);

  private:
    QString _path;
    QString _id;
    QString _icon;
    DocumentationInfo _documentationInfo;
    QString _md5;
    QString _url;
    QString _vendor;
    qint64 _size;
    QDateTime _modified;
    int _rating;
    Author _author;
    Version _version;
    QList<Application> _applications;
    QList<TranslatedString> _titles;
    QList<TranslatedString> _descriptions;
    QList<PreviewPicture> _previewPictures;
    QList<Category> _categories;
    unsigned int _flags;
    QList<Package> _installInstances;

  };
}

#endif
