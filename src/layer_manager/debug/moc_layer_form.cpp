/****************************************************************************
** Meta object code from reading C++ file 'layer_form.h'
**
** Created: Mon 24. Oct 23:11:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../layer_form.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layer_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_layer_form[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x08,
      53,   11,   11,   11, 0x28,
      76,   11,   11,   11, 0x08,
     104,   11,   11,   11, 0x08,
     134,   11,   11,   11, 0x08,
     161,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_layer_form[] = {
    "layer_form\0\0n\0stateOfLayersChanged(QListWidgetItem*)\0"
    "stateOfLayersChanged()\0"
    "button_Select_all_clicked()\0"
    "button_Deselect_all_clicked()\0"
    "button_Set_lower_clicked()\0"
    "button_Set_upper_clicked()\0"
};

const QMetaObject layer_form::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_layer_form,
      qt_meta_data_layer_form, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &layer_form::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *layer_form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *layer_form::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_layer_form))
        return static_cast<void*>(const_cast< layer_form*>(this));
    return QDialog::qt_metacast(_clname);
}

int layer_form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateOfLayersChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: stateOfLayersChanged(); break;
        case 2: button_Select_all_clicked(); break;
        case 3: button_Deselect_all_clicked(); break;
        case 4: button_Set_lower_clicked(); break;
        case 5: button_Set_upper_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
