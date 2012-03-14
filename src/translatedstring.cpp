#include "translatedstring.h"

QPndman::TranslatedString::TranslatedString(pndman_translated const* p, QObject* parent) : QObject(parent),
language(p->lang), content(p->string)
{
  
}

QString QPndman::TranslatedString::getLanguage() const
{
  return language;
}
QString QPndman::TranslatedString::getContent() const
{
  return content;
}

