#include "modif_etudiant.h"
#include "ui_modif_etudiant.h"
#include "connexionbd.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QMetaType>
#include <QRegularExpressionValidator>

extern QSqlDatabase db;

modif_etudiant::modif_etudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modif_etudiant)
{
    ui->setupUi(this);

    if (!db.isOpen()) {
        db = connexionBd::connectBase();
    }

    // config note 2 decimale
    QRegularExpressionValidator *noteValidator = new QRegularExpressionValidator(QRegularExpression("^\\d{0,2}(\\.\\d{0,2})?$"), this);
    ui->lineEdit_6->setValidator(noteValidator);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &modif_etudiant::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &modif_etudiant::reject);
}

modif_etudiant::~modif_etudiant()
{
    delete ui;
}

void modif_etudiant::remplirFormulaire(const QString &matricule, const QString &nom, const QString &prenom,
                                       const QString &telephone, const QString &mail, const QString &classe, QString groupe)
{
    ui->lineEdit->setText(matricule);
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_3->setText(prenom);
    ui->lineEdit_4->setText(mail);
    ui->lineEdit_5->setText(telephone);
    ui->comboBox_classe->setCurrentText(classe);

    // recup note
    QSqlQuery query;
    query.prepare("SELECT note_presentation FROM ETUDIANT WHERE Matricule = :matricule");
    query.bindValue(":matricule", matricule);

    if (query.exec() && query.next()) {
        QVariant note = query.value(0);
        if (!note.isNull() && note.toDouble() > 0) {
            ui->lineEdit_6->setText(note.toString());
        } else {
            ui->lineEdit_6->clear();
        }
    }

    originalMatricule = matricule;
}

void modif_etudiant::on_buttonBox_accepted()
{
    QString matricule = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString telephone = ui->lineEdit_5->text();
    QString mail = ui->lineEdit_4->text();
    QString codeClasse = ui->comboBox_classe->currentText();
    QString notePresentation = ui->lineEdit_6->text();

    if (matricule.isEmpty() || nom.isEmpty() || prenom.isEmpty() || codeClasse.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Matricule, Nom, Prénom et Classe sont obligatoires !");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE ETUDIANT SET "
                  "Matricule = :matricule, "
                  "Nom_etudiant = :nom, "
                  "Prenom_etudiant = :prenom, "
                  "Telephone_etudiant = :telephone, "
                  "Mail_etudiant = :mail, "
                  "CLASSE_num_classe = :classe, "
                  "note_presentation = :note_presentation "
                  "WHERE Matricule = :ancienMatricule");

    query.bindValue(":matricule", matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);

    if (mail.isEmpty()) {
        query.bindValue(":mail", QVariant(QMetaType::fromType<QString>()));
    } else {
        query.bindValue(":mail", mail);
    }

    query.bindValue(":classe", codeClasse);

    if (notePresentation.isEmpty()) {
        query.bindValue(":note_presentation", QVariant());
    } else {
        query.bindValue(":note_presentation", notePresentation.toDouble());
    }

    query.bindValue(":ancienMatricule", originalMatricule);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la mise à jour : " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "L'étudiant a été modifié avec succès !");
        accept();
    }
}

void modif_etudiant::on_buttonBox_rejected()
{
    this->close();
}
