#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>

#ifdef GIS36_LIBRARY_EXPORTS
  #if defined(WIN32) || defined(_WIN32)
    #define GIS36_LIBRARY_API __declspec(dllexport)
  #else
    #define GIS36_LIBRARY_API
  #endif
#else
  #if defined(WIN32) || defined(_WIN32)
    #define GIS36_LIBRARY_API __declspec(dllimport)
  #else
    #define GIS36_LIBRARY_API
  #endif
#endif

class GIS36_LIBRARY_API Library : public QObject {
  Q_OBJECT

 public:
  Library(QObject *parent = NULL);

  int Sum(int a, int b);
};

#endif // LIBRARY_H
