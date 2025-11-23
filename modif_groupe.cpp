#include "modif_groupe.h"
#include "ui_modif_groupe.h"
#include "connexionbd.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpressionValidator>
#include <QPushButton>

extern QSqlDatabase db;

modif_groupe::modif_groupe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modif_groupe)
{
    ui->setupUi(this);

    if (!db.open()){
        db = connexionBd::connectBase();
    }


    QRegularExpressionValidator *noteValidator = new QRegularExpressionValidator(QRegularExpression("^\\d{0,2}(\\.\\d{0,2})?$"), this);
    ui->lineEdit_19->setValidator(noteValidator);
    ui->lineEdit_20->setValidator(noteValidator);

    QRegularExpressionValidator *matriculeValidator = new QRegularExpressionValidator(QRegularExpression("\\d*"), this);
    ui->lineEdit_14->setValidator(matriculeValidator);
    ui->lineEdit_15->setValidator(matriculeValidator);
    ui->lineEdit_16->setValidator(matriculeValidator);
    ui->lineEdit_17->setValidator(matriculeValidator);
    ui->lineEdit_18->setValidator(matriculeValidator);


    QSqlQuery query;

    // classes
    ui->comboBox_7->clear();
    ui->comboBox_7->addItem("Sélectionner Classe", "");
    if (query.exec("SELECT num_classe FROM CLASSE ORDER BY num_classe")) {
        while (query.next()) {
            ui->comboBox_7->addItem(query.value(0).toString(), query.value(0));
        }
    }

    // encadreur
    ui->comboBox_8->clear();
    ui->comboBox_8->addItem("Choisir un Encadreur", "");
    if (query.exec("SELECT Trilogie_ens, CONCAT(Nom_enseignant, ' ', Prenom_enseignant) FROM ENSEIGNANT ORDER BY Nom_enseignant")) {
        while (query.next()) {
            ui->comboBox_8->addItem(query.value(1).toString(), query.value(0));
        }
    }

    // parcours cible
    ui->comboBox_10->clear();
    ui->comboBox_10->addItem("Tous les parcours", "");
    ui->comboBox_10->addItem("Thèmes génériques", "generique");
    if (query.exec("SELECT code_parcours FROM PARCOURS ORDER BY code_parcours")) {
        while (query.next()) {
            ui->comboBox_10->addItem(query.value(0).toString(), query.value(0));
        }
    }

    // theme
    ui->comboBox_9->clear();
    ui->comboBox_9->addItem("Sélectionner Thème", "");

    // theme encadreur
    connect(ui->comboBox_8, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &modif_groupe::onEncadreurChanged);


    connect(ui->comboBox_10, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &modif_groupe::onParcoursChanged);

    connect(ui->buttonBox_3, &QDialogButtonBox::accepted, this, &modif_groupe::on_buttonBox_accepted);
    connect(ui->buttonBox_3, &QDialogButtonBox::rejected, this, &modif_groupe::reject);
}

modif_groupe::~modif_groupe()
{
    delete ui;
}

void modif_groupe::onEncadreurChanged(int index)
{
    QString trilogieEncadreur = ui->comboBox_8->currentData().toString();
    chargerThemesParEncadreur(trilogieEncadreur);
}


void modif_groupe::onParcoursChanged(int index)
{
    QString trilogieEncadreur = ui->comboBox_8->currentData().toString();
    if (!trilogieEncadreur.isEmpty()) {
        chargerThemesParEncadreur(trilogieEncadreur);
    }
}


