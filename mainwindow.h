#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "modif_groupe.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void loadEtudiants(const QString& sqlFilter = "");
    void loadGroupes(const QString& encadreurTrilogie = "", const QString& nomGroupeFiltre = "");
    void loadEnseignants();
    void loadThemes();
    void afficherStatEtudiants();
    void afficherStatGroupes();
    void afficherStatEnseignants();
    void afficherStatThemes();
    void afficherActivitesRecentes();
    void chargerFiltreEncadreurs();
    void chargerFiltreClasses();


private slots:

    void applyShadowToCards();
    // Navigation btn avec titre
    void on_btn_dashboard_clicked();
    void on_btn_etudiants_clicked();
    void on_btn_groupes_clicked();
    void on_btn_enseignants_clicked();
    void on_btn_themes_clicked();
    void on_btn_evaluation_clicked();
    void reset_buttons();

    // form avy amn page
    void on_btn_add_etudiants_clicked();
    void on_btn_add_groupes_clicked();
    void on_btn_add_enseignants_clicked();
    void on_btn_add_themes_clicked();

    // form depuis dash
    void on_btn_add_etudiant_clicked();
    void on_btn_add_groupe_clicked();
    void on_btn_add_enseignant_clicked();
    void on_btn_add_theme_clicked();


    void on_filtre_encadreur_currentIndexChanged(int index);
    void on_recherche_groupes_textChanged(const QString &arg1);

    // evaluation
    void on_btn_etudiantsansnote_clicked();
    void loadEvaluationTable(const QString& sqlFilter = "", bool isSimpleMode = false);
    void on_recherche_textChanged(const QString &arg1);
    void on_filtre_groupe_2_currentIndexChanged(int index);


    // etudiant
    void updateGroupesCombo(const QString &classe);
    void filterEtudiants(const QString &selection);
    void on_recherche_etudiants_textChanged(const QString &text);
    void on_recherche_enseignants_textChanged(const QString &text);


    void on_btn_supprimer_etudiants_clicked();
    void on_btn_supprimer_enseignants_clicked();
    void on_btn_supprimer_themes_clicked();

    void on_btn_modifier_etudiants_clicked();
    void on_btn_modifier_enseignants_clicked();
    void on_btn_modifier_themes_clicked();

    //theme
    void on_recherche_themes_textChanged(const QString &text);
    void on_filtre_parcours_currentIndexChanged(int index);
    void chargerThemesAvecFiltres(const QString &recherche, const QString &filtreParcours);
    void initialiserFiltreParcours();

    //groupe
    void on_btn_supprimer_groupes_clicked();
    void on_btn_modifier_groupes_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    void openDatabase();
    void chargerFiltreClassesEtudiant();


};

extern QSqlDatabase db;

#endif // MAINWINDOW_H
