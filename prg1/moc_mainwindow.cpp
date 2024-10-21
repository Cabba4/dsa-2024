/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hh'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.hh"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomGraphicsView_t {
    const uint offsetsAndSize[14];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CustomGraphicsView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CustomGraphicsView_t qt_meta_stringdata_CustomGraphicsView = {
    {
QT_MOC_LITERAL(0, 18), // "CustomGraphicsView"
QT_MOC_LITERAL(19, 10), // "mouseMoved"
QT_MOC_LITERAL(30, 0), // ""
QT_MOC_LITERAL(31, 12), // "QMouseEvent*"
QT_MOC_LITERAL(44, 5), // "event"
QT_MOC_LITERAL(50, 9), // "mouseLeft"
QT_MOC_LITERAL(60, 12) // "mouseClicked"

    },
    "CustomGraphicsView\0mouseMoved\0\0"
    "QMouseEvent*\0event\0mouseLeft\0mouseClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomGraphicsView[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    0 /* Public */,
       5,    0,   35,    2, 0x06,    2 /* Public */,
       6,    1,   36,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void CustomGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomGraphicsView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mouseMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseLeft(); break;
        case 2: _t->mouseClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CustomGraphicsView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::mouseMoved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::mouseLeft)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::mouseClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CustomGraphicsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_CustomGraphicsView.offsetsAndSize,
    qt_meta_data_CustomGraphicsView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CustomGraphicsView_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>



>,
    nullptr
} };


const QMetaObject *CustomGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int CustomGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CustomGraphicsView::mouseMoved(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CustomGraphicsView::mouseLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CustomGraphicsView::mouseClicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[36];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 12), // "execute_line"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 12), // "cmd_selected"
QT_MOC_LITERAL(38, 3), // "idx"
QT_MOC_LITERAL(42, 15), // "number_selected"
QT_MOC_LITERAL(58, 6), // "number"
QT_MOC_LITERAL(65, 11), // "select_file"
QT_MOC_LITERAL(77, 16), // "clear_input_line"
QT_MOC_LITERAL(94, 8), // "fit_view"
QT_MOC_LITERAL(103, 22), // "scene_selection_change"
QT_MOC_LITERAL(126, 15), // "clear_selection"
QT_MOC_LITERAL(142, 12), // "onMouseMoved"
QT_MOC_LITERAL(155, 12), // "QMouseEvent*"
QT_MOC_LITERAL(168, 5), // "event"
QT_MOC_LITERAL(174, 20), // "updateCoordinateText"
QT_MOC_LITERAL(195, 11), // "onMouseLeft"
QT_MOC_LITERAL(207, 14) // "onMouseClicked"

    },
    "MainWindow\0execute_line\0\0cmd_selected\0"
    "idx\0number_selected\0number\0select_file\0"
    "clear_input_line\0fit_view\0"
    "scene_selection_change\0clear_selection\0"
    "onMouseMoved\0QMouseEvent*\0event\0"
    "updateCoordinateText\0onMouseLeft\0"
    "onMouseClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x0a,    0 /* Public */,
       3,    1,   87,    2, 0x0a,    1 /* Public */,
       5,    1,   90,    2, 0x0a,    3 /* Public */,
       7,    0,   93,    2, 0x0a,    5 /* Public */,
       8,    0,   94,    2, 0x0a,    6 /* Public */,
       9,    0,   95,    2, 0x0a,    7 /* Public */,
      10,    0,   96,    2, 0x0a,    8 /* Public */,
      11,    0,   97,    2, 0x0a,    9 /* Public */,
      12,    1,   98,    2, 0x0a,   10 /* Public */,
      15,    0,  101,    2, 0x0a,   12 /* Public */,
      16,    0,  102,    2, 0x0a,   13 /* Public */,
      17,    1,  103,    2, 0x0a,   14 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->execute_line(); break;
        case 1: _t->cmd_selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->number_selected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->select_file(); break;
        case 4: _t->clear_input_line(); break;
        case 5: _t->fit_view(); break;
        case 6: _t->scene_selection_change(); break;
        case 7: _t->clear_selection(); break;
        case 8: _t->onMouseMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->updateCoordinateText(); break;
        case 10: _t->onMouseLeft(); break;
        case 11: _t->onMouseClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
