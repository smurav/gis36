/****************************************************************************
** Meta object code from reading C++ file 'search_by_region.h'
**
** Created: Thu 27. Oct 02:58:53 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../search_by_region.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search_by_region.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SearchByRegion[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SearchByRegion[] = {
    "SearchByRegion\0\0Cafe()\0"
};

const QMetaObject SearchByRegion::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SearchByRegion,
      qt_meta_data_SearchByRegion, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SearchByRegion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SearchByRegion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SearchByRegion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchByRegion))
        return static_cast<void*>(const_cast< SearchByRegion*>(this));
    if (!strcmp(_clname, "PluginInterface"))
        return static_cast< PluginInterface*>(const_cast< SearchByRegion*>(this));
    if (!strcmp(_clname, "com.gis36.PluginInterface/1.0"))
        return static_cast< PluginInterface*>(const_cast< SearchByRegion*>(this));
    return QObject::qt_metacast(_clname);
}

int SearchByRegion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Cafe(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
