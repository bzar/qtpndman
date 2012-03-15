#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

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

    Q_PROPERTY(QString id READ getId CONSTANT)
    Q_PROPERTY(QString appdata READ getAppdata CONSTANT)
    Q_PROPERTY(QString icon READ getIcon CONSTANT)
    Q_PROPERTY(int clockFrequency READ getClockfrequency CONSTANT)
    Q_PROPERTY(QPndman::Author* author READ getAuthor CONSTANT)
    Q_PROPERTY(QPndman::Version* osVersion READ getOsversion CONSTANT)
    Q_PROPERTY(QPndman::Version* version READ getVersion CONSTANT)
    Q_PROPERTY(QPndman::ExecutionInfo* executionInfo READ getExecutioninfo CONSTANT)
    Q_PROPERTY(QPndman::DocumentationInfo* documentationInfo READ getDocumentationinfo CONSTANT)
    Q_PROPERTY(QList<QPndman::TranslatedString*> titles READ getTitles CONSTANT)
    Q_PROPERTY(QList<QPndman::TranslatedString*> descriptions READ getDescriptions CONSTANT)
    Q_PROPERTY(QList<QPndman::License*> licenses READ getLicenses CONSTANT)
    Q_PROPERTY(QList<QPndman::PreviewPicture*> previewPictures READ getPreviewpictures CONSTANT)
    Q_PROPERTY(QList<QPndman::Category*> categories READ getCategories CONSTANT)
    Q_PROPERTY(QList<QPndman::Association*> associations READ getAssociations CONSTANT)

  public:
    Application(pndman_application const* p, QObject* parent = 0);

    QString getId() const;
    QString getAppdata() const;
    QString getIcon() const;
    int getClockfrequency() const;
    Author* getAuthor() const;
    Version* getOsversion() const;
    Version* getVersion() const;
    ExecutionInfo* getExecutioninfo() const;
    DocumentationInfo* getDocumentationinfo() const;
    QList<TranslatedString*> getTitles() const;
    QList<TranslatedString*> getDescriptions() const;
    QList<License*> getLicenses() const;
    QList<PreviewPicture*> getPreviewpictures() const;
    QList<Category*> getCategories() const;
    QList<Association*> getAssociations() const;

  private:
    QString id;
    QString appdata;
    QString icon;
    int clockFrequency;
    Author* author;
    Version* osVersion;
    Version* version;
    ExecutionInfo* executionInfo;
    DocumentationInfo* documentationInfo;
    QList<TranslatedString*> titles;
    QList<TranslatedString*> descriptions;
    QList<License*> licenses;
    QList<PreviewPicture*> previewPictures;
    QList<Category*> categories;
    QList<Association*> associations;
  };
}

#endif
