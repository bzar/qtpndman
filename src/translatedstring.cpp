#include "translatedstring.h"

QPndman::TranslatedString::TranslatedString(QString const& language, QString const& content, QObject* parent) : QObject(parent), 
  _language(language), _content(content)
{
}

QPndman::TranslatedString::TranslatedString(pndman_translated const* p) : QObject(0), 
  _language(p->lang), _content(p->string)
{
}

QPndman::TranslatedString::TranslatedString(TranslatedString const& other) : QObject(0), 
  _language(other._language), _content(other._content)
{
}

QPndman::TranslatedString& QPndman::TranslatedString::operator=(TranslatedString const& other)
{
  if(&other == this)
    return *this;
  
  _language = other._language;
  _content = other._content;
  
  return *this;
}

QString QPndman::TranslatedString::getLanguage() const
{
  return _language;
}
QString QPndman::TranslatedString::getContent() const
{
  return _content;
}

void QPndman::TranslatedString::setLanguage(QString const& language)
{
  if(language != _language) 
  {
    _language = language; 
    emit languageChanged(_language);
  }
}
void QPndman::TranslatedString::setContent(QString const& content)
{
  if(content != _content) 
  {
    _content = content; 
    emit contentChanged(_content);
  }
}
