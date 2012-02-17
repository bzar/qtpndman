#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QSharedPointer>

#include "executioninfo.h"
#include "documentationinfo.h"
#include "author.h"
#include "version.h"
#include "license.h"
#include "translatedstring.h"
#include "previewpicture.h"
#include "category.h"
#include "association.h"

#include "pndman.h"

namespace QPndman
{
  class Application : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged);
    Q_PROPERTY(QString appdata READ getAppdata WRITE setAppdata NOTIFY appdataChanged);
    Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
    Q_PROPERTY(int clockFrequency READ getClockfrequency WRITE setClockfrequency NOTIFY clockFrequencyChanged);
    Q_PROPERTY(Author author READ getAuthor WRITE setAuthor NOTIFY authorChanged);
    Q_PROPERTY(Version osVersion READ getOsversion WRITE setOsversion NOTIFY osVersionChanged);
    Q_PROPERTY(Version version READ getVersion WRITE setVersion NOTIFY versionChanged);
    Q_PROPERTY(ExecutionInfo executionInfo READ getExecutioninfo WRITE setExecutioninfo NOTIFY executionInfoChanged);
    Q_PROPERTY(DocumentationInfo documentationInfo READ getDocumentationinfo WRITE setDocumentationinfo NOTIFY documentationInfoChanged);
    Q_PROPERTY(QList< QSharedPointer<TranslatedString> > titles READ getTitles WRITE setTitles NOTIFY titlesChanged);
    Q_PROPERTY(QList< QSharedPointer<TranslatedString> > descriptions READ getDescriptions WRITE setDescriptions NOTIFY descriptionsChanged);
    Q_PROPERTY(QList< QSharedPointer<License> > licenses READ getLicenses WRITE setLicenses NOTIFY licensesChanged);
    Q_PROPERTY(QList< QSharedPointer<PreviewPicture> > previewPictures READ getPreviewpictures WRITE setPreviewpictures NOTIFY previewPicturesChanged);
    Q_PROPERTY(QList< QSharedPointer<Category> > categories READ getCategories WRITE setCategories NOTIFY categoriesChanged);
    Q_PROPERTY(QList< QSharedPointer<Association> > associations READ getAssociations WRITE setAssociations NOTIFY associationsChanged);

  public:
    Application(QString const& id, QString const& appdata, QString const& icon, int const& clockFrequency, Author const& author, Version const& osVersion, Version const& version, ExecutionInfo const& executionInfo, DocumentationInfo const& documentationInfo, QList< QSharedPointer<TranslatedString> > const& titles, QList< QSharedPointer<TranslatedString> > const& descriptions, QList< QSharedPointer<License> > const& licenses, QList< QSharedPointer<PreviewPicture> > const& previewPictures, QList< QSharedPointer<Category> > const& categories, QList< QSharedPointer<Association> > const& associations, QObject* parent = 0);
    Application(pndman_application const* p);
    Application(Application const& other);
    Application& operator=(Application const& other);

  public slots:
    QString getId() const;
    QString getAppdata() const;
    QString getIcon() const;
    int getClockfrequency() const;
    Author getAuthor() const;
    Version getOsversion() const;
    Version getVersion() const;
    ExecutionInfo getExecutioninfo() const;
    DocumentationInfo getDocumentationinfo() const;
    QList< QSharedPointer<TranslatedString> > getTitles() const;
    QList< QSharedPointer<TranslatedString> > getDescriptions() const;
    QList< QSharedPointer<License> > getLicenses() const;
    QList< QSharedPointer<PreviewPicture> > getPreviewpictures() const;
    QList< QSharedPointer<Category> > getCategories() const;
    QList< QSharedPointer<Association> > getAssociations() const;

    void setId(QString const& id);
    void setAppdata(QString const& appdata);
    void setIcon(QString const& icon);
    void setClockfrequency(int const& clockFrequency);
    void setAuthor(Author const& author);
    void setOsversion(Version const& osVersion);
    void setVersion(Version const& version);
    void setExecutioninfo(ExecutionInfo const& executionInfo);
    void setDocumentationinfo(DocumentationInfo const& documentationInfo);
    void setTitles(QList< QSharedPointer<TranslatedString> > const& titles);
    void setDescriptions(QList< QSharedPointer<TranslatedString> > const& descriptions);
    void setLicenses(QList< QSharedPointer<License> > const& licenses);
    void setPreviewpictures(QList< QSharedPointer<PreviewPicture> > const& previewPictures);
    void setCategories(QList< QSharedPointer<Category> > const& categories);
    void setAssociations(QList< QSharedPointer<Association> > const& associations);

  signals:
    void idChanged(QString newId);
    void appdataChanged(QString newAppdata);
    void iconChanged(QString newIcon);
    void clockFrequencyChanged(int newClockfrequency);
    void authorChanged(Author newAuthor);
    void osVersionChanged(Version newOsversion);
    void versionChanged(Version newVersion);
    void executionInfoChanged(ExecutionInfo newExecutioninfo);
    void documentationInfoChanged(DocumentationInfo newDocumentationinfo);
    void titlesChanged(QList< QSharedPointer<TranslatedString> > newTitles);
    void descriptionsChanged(QList< QSharedPointer<TranslatedString> > newDescriptions);
    void licensesChanged(QList< QSharedPointer<License> > newLicenses);
    void previewPicturesChanged(QList< QSharedPointer<PreviewPicture> > newPreviewpictures);
    void categoriesChanged(QList< QSharedPointer<Category> > newCategories);
    void associationsChanged(QList< QSharedPointer<Association> > newAssociations);

  private:
    QString _id;
    QString _appdata;
    QString _icon;
    int _clockFrequency;
    Author _author;
    Version _osVersion;
    Version _version;
    ExecutionInfo _executionInfo;
    DocumentationInfo _documentationInfo;
    QList< QSharedPointer<TranslatedString> > _titles;
    QList< QSharedPointer<TranslatedString> > _descriptions;
    QList< QSharedPointer<License> > _licenses;
    QList< QSharedPointer<PreviewPicture> > _previewPictures;
    QList< QSharedPointer<Category> > _categories;
    QList< QSharedPointer<Association> > _associations;

  };
}

#endif