void modif_groupe::chargerThemesParEncadreur(const QString& trilogieEncadreur)
{
    ui->comboBox_9->clear();
    ui->comboBox_9->addItem("Sélectionner Thème", "");

    if (trilogieEncadreur.isEmpty()) {
        return;
    }

    QString parcoursFiltre = ui->comboBox_10->currentData().toString();
    QSqlQuery query;


    if (parcoursFiltre == "generique") {
        query.prepare("SELECT num_theme, libelle FROM THEME WHERE ENSEIGNANT_Trilogie_ens = :trilogie AND PARCOURS_code_parcours IS NULL ORDER BY libelle");
    } else if (!parcoursFiltre.isEmpty()) {
        query.prepare("SELECT num_theme, libelle FROM THEME WHERE ENSEIGNANT_Trilogie_ens = :trilogie AND PARCOURS_code_parcours = :parcours ORDER BY libelle");
        query.bindValue(":parcours", parcoursFiltre);
    } else {
        query.prepare("SELECT num_theme, libelle FROM THEME WHERE ENSEIGNANT_Trilogie_ens = :trilogie ORDER BY libelle");
    }

    query.bindValue(":trilogie", trilogieEncadreur);

    if (query.exec()) {
        while (query.next()) {
            ui->comboBox_9->addItem(query.value(1).toString(), query.value(0));
        }
    } else {
        qDebug() << "Erreur chargement thèmes encadreur:" << query.lastError().text();
    }
}

void modif_groupe::remplirFormulaire(const QString& nomGroupe, const QString& classe,
                                     const QString& encadreur, const QString& theme,
                                     const QStringList& matriculesEtudiants,
                                     const QString& noteRapport, const QString& noteApplication)
{
    originalNomGroupe = nomGroupe;
    originalClasse = classe;

    ui->lineEdit_13->setText(nomGroupe);


    if (noteRapport.toDouble() > 0) ui->lineEdit_19->setText(noteRapport);
    else ui->lineEdit_19->clear();

    if (noteApplication.toDouble() > 0) ui->lineEdit_20->setText(noteApplication);
    else ui->lineEdit_20->clear();

    for (int i = 0; i < ui->comboBox_7->count(); ++i) {
        if (ui->comboBox_7->itemData(i).toString() == classe) {
            ui->comboBox_7->setCurrentIndex(i);
            break;
        }
    }

    for (int i = 0; i < ui->comboBox_8->count(); ++i) {
        if (ui->comboBox_8->itemData(i).toString() == encadreur) {
            ui->comboBox_8->setCurrentIndex(i);
            break;
        }
    }
    chargerThemesParEncadreur(encadreur);

    for (int i = 0; i < ui->comboBox_9->count(); ++i) {
        if (ui->comboBox_9->itemData(i).toString() == theme) {
            ui->comboBox_9->setCurrentIndex(i);
            break;
        }
    }

    for (int i = 0; i < matriculesEtudiants.size() && i < 5; ++i) {
        switch(i) {
        case 0: ui->lineEdit_14->setText(matriculesEtudiants[i]); break;
        case 1: ui->lineEdit_15->setText(matriculesEtudiants[i]); break;
        case 2: ui->lineEdit_16->setText(matriculesEtudiants[i]); break;
        case 3: ui->lineEdit_17->setText(matriculesEtudiants[i]); break;
        case 4: ui->lineEdit_18->setText(matriculesEtudiants[i]); break;
        }
    }
}

void modif_groupe::on_comboBox_7_currentIndexChanged(int index)
{

}

void modif_groupe::on_comboBox_9_currentIndexChanged(int index)
{

}

