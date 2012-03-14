#include "application.h"
#include "util.h"

QPndman::Application::Application(pndman_application const* p, QObject *parent) : QObject(parent),
  id(p->id), appdata(p->appdata), icon(p->icon), clockFrequency(p->frequency),
  author(new Author(&p->author, this)),
  osVersion(new Version(&p->osversion, this)),
  version(new Version(&p->version, this)),
  executionInfo(new ExecutionInfo(&p->exec, this)),
  documentationInfo(new DocumentationInfo(&p->info, this)),
  titles(makeQListPtr<pndman_translated const, TranslatedString>(p->title, this)),
  descriptions(makeQListPtr<pndman_translated const, TranslatedString>(p->description, this)),
  licenses(makeQListPtr<pndman_license const, License>(p->license, this)),
  previewPictures(makeQListPtr<pndman_previewpic const, PreviewPicture>(p->previewpic, this)),
  categories(makeQListPtr<pndman_category const, Category>(p->category, this)),
  associations(makeQListPtr<pndman_association const, Association>(p->association, this))
{
}

QString QPndman::Application::getId() const
{
  return id;
}
QString QPndman::Application::getAppdata() const
{
  return appdata;
}
QString QPndman::Application::getIcon() const
{
  return icon;
}
int QPndman::Application::getClockfrequency() const
{
  return clockFrequency;
}
QPndman::Author* QPndman::Application::getAuthor() const
{
  return author;
}
QPndman::Version* QPndman::Application::getOsversion() const
{
  return osVersion;
}
QPndman::Version* QPndman::Application::getVersion() const
{
  return version;
}
QPndman::ExecutionInfo* QPndman::Application::getExecutioninfo() const
{
  return executionInfo;
}
QPndman::DocumentationInfo* QPndman::Application::getDocumentationinfo() const
{
  return documentationInfo;
}
QList<QPndman::TranslatedString*> QPndman::Application::getTitles() const
{
  return titles;
}
QList<QPndman::TranslatedString*> QPndman::Application::getDescriptions() const
{
  return descriptions;
}
QList<QPndman::License*> QPndman::Application::getLicenses() const
{
  return licenses;
}
QList<QPndman::PreviewPicture*> QPndman::Application::getPreviewpictures() const
{
  return previewPictures;
}
QList<QPndman::Category*> QPndman::Application::getCategories() const
{
  return categories;
}
QList<QPndman::Association*> QPndman::Application::getAssociations() const
{
  return associations;
}
