#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QDateTime>

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

    Q_ENUMS(QPndman::Enum::InstallLocation)
    Q_PROPERTY(QString path READ getPath CONSTANT)
    Q_PROPERTY(QString id READ getId CONSTANT)
    Q_PROPERTY(QString icon READ getIcon CONSTANT)
    Q_PROPERTY(QString info READ getInfo CONSTANT)
    Q_PROPERTY(QString md5 READ getMd5 CONSTANT)
    Q_PROPERTY(QString url READ getUrl CONSTANT)
    Q_PROPERTY(QString vendor READ getVendor CONSTANT)
    Q_PROPERTY(QString mount READ getMount CONSTANT)
    Q_PROPERTY(qint64 size READ getSize CONSTANT)
    Q_PROPERTY(QDateTime modified READ getModified CONSTANT)
    Q_PROPERTY(int rating READ getRating CONSTANT)
    Q_PROPERTY(QPndman::Author* author READ getAuthor CONSTANT)
    Q_PROPERTY(QPndman::Version* version READ getVersion CONSTANT)
    Q_PROPERTY(QList<QPndman::Application*> applications READ getApplications CONSTANT)
    Q_PROPERTY(QList<QPndman::TranslatedString*> titles READ getTitles CONSTANT)
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QList<QPndman::TranslatedString*> descriptions READ getDescriptions CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)
    Q_PROPERTY(QList<QPndman::Category*> categories READ getCategories CONSTANT)
    Q_PROPERTY(QList<QPndman::PreviewPicture*> previewPictures READ getPreviewPictures CONSTANT)
    Q_PROPERTY(QList<QPndman::Package*> installInstances READ getInstallInstances CONSTANT)
    Q_PROPERTY(QPndman::Package* upgradeCandidate READ getUpgradeCandidate CONSTANT)


  public:
    Package(Context* context, pndman_package* p, QObject* parent = 0, bool initUpgradeCandidate = true);

    pndman_package* getPndmanPackage() const;
    
    Q_INVOKABLE InstallHandle* install(Device* device, Enum::InstallLocation location, bool force = false);
    Q_INVOKABLE UpgradeHandle* upgrade(bool force = false);
    bool crawl(bool full = false);

    QString getPath() const;
    QString getId() const;
    QString getIcon() const;
    QString getInfo() const;
    QString getMd5() const;
    QString getUrl() const;
    QString getVendor() const;
    QString getMount() const;
    qint64 getSize() const;
    QDateTime getModified() const;
    int getRating() const;
    Author* getAuthor() const;
    Version* getVersion() const;
    QList<Application*> getApplications() const;
    QList<TranslatedString*> getTitles() const;
    QString getTitle() const;
    QList<TranslatedString*> getDescriptions() const;
    QString getDescription() const;
    QList<Category*> getCategories() const;
    QList<PreviewPicture*> getPreviewPictures() const;
    QList<Package*> getInstallInstances() const;
    Package* getUpgradeCandidate() const;

  protected:
    pndman_package* package;
    Context* context;

    QString path;
    QString id;
    QString icon;
    QString info;
    QString md5;
    QString url;
    QString vendor;
    QString mount;
    qint64 size;
    QDateTime modified;
    int rating;
    Author* author;
    Version* version;
    QList<Application*> applications;
    QList<TranslatedString*> titles;
    QList<TranslatedString*> descriptions;
    QList<Category*> categories;
    QList<PreviewPicture*> previewPictures;
    QList<Package*> installInstances;
    Package* upgradeCandidate;
  };
}

#endif
