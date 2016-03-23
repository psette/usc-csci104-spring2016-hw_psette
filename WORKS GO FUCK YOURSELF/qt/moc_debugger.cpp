/****************************************************************************
** Meta object code from reading C++ file 'debugger.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "debugger.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'debugger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Debugger[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      17,    9,    9,    9, 0x0a,
      28,    9,    9,    9, 0x0a,
      44,    9,    9,    9, 0x0a,
      51,    9,    9,    9, 0x0a,
      61,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Debugger[] = {
    "Debugger\0\0step()\0setBreak()\0continue_func()\0"
    "next()\0inspect()\0quit()\0"
};

void Debugger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Debugger *_t = static_cast<Debugger *>(_o);
        switch (_id) {
        case 0: _t->step(); break;
        case 1: _t->setBreak(); break;
        case 2: _t->continue_func(); break;
        case 3: _t->next(); break;
        case 4: _t->inspect(); break;
        case 5: _t->quit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Debugger::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Debugger::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Debugger,
      qt_meta_data_Debugger, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Debugger::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Debugger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Debugger::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Debugger))
        return static_cast<void*>(const_cast< Debugger*>(this));
    return QWidget::qt_metacast(_clname);
}

int Debugger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
