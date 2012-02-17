#include "application.h"
#include "util.h"

QPndman::Application::Application(QString const& id, QString const& appdata, QString const& icon, int const& clockFrequency, Author const& author, Version const& osVersion, Version const& version, ExecutionInfo const& executionInfo, DocumentationInfo const& documentationInfo, QList< QSharedPointer<TranslatedString> > const& titles, QList< QSharedPointer<TranslatedString> > const& descriptions, QList< QSharedPointer<License> > const& licenses, QList< QSharedPointer<PreviewPicture> > const& previewPictures, QList< QSharedPointer<Category> > const& categories, QList< QSharedPointer<Association> > const& associations, QObject* parent) : QObject(parent), 
  _id(id), _appdata(appdata), _icon(icon), _clockFrequency(clockFrequency), _author(author), _osVersion(osVersion), _version(version), _executionInfo(executionInfo), _documentationInfo(documentationInfo), _titles(titles), _descriptions(descriptions), _licenses(licenses), _previewPictures(previewPictures), _categories(categories), _associations(associations)
{
}

QPndman::Application::Application(pndman_application const* p) : QObject(0), 
  _id(p->id), _appdata(p->appdata), _icon(p->icon), _clockFrequency(p->frequency), _author(&(p->author)), _osVersion(&(p->osversion)), _version(&(p->version)), 
  _executionInfo(&(p->exec)), _documentationInfo(&(p->info)), 
  _titles(makeQList<pndman_translated, TranslatedString>(p->title)),
  _descriptions(makeQList<pndman_translated, TranslatedString>(p->description)), 
  _licenses(makeQList<pndman_license, License>(p->license)), 
  _previewPictures(makeQList<pndman_previewpic, PreviewPicture>(p->previewpic)), 
  _categories(makeQList<pndman_category, Category>(p->category)), 
  _associations(makeQList<pndman_association, Association>(p->association))
{
}

QPndman::Application::Application(Application const& other) : QObject(0), 
  _id(other._id), _appdata(other._appdata), _icon(other._icon), _clockFrequency(other._clockFrequency), _author(other._author), _osVersion(other._osVersion), _version(other._version), _executionInfo(other._executionInfo), _documentationInfo(other._documentationInfo), _titles(other._titles), _descriptions(other._descriptions), _licenses(other._licenses), _previewPictures(other._previewPictures), _categories(other._categories), _associations(other._associations)
{
}

QPndman::Application& QPndman::Application::operator=(Application const& other)
{
  if(&other == this)
    return *this;
  
  _id = other._id;
  _appdata = other._appdata;
  _icon = other._icon;
  _clockFrequency = other._clockFrequency;
  _author = other._author;
  _osVersion = other._osVersion;
  _version = other._version;
  _executionInfo = other._executionInfo;
  _documentationInfo = other._documentationInfo;
  _titles = other._titles;
  _descriptions = other._descriptions;
  _licenses = other._licenses;
  _previewPictures = other._previewPictures;
  _categories = other._categories;
  _associations = other._associations;
  
  return *this;
}

QString QPndman::Application::getId() const
{
  return _id;
}
QString QPndman::Application::getAppdata() const
{
  return _appdata;
}
QString QPndman::Application::getIcon() const
{
  return _icon;
}
int QPndman::Application::getClockfrequency() const
{
  return _clockFrequency;
}
QPndman::Author QPndman::Application::getAuthor() const
{
  return _author;
}
QPndman::Version QPndman::Application::getOsversion() const
{
  return _osVersion;
}
QPndman::Version QPndman::Application::getVersion() const
{
  return _version;
}
QPndman::ExecutionInfo QPndman::Application::getExecutioninfo() const
{
  return _executionInfo;
}
QPndman::DocumentationInfo QPndman::Application::getDocumentationinfo() const
{
  return _documentationInfo;
}
QList< QSharedPointer<QPndman::TranslatedString> > QPndman::Application::getTitles() const
{
  return _titles;
}
QList< QSharedPointer<QPndman::TranslatedString> > QPndman::Application::getDescriptions() const
{
  return _descriptions;
}
QList< QSharedPointer<QPndman::License> > QPndman::Application::getLicenses() const
{
  return _licenses;
}
QList< QSharedPointer<QPndman::PreviewPicture> > QPndman::Application::getPreviewpictures() const
{
  return _previewPictures;
}
QList< QSharedPointer<QPndman::Category> > QPndman::Application::getCategories() const
{
  return _categories;
}
QList< QSharedPointer<QPndman::Association> > QPndman::Application::getAssociations() const
{
  return _associations;
}

void QPndman::Application::setId(QString const& id)
{
  if(id != _id) 
  {
    _id = id; 
    emit idChanged(_id);
  }
}
void QPndman::Application::setAppdata(QString const& appdata)
{
  if(appdata != _appdata) 
  {
    _appdata = appdata; 
    emit appdataChanged(_appdata);
  }
}
void QPndman::Application::setIcon(QString const& icon)
{
  if(icon != _icon) 
  {
    _icon = icon; 
    emit iconChanged(_icon);
  }
}
void QPndman::Application::setClockfrequency(int const& clockFrequency)
{
  if(clockFrequency != _clockFrequency) 
  {
    _clockFrequency = clockFrequency; 
    emit clockFrequencyChanged(_clockFrequency);
  }
}
void QPndman::Application::setAuthor(Author const& author)
{
  _author = author; 
  emit authorChanged(_author);
}
void QPndman::Application::setOsversion(Version const& osVersion)
{
  _osVersion = osVersion; 
  emit osVersionChanged(_osVersion);
}
void QPndman::Application::setVersion(Version const& version)
{
  _version = version; 
  emit versionChanged(_version);
}
void QPndman::Application::setExecutioninfo(ExecutionInfo const& executionInfo)
{
  _executionInfo = executionInfo; 
  emit executionInfoChanged(_executionInfo);
}
void QPndman::Application::setDocumentationinfo(DocumentationInfo const& documentationInfo)
{
  _documentationInfo = documentationInfo; 
  emit documentationInfoChanged(_documentationInfo);
}
void QPndman::Application::setTitles(QList< QSharedPointer<TranslatedString> > const& titles)
{
  _titles = titles; 
  emit titlesChanged(_titles);
}
void QPndman::Application::setDescriptions(QList< QSharedPointer<TranslatedString> > const& descriptions)
{
  _descriptions = descriptions; 
  emit descriptionsChanged(_descriptions);
}
void QPndman::Application::setLicenses(QList< QSharedPointer<License> > const& licenses)
{
  _licenses = licenses; 
  emit licensesChanged(_licenses);
}
void QPndman::Application::setPreviewpictures(QList< QSharedPointer<PreviewPicture> > const& previewPictures)
{
  _previewPictures = previewPictures; 
  emit previewPicturesChanged(_previewPictures);
}
void QPndman::Application::setCategories(QList< QSharedPointer<Category> > const& categories)
{
  _categories = categories; 
  emit categoriesChanged(_categories);
}
void QPndman::Application::setAssociations(QList< QSharedPointer<Association> > const& associations)
{
  _associations = associations; 
  emit associationsChanged(_associations);
}
