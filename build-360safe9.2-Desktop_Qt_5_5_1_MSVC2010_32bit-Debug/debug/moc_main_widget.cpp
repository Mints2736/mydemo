/****************************************************************************
** Meta object code from reading C++ file 'main_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../360safe9.2/main_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWidget_t {
    QByteArrayData data[21];
    char stringdata0[283];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWidget_t qt_meta_stringdata_MainWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWidget"
QT_MOC_LITERAL(1, 11, 10), // "showWidget"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 18), // "newLocalConnection"
QT_MOC_LITERAL(4, 42, 14), // "showSkinWidget"
QT_MOC_LITERAL(5, 57, 12), // "showMainMenu"
QT_MOC_LITERAL(6, 70, 17), // "showSettingDialog"
QT_MOC_LITERAL(7, 88, 11), // "showAboutUs"
QT_MOC_LITERAL(8, 100, 16), // "showNewCharacter"
QT_MOC_LITERAL(9, 117, 15), // "showLoginDialog"
QT_MOC_LITERAL(10, 133, 18), // "showRegisterDialog"
QT_MOC_LITERAL(11, 152, 10), // "changeSkin"
QT_MOC_LITERAL(12, 163, 9), // "skin_name"
QT_MOC_LITERAL(13, 173, 13), // "iconIsActived"
QT_MOC_LITERAL(14, 187, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(15, 221, 6), // "reason"
QT_MOC_LITERAL(16, 228, 14), // "changeLanguage"
QT_MOC_LITERAL(17, 243, 8), // "LANGUAGE"
QT_MOC_LITERAL(18, 252, 8), // "language"
QT_MOC_LITERAL(19, 261, 8), // "turnPage"
QT_MOC_LITERAL(20, 270, 12) // "current_page"

    },
    "MainWidget\0showWidget\0\0newLocalConnection\0"
    "showSkinWidget\0showMainMenu\0"
    "showSettingDialog\0showAboutUs\0"
    "showNewCharacter\0showLoginDialog\0"
    "showRegisterDialog\0changeSkin\0skin_name\0"
    "iconIsActived\0QSystemTrayIcon::ActivationReason\0"
    "reason\0changeLanguage\0LANGUAGE\0language\0"
    "turnPage\0current_page"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      16,    1,   94,    2, 0x08 /* Private */,
      19,    1,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int,   20,

       0        // eod
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWidget *_t = static_cast<MainWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showWidget(); break;
        case 1: _t->newLocalConnection(); break;
        case 2: _t->showSkinWidget(); break;
        case 3: _t->showMainMenu(); break;
        case 4: _t->showSettingDialog(); break;
        case 5: _t->showAboutUs(); break;
        case 6: _t->showNewCharacter(); break;
        case 7: _t->showLoginDialog(); break;
        case 8: _t->showRegisterDialog(); break;
        case 9: _t->changeSkin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->iconIsActived((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 11: _t->changeLanguage((*reinterpret_cast< LANGUAGE(*)>(_a[1]))); break;
        case 12: _t->turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWidget::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_MainWidget.data,
      qt_meta_data_MainWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget.stringdata0))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE