#include "application.h"
#include "util.h"

QPndman::Application::Application(pndman_application const* p) : QObject(0), d(new Data(p))
{
}
QPndman::Application::Data::Data(pndman_application const* p) : 
  id(p->id), appdata(p->appdata), icon(p->icon), clockFrequency(p->frequency), author(&(p->author)), osVersion(&(p->osversion)), version(&(p->version)), 
  executionInfo(&(p->exec)), documentationInfo(&(p->info)), 
  titles(makeQList<pndman_translated const, TranslatedString>(p->title)),
  descriptions(makeQList<pndman_translated const, TranslatedString>(p->description)), 
  licenses(makeQList<pndman_license const, License>(p->license)), 
  previewPictures(makeQList<pndman_previewpic const, PreviewPicture>(p->previewpic)), 
  categories(makeQList<pndman_category const, Category>(p->category)), 
  associations(makeQList<pndman_association const, Association>(p->association))
{
}

QPndman::Application::Application(Application const& other) : QObject(0), d(other.d)
{
}

QPndman::Application& QPndman::Application::operator=(Application const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::Application::getId() const
{
  return d->id;
}
QString QPndman::Application::getAppdata() const
{
  return d->appdata;
}
QString QPndman::Application::getIcon() const
{
  return d->icon;
}
int QPndman::Application::getClockfrequency() const
{
  return d->clockFrequency;
}
QPndman::Author QPndman::Application::getAuthor() const
{
  return d->author;
}
QPndman::Version QPndman::Application::getOsversion() const
{
  return d->osVersion;
}
QPndman::Version QPndman::Application::getVersion() const
{
  return d->version;
}
QPndman::ExecutionInfo QPndman::Application::getExecutioninfo() const
{
  return d->executionInfo;
}
QPndman::DocumentationInfo QPndman::Application::getDocumentationinfo() const
{
  return d->documentationInfo;
}
QList<QPndman::TranslatedString> QPndman::Application::getTitles() const
{
  return d->titles;
}
QList<QPndman::TranslatedString> QPndman::Application::getDescriptions() const
{
  return d->descriptions;
}
QList<QPndman::License> QPndman::Application::getLicenses() const
{
  return d->licenses;
}
QList<QPndman::PreviewPicture> QPndman::Application::getPreviewpictures() const
{
  return d->previewPictures;
}
QList<QPndman::Category> QPndman::Application::getCategories() const
{
  return d->categories;
}
QList<QPndman::Association> QPndman::Application::getAssociations() const
{
  return d->associations;
}

void QPndman::Application::setId(QString const& id)
{
  if(id != d->id) 
  {
    d->id = id; 
    emit idChanged(d->id);
  }
}
void QPndman::Application::setAppdata(QString const& appdata)
{
  if(appdata != d->appdata) 
  {
    d->appdata = appdata; 
    emit appdataChanged(d->appdata);
  }
}
void QPndman::Application::setIcon(QString const& icon)
{
  if(icon != d->icon) 
  {
    d->icon = icon; 
    emit iconChanged(d->icon);
  }
}
void QPndman::Application::setClockfrequency(int const& clockFrequency)
{
  if(clockFrequency != d->clockFrequency) 
  {
    d->clockFrequency = clockFrequency; 
    emit clockFrequencyChanged(d->clockFrequency);
  }
}
void QPndman::Application::setAuthor(Author const& author)
{
  d->author = author; 
  emit authorChanged(d->author);
}
void QPndman::Application::setOsversion(Version const& osVersion)
{
  d->osVersion = osVersion; 
  emit osVersionChanged(d->osVersion);
}
void QPndman::Application::setVersion(Version const& version)
{
  d->version = version; 
  emit versionChanged(d->version);
}
void QPndman::Application::setExecutioninfo(ExecutionInfo const& executionInfo)
{
  d->executionInfo = executionInfo; 
  emit executionInfoChanged(d->executionInfo);
}
void QPndman::Application::setDocumentationinfo(DocumentationInfo const& documentationInfo)
{
  d->documentationInfo = documentationInfo; 
  emit documentationInfoChanged(d->documentationInfo);
}
void QPndman::Application::setTitles(QList<TranslatedString> const& titles)
{
  d->titles = titles; 
  emit titlesChanged(d->titles);
}
void QPndman::Application::setDescriptions(QList<TranslatedString> const& descriptions)
{
  d->descriptions = descriptions; 
  emit descriptionsChanged(d->descriptions);
}
void QPndman::Application::setLicenses(QList<License> const& licenses)
{
  d->licenses = licenses; 
  emit licensesChanged(d->licenses);
}
void QPndman::Application::setPreviewpictures(QList<PreviewPicture> const& previewPictures)
{
  d->previewPictures = previewPictures; 
  emit previewPicturesChanged(d->previewPictures);
}
void QPndman::Application::setCategories(QList<Category> const& categories)
{
  d->categories = categories; 
  emit categoriesChanged(d->categories);
}
void QPndman::Application::setAssociations(QList<Association> const& associations)
{
  d->associations = associations; 
  emit associationsChanged(d->associations);
}
