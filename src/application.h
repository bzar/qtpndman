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
    Q_PROPERTY(QList<TranslatedString> titles READ getTitles WRITE setTitles NOTIFY titlesChanged);
    Q_PROPERTY(QList<TranslatedString> descriptions READ getDescriptions WRITE setDescriptions NOTIFY descriptionsChanged);
    Q_PROPERTY(QList<License> licenses READ getLicenses WRITE setLicenses NOTIFY licensesChanged);
    Q_PROPERTY(QList<PreviewPicture> previewPictures READ getPreviewpictures WRITE setPreviewpictures NOTIFY previewPicturesChanged);
    Q_PROPERTY(QList<Category> categories READ getCategories WRITE setCategories NOTIFY categoriesChanged);
    Q_PROPERTY(QList<Association> associations READ getAssociations WRITE setAssociations NOTIFY associationsChanged);

  public:
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
    QList<TranslatedString> getTitles() const;
    QList<TranslatedString> getDescriptions() const;
    QList<License> getLicenses() const;
    QList<PreviewPicture> getPreviewpictures() const;
    QList<Category> getCategories() const;
    QList<Association> getAssociations() const;

    void setId(QString const& id);
    void setAppdata(QString const& appdata);
    void setIcon(QString const& icon);
    void setClockfrequency(int const& clockFrequency);
    void setAuthor(Author const& author);
    void setOsversion(Version const& osVersion);
    void setVersion(Version const& version);
    void setExecutioninfo(ExecutionInfo const& executionInfo);
    void setDocumentationinfo(DocumentationInfo const& documentationInfo);
    void setTitles(QList<TranslatedString> const& titles);
    void setDescriptions(QList<TranslatedString> const& descriptions);
    void setLicenses(QList<License> const& licenses);
    void setPreviewpictures(QList<PreviewPicture> const& previewPictures);
    void setCategories(QList<Category> const& categories);
    void setAssociations(QList<Association> const& associations);

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
    void titlesChanged(QList<TranslatedString> newTitles);
    void descriptionsChanged(QList<TranslatedString> newDescriptions);
    void licensesChanged(QList<License> newLicenses);
    void previewPicturesChanged(QList<PreviewPicture> newPreviewpictures);
    void categoriesChanged(QList<Category> newCategories);
    void associationsChanged(QList<Association> newAssociations);

  private:
    struct Data
    {
      Data(pndman_application const* p);
      
      QString id;
      QString appdata;
      QString icon;
      int clockFrequency;
      Author author;
      Version osVersion;
      Version version;
      ExecutionInfo executionInfo;
      DocumentationInfo documentationInfo;
      QList<TranslatedString> titles;
      QList<TranslatedString> descriptions;
      QList<License> licenses;
      QList<PreviewPicture> previewPictures;
      QList<Category> categories;
      QList<Association> associations;
    };
    
    QSharedPointer<Data> d;

  };
}

#endif
