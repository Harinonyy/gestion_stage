#include "form_etudiant.h"
#include "connexionbd.h"
#include "ui_form_etudiant.h"
#include "mainwindow.h"
#include "modif_etudiant.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QDialogButtonBox>
#include <QRegularExpressionValidator>
#include <QMetaType>

form_etudiant::form_etudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_etudiant)
{
    ui->setupUi(this);

    // connexion
    if (!db.isOpen()) {
        db = connexionBd::connectBase();
    }

    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [=](const QString &text) {
        QString upperText = text.toUpper();
        if (ui->lineEdit_2->text() != upperText)
            ui->lineEdit_2->setText(upperText);
    });

    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [=](const QString &text) {
        QString formatted = text.toLower();
        bool capitalizeNext = true;

        for (int i = 0; i < formatted.length(); ++i) {
            if (capitalizeNext && formatted[i].isLetter()) {
                formatted[i] = formatted[i].toUpper();
                capitalizeNext = false;
            } else if (formatted[i].isSpace()) {
                capitalizeNext = true;
            }
        }

        if (ui->lineEdit_3->text() != formatted)
            ui->lineEdit_3->setText(formatted);
    });


    QRegularExpression rx("^(032|033|034|037|038)\\d{7}$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_5->setValidator(validator);

    connect(ui->lineEdit_5, &QLineEdit::editingFinished, this, [=]() {
        QString tel = ui->lineEdit_5->text();
        if (!tel.isEmpty() && !rx.match(tel).hasMatch()) {
            QMessageBox::warning(this, "Numéro invalide",
                                 "Le numéro doit commencer par 032, 033, 034, 037 ou 038 et contenir 10 chiffres.");
            ui->lineEdit_5->clear();
            ui->lineEdit_5->setFocus();
        }
    });


    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

form_etudiant::~form_etudiant()
{
    delete ui;
}


void form_etudiant::on_buttonBox_accepted()
{
    QString matricule = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString telephone = ui->lineEdit_5->text();
    QString mail = ui->lineEdit_4->text();
    QString codeClasse = ui->comboBox_classe->currentText();

    if (matricule.isEmpty() || nom.isEmpty() || prenom.isEmpty() || codeClasse.isEmpty()) {
        QMessageBox::warning(this, "Etudiant", "Matricule, Nom, Prénom et Classe sont obligatoires !");
        return;
    }
    if (isEditMode) {
        mettreAJourEtudiant(originalMatricule);
    } else {
        QSqlQuery etudiant(db);

        etudiant.prepare("INSERT INTO ETUDIANT (Matricule, Nom_etudiant, Prenom_etudiant, Telephone_etudiant, Mail_etudiant, CLASSE_num_classe, GROUPE_nom_groupe) "
                         "VALUES (:matricule, :nom, :prenom, :telephone, :mail, :classe, NULL)");

        etudiant.bindValue(":matricule", matricule);
        etudiant.bindValue(":nom", nom);
        etudiant.bindValue(":prenom", prenom);
        etudiant.bindValue(":telephone", telephone);

        if (mail.isEmpty()) {
            etudiant.bindValue(":mail", QVariant(QMetaType::fromType<QString>()));
        } else {
            etudiant.bindValue(":mail", mail);
        }
        etudiant.bindValue(":classe", codeClasse);

        if (!etudiant.exec()) {
            QMessageBox::warning(this, "Erreur", "Erreur lors de l'inscription de l'étudiant : " + etudiant.lastError().text());
        } else {
            QMessageBox::information(this, "Succès", "L'étudiant a été enregistré avec succès !");
            if (auto *mw = qobject_cast<MainWindow*>(parentWidget())) {
                mw->loadEtudiants();
            }
            close();
        }
    }
}

void form_etudiant::remplirFormulaire(const QString &matricule, const QString &nom, const QString &prenom,
                                      const QString &telephone, const QString &mail, const QString &classe, QString groupe)
{
    ui->lineEdit->setText(matricule);
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_3->setText(prenom);
    ui->lineEdit_4->setText(mail);
    ui->lineEdit_5->setText(telephone);
    ui->comboBox_classe->setCurrentText(classe);


    originalMatricule = matricule;
    isEditMode = true;
}

void form_etudiant::mettreAJourEtudiant(const QString &ancienMatricule)
{
    QString nouveauMatricule = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString mail = ui->lineEdit_4->text();
    QString telephone = ui->lineEdit_5->text();
    QString codeClasse = ui->comboBox_classe->currentText();

    QSqlQuery query(db);

    query.prepare("UPDATE ETUDIANT SET "
                  "Matricule = :matricule, Nom_etudiant = :nom, Prenom_etudiant = :prenom, "
                  "Telephone_etudiant = :telephone, Mail_etudiant = :mail, "
                  "CLASSE_num_classe = :classe "
                  "WHERE Matricule = :ancienMatricule");
    query.bindValue(":matricule", nouveauMatricule);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);

    if (mail.isEmpty()) {
        query.bindValue(":mail", QVariant(QMetaType::fromType<QString>()));
    } else {
        query.bindValue(":mail", mail);
    }
    query.bindValue(":classe", codeClasse);
    query.bindValue(":ancienMatricule", ancienMatricule);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la mise à jour : " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "L'étudiant a été modifié avec succès !");
        if (auto *mw = qobject_cast<MainWindow*>(parentWidget())) {
            mw->loadEtudiants();
        }
        accept();
    }
}


void form_etudiant::on_buttonBox_rejected()
{
    close();
}
