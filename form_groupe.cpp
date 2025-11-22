#include "form_groupe.h"
#include "ui_form_groupe.h"
#include "connexionbd.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QVariant>
#include <QRegularExpressionValidator>

extern QSqlDatabase db;

form_groupe::form_groupe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_groupe)
{
    ui->setupUi(this);

    if (!db.open()){
        db = connexionBd::connectBase();
    }

    chargerClasses();
    chargerParcours();
    chargerEncadreurs();
    chargerThemes();

    ui->lineEdit->setEnabled(false);

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("\\d*"), this);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);
    ui->lineEdit_5->setValidator(validator);
    ui->lineEdit_6->setValidator(validator);

    this->setStyleSheet("QComboBox QAbstractItemView { color: #000000; background-color: #FFFFFF; }");
}

form_groupe::~form_groupe()
{
    delete ui;
}

// affiche classe
void form_groupe::chargerClasses()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(" Sélectionner Classe ", QVariant(""));
    QSqlQuery query;
    if (query.exec("SELECT num_classe, num_classe FROM CLASSE ORDER BY num_classe")) {
        while (query.next()) {
            ui->comboBox->addItem(query.value(1).toString(), query.value(0));
        }
    } else {
        qDebug() << "Erreur chargerClasses:" << query.lastError().text();
    }
}

// affiche parcours
void form_groupe::chargerParcours()
{
    ui->comboBox_3->clear();
    ui->comboBox_3->addItem(" Tous les parcours ", QVariant(""));
    ui->comboBox_3->addItem(" Thèmes génériques ", QVariant("generique"));

    QSqlQuery query;
    if (query.exec("SELECT code_parcours, nom_parcours FROM PARCOURS ORDER BY nom_parcours")) {
        while (query.next()) {
            QString code = query.value(0).toString().trimmed();
            QString nom = query.value(1).toString().trimmed();
            QString affichage = nom.isEmpty() ? code : nom + " (" + code + ")";
            ui->comboBox_3->addItem(affichage, code);
        }
    } else {
        qDebug() << "Erreur chargerParcours:" << query.lastError().text();
    }
}

// affichage theme
void form_groupe::chargerThemes(const QString& codeParcours)
{
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem(" Sélectionner Thème ", QVariant(""));

    QSqlQuery query;

    if (codeParcours == "generique") {
        // Affichage theme generique only
        query.prepare("SELECT num_theme, libelle FROM THEME WHERE PARCOURS_code_parcours IS NULL ORDER BY libelle");
    } else if (!codeParcours.isEmpty()) {
        // Affichage parcours specifique
        query.prepare("SELECT num_theme, libelle FROM THEME WHERE PARCOURS_code_parcours = :codeParcours ORDER BY libelle");
        query.bindValue(":codeParcours", codeParcours);
    } else {
        // Affichage tous
        query.prepare("SELECT num_theme, libelle FROM THEME ORDER BY libelle");
    }

    if (query.exec()) {
        while (query.next()) {
            ui->comboBox_4->addItem(query.value(1).toString(), query.value(0));
        }
    } else {
        qDebug() << "Erreur chargerThemes (filtre):" << query.lastError().text();
    }
}

// affichage encadreur
void form_groupe::chargerEncadreurs()
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(" Choisir un Encadreur ", QVariant(""));
    QSqlQuery query;
    if (query.exec("SELECT Trilogie_ens, Nom_enseignant, Prenom_enseignant FROM ENSEIGNANT ORDER BY Nom_enseignant")) {
        while (query.next()) {
            QString nomComplet = query.value(1).toString() + " " + query.value(2).toString();
            ui->comboBox_2->addItem(nomComplet, query.value(0));
        }
    } else {
        qDebug() << "Erreur chargerEncadreurs:" << query.lastError().text();
    }
}

// calcul incre Gn+1
QString form_groupe::calculerNomGroupeSuivant(const QString& numClasse)
{
    if (numClasse.isEmpty()) return "";

    QSqlQuery query;
    int maxNumero = 0;
    QString sql = QString(
        "SELECT MAX(CAST(SUBSTR(nom_groupe, 2) AS UNSIGNED)) "
        "FROM GROUPE "
        "WHERE CLASSE_num_classe = :numClasse"
        );
    query.prepare(sql);
    query.bindValue(":numClasse", numClasse);

    if (query.exec() && query.next()) {
        if (query.value(0).isValid()) {
            maxNumero = query.value(0).toInt();
        }
    } else {
        qDebug() << "Erreur calcul nom groupe:" << query.lastError().text();
    }
    return "G" + QString::number(maxNumero + 1);
}

