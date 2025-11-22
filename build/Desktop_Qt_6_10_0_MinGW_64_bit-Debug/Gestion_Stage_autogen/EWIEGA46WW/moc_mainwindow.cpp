/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "applyShadowToCards",
        "",
        "on_btn_dashboard_clicked",
        "on_btn_etudiants_clicked",
        "on_btn_groupes_clicked",
        "on_btn_enseignants_clicked",
        "on_btn_themes_clicked",
        "on_btn_evaluation_clicked",
        "reset_buttons",
        "on_btn_add_etudiants_clicked",
        "on_btn_add_groupes_clicked",
        "on_btn_add_enseignants_clicked",
        "on_btn_add_themes_clicked",
        "on_btn_add_etudiant_clicked",
        "on_btn_add_groupe_clicked",
        "on_btn_add_enseignant_clicked",
        "on_btn_add_theme_clicked",
        "on_filtre_encadreur_currentIndexChanged",
        "index",
        "on_recherche_groupes_textChanged",
        "arg1",
        "on_btn_etudiantsansnote_clicked",
        "loadEvaluationTable",
        "sqlFilter",
        "isSimpleMode",
        "on_recherche_textChanged",
        "on_filtre_groupe_2_currentIndexChanged",
        "updateGroupesCombo",
        "classe",
        "filterEtudiants",
        "selection",
        "on_recherche_etudiants_textChanged",
        "text",
        "on_recherche_enseignants_textChanged",
        "on_btn_supprimer_etudiants_clicked",
        "on_btn_supprimer_enseignants_clicked",
        "on_btn_supprimer_themes_clicked",
        "on_btn_modifier_etudiants_clicked",
        "on_btn_modifier_enseignants_clicked",
        "on_btn_modifier_themes_clicked",
        "on_recherche_themes_textChanged",
        "on_filtre_parcours_currentIndexChanged",
        "chargerThemesAvecFiltres",
        "recherche",
        "filtreParcours",
        "initialiserFiltreParcours",
        "on_btn_supprimer_groupes_clicked",
        "on_btn_modifier_groupes_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'applyShadowToCards'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_dashboard_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_etudiants_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_groupes_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_enseignants_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_themes_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_evaluation_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'reset_buttons'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_etudiants_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_groupes_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_enseignants_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_themes_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_etudiant_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_groupe_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_enseignant_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_add_theme_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_filtre_encadreur_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 19 },
        }}),
        // Slot 'on_recherche_groupes_textChanged'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 21 },
        }}),
        // Slot 'on_btn_etudiantsansnote_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadEvaluationTable'
        QtMocHelpers::SlotData<void(const QString &, bool)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::Bool, 25 },
        }}),
        // Slot 'loadEvaluationTable'
        QtMocHelpers::SlotData<void(const QString &)>(23, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'loadEvaluationTable'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void),
        // Slot 'on_recherche_textChanged'
        QtMocHelpers::SlotData<void(const QString &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 21 },
        }}),
        // Slot 'on_filtre_groupe_2_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 19 },
        }}),
        // Slot 'updateGroupesCombo'
        QtMocHelpers::SlotData<void(const QString &)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 29 },
        }}),
        // Slot 'filterEtudiants'
        QtMocHelpers::SlotData<void(const QString &)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 31 },
        }}),
        // Slot 'on_recherche_etudiants_textChanged'
        QtMocHelpers::SlotData<void(const QString &)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 33 },
        }}),
        // Slot 'on_recherche_enseignants_textChanged'
        QtMocHelpers::SlotData<void(const QString &)>(34, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 33 },
        }}),
        // Slot 'on_btn_supprimer_etudiants_clicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_supprimer_enseignants_clicked'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_supprimer_themes_clicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_modifier_etudiants_clicked'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_modifier_enseignants_clicked'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_modifier_themes_clicked'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_recherche_themes_textChanged'
        QtMocHelpers::SlotData<void(const QString &)>(41, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 33 },
        }}),
        // Slot 'on_filtre_parcours_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(42, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 19 },
        }}),
        // Slot 'chargerThemesAvecFiltres'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(43, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 44 }, { QMetaType::QString, 45 },
        }}),
        // Slot 'initialiserFiltreParcours'
        QtMocHelpers::SlotData<void()>(46, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_supprimer_groupes_clicked'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_modifier_groupes_clicked'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->applyShadowToCards(); break;
        case 1: _t->on_btn_dashboard_clicked(); break;
        case 2: _t->on_btn_etudiants_clicked(); break;
        case 3: _t->on_btn_groupes_clicked(); break;
        case 4: _t->on_btn_enseignants_clicked(); break;
        case 5: _t->on_btn_themes_clicked(); break;
        case 6: _t->on_btn_evaluation_clicked(); break;
        case 7: _t->reset_buttons(); break;
        case 8: _t->on_btn_add_etudiants_clicked(); break;
        case 9: _t->on_btn_add_groupes_clicked(); break;
        case 10: _t->on_btn_add_enseignants_clicked(); break;
        case 11: _t->on_btn_add_themes_clicked(); break;
        case 12: _t->on_btn_add_etudiant_clicked(); break;
        case 13: _t->on_btn_add_groupe_clicked(); break;
        case 14: _t->on_btn_add_enseignant_clicked(); break;
        case 15: _t->on_btn_add_theme_clicked(); break;
        case 16: _t->on_filtre_encadreur_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->on_recherche_groupes_textChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->on_btn_etudiantsansnote_clicked(); break;
        case 19: _t->loadEvaluationTable((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 20: _t->loadEvaluationTable((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->loadEvaluationTable(); break;
        case 22: _t->on_recherche_textChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->on_filtre_groupe_2_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->updateGroupesCombo((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->filterEtudiants((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->on_recherche_etudiants_textChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->on_recherche_enseignants_textChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 28: _t->on_btn_supprimer_etudiants_clicked(); break;
        case 29: _t->on_btn_supprimer_enseignants_clicked(); break;
        case 30: _t->on_btn_supprimer_themes_clicked(); break;
        case 31: _t->on_btn_modifier_etudiants_clicked(); break;
        case 32: _t->on_btn_modifier_enseignants_clicked(); break;
        case 33: _t->on_btn_modifier_themes_clicked(); break;
        case 34: _t->on_recherche_themes_textChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 35: _t->on_filtre_parcours_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 36: _t->chargerThemesAvecFiltres((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 37: _t->initialiserFiltreParcours(); break;
        case 38: _t->on_btn_supprimer_groupes_clicked(); break;
        case 39: _t->on_btn_modifier_groupes_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 40;
    }
    return _id;
}
QT_WARNING_POP
