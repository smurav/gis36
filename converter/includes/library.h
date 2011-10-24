#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QtXmlPatterns/QXmlQuery>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QXmlStreamAttributes>
#include <QtCore/qglobal.h>

#if defined(GIS36_LIBRARY_EXPORTS)
#  define GIS36_LIBRARY_API Q_DECL_EXPORT
#else
#  define GIS36_LIBRARY_API Q_DECL_IMPORT
#endif


class GIS36_LIBRARY_API Library : public QObject {
  Q_OBJECT

 public:
    Library();

    virtual int Sum(int a, int b);
    virtual QString Parser(const QString &prs);
};

#endif // LIBRARY_H