void modif_groupe::on_buttonBox_accepted()
{
    qDebug() << "Bouton OK cliqué !";

    QString nomGroupe = ui->lineEdit_13->text();
    QString nouvelleClasse = ui->comboBox_7->currentData().toString();
    QString encadreur = ui->comboBox_8->currentData().toString();
    QString theme = ui->comboBox_9->currentData().toString();
    QString noteRapport = ui->lineEdit_19->text();
    QString noteApplication = ui->lineEdit_20->text();

    qDebug() << "Données récupérées:" << nomGroupe << nouvelleClasse << encadreur << theme << noteRapport << noteApplication;


    QStringList nouveauxMatricules;
    if (!ui->lineEdit_14->text().isEmpty()) nouveauxMatricules << ui->lineEdit_14->text();
    if (!ui->lineEdit_15->text().isEmpty()) nouveauxMatricules << ui->lineEdit_15->text();
    if (!ui->lineEdit_16->text().isEmpty()) nouveauxMatricules << ui->lineEdit_16->text();
    if (!ui->lineEdit_17->text().isEmpty()) nouveauxMatricules << ui->lineEdit_17->text();
    if (!ui->lineEdit_18->text().isEmpty()) nouveauxMatricules << ui->lineEdit_18->text();

    qDebug() << "Matricules:" << nouveauxMatricules;


    if (nomGroupe.isEmpty() || nouvelleClasse.isEmpty() || encadreur.isEmpty() || theme.isEmpty()) {
        QMessageBox::warning(this, "Champs obligatoires", "Nom, classe, encadreur et thème sont obligatoires !");
        return;
    }

    if (nouveauxMatricules.size() < 4 || nouveauxMatricules.size() > 5) {
        QMessageBox::warning(this, "Nombre d'étudiants", "Un groupe doit avoir 4 ou 5 étudiants !");
        return;
    }


    for (const QString &matricule : nouveauxMatricules) {
        QSqlQuery verif;
        verif.prepare("SELECT COUNT(*) FROM ETUDIANT WHERE Matricule = :matricule");
        verif.bindValue(":matricule", matricule);

        if (verif.exec() && verif.next()) {
            if (verif.value(0).toInt() == 0) {
                QMessageBox::warning(this, "Matricule invalide", "L'étudiant " + matricule + " n'existe pas !");
                return;
            }
        }
    }

    QSqlDatabase::database().transaction();

    try {

        QSqlQuery desaffecter;
        desaffecter.prepare("UPDATE ETUDIANT SET GROUPE_num_groupe = NULL, CLASSE_num_classe = NULL WHERE GROUPE_num_groupe = :groupe AND CLASSE_num_classe = :classe");
        desaffecter.bindValue(":groupe", originalNomGroupe);
        desaffecter.bindValue(":classe", originalClasse);
        if (!desaffecter.exec()) {
            throw std::runtime_error("Erreur désaffectation anciens étudiants: " + desaffecter.lastError().text().toStdString());
        }


        QSqlQuery updateGroupe;
        updateGroupe.prepare("UPDATE GROUPE SET num_groupe = :nouveau_nom, CLASSE_num_classe = :nouvelle_classe, "
                             "ENSEIGNANT_Trilogie_ens = :encadreur, THEME_num_theme = :theme, "
                             "note_rapport = :note_rapport, note_application = :note_app "
                             "WHERE num_groupe = :ancien_nom AND CLASSE_num_classe = :ancienne_classe");
        updateGroupe.bindValue(":nouveau_nom", nomGroupe);
        updateGroupe.bindValue(":nouvelle_classe", nouvelleClasse);
        updateGroupe.bindValue(":encadreur", encadreur);
        updateGroupe.bindValue(":theme", theme);
        updateGroupe.bindValue(":note_rapport", noteRapport.isEmpty() ? QVariant() : noteRapport.toDouble());
        updateGroupe.bindValue(":note_app", noteApplication.isEmpty() ? QVariant() : noteApplication.toDouble());
        updateGroupe.bindValue(":ancien_nom", originalNomGroupe);
        updateGroupe.bindValue(":ancienne_classe", originalClasse);

        if (!updateGroupe.exec()) {
            throw std::runtime_error("Erreur mise à jour groupe: " + updateGroupe.lastError().text().toStdString());
        }

        for (const QString &matricule : nouveauxMatricules) {
            QSqlQuery affecter;
            affecter.prepare("UPDATE ETUDIANT SET GROUPE_num_groupe = :groupe, CLASSE_num_classe = :classe WHERE Matricule = :matricule");
            affecter.bindValue(":groupe", nomGroupe);
            affecter.bindValue(":classe", nouvelleClasse);
            affecter.bindValue(":matricule", matricule);

            if (!affecter.exec()) {
                throw std::runtime_error("Erreur affectation étudiant " + matricule.toStdString() + ": " + affecter.lastError().text().toStdString());
            }
        }

        QSqlDatabase::database().commit();
        QMessageBox::information(this, "Succès", "Groupe modifié avec succès !");


        MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
        if (mw) {
            mw->loadGroupes();
            mw->loadEtudiants();
        }

        accept();

    } catch (const std::exception& e) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Erreur", "La modification a échoué :\n" + QString::fromStdString(e.what()));
    }
}
