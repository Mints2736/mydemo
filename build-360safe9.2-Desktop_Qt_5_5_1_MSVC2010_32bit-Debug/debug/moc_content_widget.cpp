/****************************************************************************
** Meta object code from reading C++ file 'content_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../360safe9.2/content_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'content_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ContentWidget_t {
    QByteArrayData data[4];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ContentWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ContentWidget_t qt_meta_stringdata_ContentWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ContentWidget"
QT_MOC_LITERAL(1, 14, 15), // "showLoginDialog"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18) // "showRegisterDialog"

    },
    "ContentWidget\0showLoginDialog\0\0"
    "showRegisterDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ContentWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ContentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ContentWidget *_t = static_cast<ContentWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showLoginDialog(); break;
        case 1: _t->showRegisterDialog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ContentWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ContentWidget::showLoginDialog)) {
                *result = 0;
            }
        }
        {
            typedef void (ContentWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ContentWidget::showRegisterDialog)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ContentWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ContentWidget.data,
      qt_meta_data_ContentWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ContentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ContentWidget.stringdata0))
        return static_cast<void*>(const_cast< ContentWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ContentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ContentWidget::showLoginDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ContentWidget::showRegisterDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
