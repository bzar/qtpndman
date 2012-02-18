#include "translatedstring.h"

QPndman::TranslatedString::TranslatedString(pndman_translated const* p) : QObject(0), d(new Data(p))
{
  
}
QPndman::TranslatedString::Data::Data(pndman_translated const* p) : 
  language(p->lang), content(p->string)
{
}

QPndman::TranslatedString::TranslatedString(TranslatedString const& other) : QObject(0), d(other.d)
{
}

QPndman::TranslatedString& QPndman::TranslatedString::operator=(TranslatedString const& other)
{
  if(&other == this)
    return *this;
  
  d = other.d;
  
  return *this;
}

QString QPndman::TranslatedString::getLanguage() const
{
  return d->language;
}
QString QPndman::TranslatedString::getContent() const
{
  return d->content;
}

void QPndman::TranslatedString::setLanguage(QString const& language)
{
  if(language != d->language) 
  {
    d->language = language; 
    emit languageChanged(d->language);
  }
}
void QPndman::TranslatedString::setContent(QString const& content)
{
  if(content != d->content) 
  {
    d->content = content; 
    emit contentChanged(d->content);
  }
}
