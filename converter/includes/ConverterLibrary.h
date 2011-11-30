#ifndef CONVERTERLIBRARY_H
#define CONVERTERLIBRARY_H

#include <QObject>
#include <QtXmlPatterns/QXmlQuery>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QXmlStreamAttributes>
#include <QtCore/QXmlStreamAttributes>
#include <QtCore/qglobal.h>

#if defined(GIS36_LIBRARY_EXPORTS)
#  define GIS36_LIBRARY_API Q_DECL_EXPORT
#else
#  define GIS36_LIBRARY_API Q_DECL_IMPORT
#endif


class GIS36_LIBRARY_API ConverterLibrary : public QObject {
  Q_OBJECT

 public:
    ConverterLibrary();

    virtual QString Parser(const QString &file);
};

#endif // CONVERTERLIBRARY_H
