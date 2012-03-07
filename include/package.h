#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QDateTime>
#include <QSharedPointer>
#include <QMetaType>

#include "author.h"
#include "version.h"
#include "application.h"
#include "translatedstring.h"
#include "category.h"
#include "enums.h"

#include "pndman.h"

namespace QPndman
{
  class InstallHandle;
  class UpgradeHandle;
  class Device;
  class Context;
  
  class Package : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString path READ getPath NOTIFY pathChanged)
    Q_PROPERTY(QString id READ getId NOTIFY idChanged)
    Q_PROPERTY(QString icon READ getIcon NOTIFY iconChanged)
    Q_PROPERTY(QString info READ getInfo NOTIFY infoChanged)
    Q_PROPERTY(QString md5 READ getMd5 NOTIFY md5Changed)
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
    Q_PROPERTY(QString vendor READ getVendor NOTIFY vendorChanged)
    Q_PROPERTY(QString device READ getDevice NOTIFY deviceChanged)
    Q_PROPERTY(qint64 size READ getSize NOTIFY sizeChanged)
    Q_PROPERTY(QDateTime modified READ getModified NOTIFY modifiedChanged)
    Q_PROPERTY(int rating READ getRating NOTIFY ratingChanged)
    Q_PROPERTY(Author author READ getAuthor NOTIFY authorChanged)
    Q_PROPERTY(Version version READ getVersion NOTIFY versionChanged)
    Q_PROPERTY(QList<Application> applications READ getApplications NOTIFY applicationsChanged)
    Q_PROPERTY(QList<TranslatedString> titles READ getTitles NOTIFY titlesChanged)
    Q_PROPERTY(QString title READ getTitle NOTIFY titlesChanged)
    Q_PROPERTY(QList<TranslatedString> descriptions READ getDescriptions NOTIFY descriptionsChanged)
    Q_PROPERTY(QString description READ getDescription NOTIFY descriptionsChanged)
    Q_PROPERTY(QList<Category> categories READ getCategories NOTIFY categoriesChanged)
    Q_PROPERTY(QList<Package> installInstances READ getInstallInstances NOTIFY installInstancesChanged)

    Q_ENUMS(QPndman::Enum::InstallLocation)

  public:
    explicit Package(QObject* parent = 0);
    Package(Context* context, pndman_package* p, bool initUpgradeCandidate = true);
    Package(Package const& other);
    
    Package& operator=(Package const& other);

    pndman_package* getPndmanPackage() const;
    bool isNull() const;
    
    InstallHandle* install(Device* device, Enum::InstallLocation location, bool force = false);
    UpgradeHandle* upgrade(bool force = false);
    
  public slots:
    QString getPath() const;
    QString getId() const;
    QString getIcon() const;
    QString getInfo() const;
    QString getMd5() const;
    QString getUrl() const;
    QString getVendor() const;
    QString getDevice() const;
    qint64 getSize() const;
    QDateTime getModified() const;
    int getRating() const;
    Author getAuthor() const;
    Version getVersion() const;
    QList<Application> getApplications() const;
    QList<TranslatedString> getTitles() const;
    QString getTitle() const;
    QList<TranslatedString> getDescriptions() const;
    QString getDescription() const;
    QList<Category> getCategories() const;
    QList<Package> getInstallInstances() const;
    Package* getUpgradeCandidate() const;

  signals:
    void pathChanged(QString newPath);
    void idChanged(QString newId);
    void iconChanged(QString newIcon);
    void infoChanged(QString newInfo);
    void md5Changed(QString newMd5);
    void urlChanged(QString newUrl);
    void vendorChanged(QString newVendor);
    void deviceChanged(QString newDevice);
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
    void upgradeCandidateChanged(Package* newUpgradeCandidate);

  protected:
    void setPndmanPackage(pndman_package* package);
    void setPath(QString const& path);
    void setId(QString const& id);
    void setIcon(QString const& icon);
    void setInfo(QString const& info);
    void setMd5(QString const& md5);
    void setUrl(QString const& url);
    void setVendor(QString const& vendor);
    void setDevice(QString const& device);
    void setSize(qint64 const& size);
    void setModified(QDateTime const& modified);
    void setRating(int const& rating);
    void setAuthor(Author const& author);
    void setVersion(Version const& version);
    void setApplications(QList<Application> const& applications);
    void setTitles(QList<TranslatedString> const& titles);
    void setDescriptions(QList<TranslatedString> const& descriptions);
    void setCategories(QList<Category> const& categories);
    void setInstallinstances(QList<Package> const& installInstances);
    void setUpgradeCandidate(Package* upgradeCandidate);
    
  private:
    struct Data
    {
        Data(Context* context, pndman_package* p);
        pndman_package* package;
        Context* context;

        QString path;
        QString id;
        QString icon;
        QString info;
        QString md5;
        QString url;
        QString vendor;
        QString device;
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
        Package* upgradeCandidate;
      };

    QSharedPointer<Data> d;
  };
}

Q_DECLARE_METATYPE(QPndman::Package);

#endif