// slots

void form_groupe::on_comboBox_currentIndexChanged(int index)
{
    QString numClasse = ui->comboBox->currentData().toString();
    QString nouveauNom = calculerNomGroupeSuivant(numClasse);
    ui->lineEdit->setText(nouveauNom);
}

void form_groupe::on_comboBox_3_currentIndexChanged(int index)
{
    QString codeParcours = ui->comboBox_3->currentData().toString();

    if (codeParcours.isEmpty()) {
        chargerThemes("");
    } else {
        chargerThemes(codeParcours);
    }
}

void form_groupe::on_buttonBox_accepted()
{
    QString nomGroupe = ui->lineEdit->text();
    QString numClasse = ui->comboBox->currentData().toString();
    QString encadreur = ui->comboBox_2->currentData().toString();
    QString theme = ui->comboBox_4->currentData().toString();

    // recup des matricule
    QStringList matricules;
    if (!ui->lineEdit_2->text().isEmpty()) matricules << ui->lineEdit_2->text();
    if (!ui->lineEdit_3->text().isEmpty()) matricules << ui->lineEdit_3->text();
    if (!ui->lineEdit_4->text().isEmpty()) matricules << ui->lineEdit_4->text();
    if (!ui->lineEdit_5->text().isEmpty()) matricules << ui->lineEdit_5->text();
    if (!ui->lineEdit_6->text().isEmpty()) matricules << ui->lineEdit_6->text();

    // validation
    if (numClasse.isEmpty() || encadreur.isEmpty() || theme.isEmpty()) {
        QMessageBox::warning(this, "Champs obligatoires", "Classe, encadreur et thème sont obligatoires !");
        return;
    }

    if (matricules.size() < 4 || matricules.size() > 5) {
        QMessageBox::warning(this, "Nombre d'étudiants", "Un groupe doit avoir 4 ou 5 étudiants !");
        return;
    }

    // verification raha mbola tsy misy
    for (const QString &matricule : matricules) {
        QSqlQuery verif;
        verif.prepare("SELECT COUNT(*), GROUPE_nom_groupe FROM ETUDIANT WHERE Matricule = :matricule GROUP BY Matricule");
        verif.bindValue(":matricule", matricule);

        if (verif.exec() && verif.next()) {
            if (verif.value(0).toInt() == 0) {
                QMessageBox::warning(this, "Matricule invalide",
                                     "L'étudiant avec le matricule " + matricule + " n'existe pas !");
                return;
            }

            // verifier rahae fa manana groupe le etudiant
            if (!verif.value(1).isNull() && !verif.value(1).toString().isEmpty()) {
                QMessageBox::warning(this, "Étudiant déjà dans un groupe",
                                     "L'étudiant " + matricule + " est déjà dans le groupe " + verif.value(1).toString() + " !");
                return;
            }
        }
    }

    // Insertion groupe
    QSqlQuery query;
    query.prepare("INSERT INTO GROUPE (nom_groupe, CLASSE_num_classe, ENSEIGNANT_Trilogie_ens, THEME_num_theme) "
                  "VALUES (:nom, :classe, :encadreur, :theme)");
    query.bindValue(":nom", nomGroupe);
    query.bindValue(":classe", numClasse);
    query.bindValue(":encadreur", encadreur);
    query.bindValue(":theme", theme);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur création groupe: " + query.lastError().text());
        return;
    }

    // MAJ etudiant avec groupe
    for (const QString &matricule : matricules) {
        QSqlQuery updateEtudiant;
        updateEtudiant.prepare("UPDATE ETUDIANT SET GROUPE_nom_groupe = :groupe, CLASSE_num_classe = :classe "
                               "WHERE Matricule = :matricule");
        updateEtudiant.bindValue(":groupe", nomGroupe);
        updateEtudiant.bindValue(":classe", numClasse);
        updateEtudiant.bindValue(":matricule", matricule);

        if (!updateEtudiant.exec()) {
            QMessageBox::warning(this, "Avertissement",
                                 "Erreur affectation étudiant " + matricule + ": " + updateEtudiant.lastError().text());
        }
    }

    QMessageBox::information(this, "Succès", "Groupe créé avec succès !");

    // Recharger les donnees dans MainWindow
    MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
    if (mw) {
        mw->loadGroupes();
        mw->loadEtudiants();
    }

    accept();
}
void form_groupe::on_buttonBox_rejected()
{
    reject();
}
