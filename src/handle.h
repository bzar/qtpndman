#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>

namespace QPndman
{
  class Handle : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString main READ getMain WRITE setMain NOTIFY mainChanged);
    Q_PROPERTY(QString error READ getError WRITE setError NOTIFY errorChanged);
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged);
    Q_PROPERTY(unsigned int flags READ getFlags WRITE setFlags NOTIFY flagsChanged);
    Q_PROPERTY(bool done READ getDone WRITE setDone NOTIFY doneChanged);

  public:
    Handle(QString const& main, QString const& error, QString const& url, unsigned int const& flags, bool const& done, QObject* parent = 0);
    Handle(Handle const& other);
    Handle& operator=(Handle const& other);

  public slots:
    QString getMain() const;
    QString getError() const;
    QString getUrl() const;
    unsigned int getFlags() const;
    bool getDone() const;

    void setMain(QString const& main);
    void setError(QString const& error);
    void setUrl(QString const& url);
    void setFlags(unsigned int const& flags);
    void setDone(bool const& done);

  signals:
    void mainChanged(QString newMain);
    void errorChanged(QString newError);
    void urlChanged(QString newUrl);
    void flagsChanged(unsigned int newFlags);
    void doneChanged(bool newDone);

  private:
    QString _main;
    QString _error;
    QString _url;
    unsigned int _flags;
    bool _done;

  };
}

#endif
