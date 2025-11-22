#include "modif_enseignant.h"
#include "ui_modif_enseignant.h"
#include "connexionbd.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

extern QSqlDatabase db;

modif_enseignant::modif_enseignant(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::modif_enseignant)
{
    ui->setupUi(this);


    if (!db.isOpen()) {
        db = connexionBd::connectBase();
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &modif_enseignant::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &modif_enseignant::reject);
}

modif_enseignant::~modif_enseignant()
{
    delete ui;
}

void modif_enseignant::remplirFormulaire(const QString &trilogie, const QString &nom,
                                         const QString &prenom, const QString &telephone,
                                         const QString &email)
{
    ui->lineEdit->setText(trilogie);
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_3->setText(prenom);
    ui->lineEdit_4->setText(email);
    ui->lineEdit_5->setText(telephone);

    originalTrilogie = trilogie;
}

void modif_enseignant::on_buttonBox_accepted()
{
    QString trilogie = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString telephone = ui->lineEdit_5->text();
    QString email = ui->lineEdit_4->text();


    if (trilogie.isEmpty() || nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Trilogie, Nom et Prénom sont obligatoires !");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE ENSEIGNANT SET "
                  "Trilogie_ens = :trilogie, "
                  "Nom_enseignant = :nom, "
                  "Prenom_enseignant = :prenom, "
                  "Telephone_enseignant = :telephone, "
                  "Mail_enseignant = :email "
                  "WHERE Trilogie_ens = :ancienneTrilogie");

    query.bindValue(":trilogie", trilogie);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);


    if (telephone.isEmpty()) {
        query.bindValue(":telephone", QVariant(QMetaType::fromType<QString>()));
    } else {
        query.bindValue(":telephone", telephone);
    }

    if (email.isEmpty()) {
        query.bindValue(":email", QVariant(QMetaType::fromType<QString>()));
    } else {
        query.bindValue(":email", email);
    }

    query.bindValue(":ancienneTrilogie", originalTrilogie);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la mise à jour : " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "L'enseignant a été modifié avec succès !");
        accept();
    }
}
