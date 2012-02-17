#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QObject>

#include "pndman.h"

namespace QPndman
{
  class Association : public QObject
  {
  Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString fileType READ getFiletype WRITE setFiletype NOTIFY fileTypeChanged);
    Q_PROPERTY(QString exec READ getExec WRITE setExec NOTIFY execChanged);

  public:
    Association(QString const& name, QString const& fileType, QString const& exec, QObject* parent = 0);
    Association(pndman_association const* p);
    Association(Association const& other);
    Association& operator=(Association const& other);

  public slots:
    QString getName() const;
    QString getFiletype() const;
    QString getExec() const;

    void setName(QString const& name);
    void setFiletype(QString const& fileType);
    void setExec(QString const& exec);

  signals:
    void nameChanged(QString newName);
    void fileTypeChanged(QString newFiletype);
    void execChanged(QString newExec);

  private:
    QString _name;
    QString _fileType;
    QString _exec;

  };
}

#endif
