/****************************************************************************
** Meta object code from reading C++ file 'values_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "values_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'values_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_values_window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      28,   14,   14,   14, 0x0a,
      42,   14,   14,   14, 0x0a,
      54,   14,   14,   14, 0x0a,
      67,   14,   14,   14, 0x0a,
      78,   14,   14,   14, 0x0a,
      89,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_values_window[] = {
    "values_window\0\0ascendName()\0descendName()\0"
    "ascendVal()\0descendVal()\0hide_win()\0"
    "show_win()\0update_win()\0"
};

void values_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        values_window *_t = static_cast<values_window *>(_o);
        switch (_id) {
        case 0: _t->ascendName(); break;
        case 1: _t->descendName(); break;
        case 2: _t->ascendVal(); break;
        case 3: _t->descendVal(); break;
        case 4: _t->hide_win(); break;
        case 5: _t->show_win(); break;
        case 6: _t->update_win(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData values_window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject values_window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_values_window,
      qt_meta_data_values_window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &values_window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *values_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *values_window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_values_window))
        return static_cast<void*>(const_cast< values_window*>(this));
    return QWidget::qt_metacast(_clname);
}

int values_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
