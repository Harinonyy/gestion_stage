#include "form_enseignant.h"
#include "ui_form_enseignant.h"
#include "connexionbd.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>


form_enseignant::form_enseignant(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::form_enseignant)
{
    ui->setupUi(this);

    if (!db.open()){
        db = connexionBd::connectBase();
    }

    connect(ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString &text) {
        QString upper = text.toUpper();
        if (text != upper) {
            ui->lineEdit->setText(upper);
        }
    });

        connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [this](const QString &text) {
            QString upper = text.toUpper();
            if (text != upper) {
                ui->lineEdit_2->setText(upper);
            }
        });
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [this](const QString &text) {
        QString formatted = text.toLower();
        bool capitalizeNext = true;
        for (int i = 0; i < formatted.size(); ++i) {
            if (capitalizeNext && formatted[i].isLetter()) {
                formatted[i] = formatted[i].toUpper();
                capitalizeNext = false;
            } else if (formatted[i].isSpace()) {
                capitalizeNext = true;
            }
        }
        if (text != formatted) {
            ui->lineEdit_3->setText(formatted);
        }
    });

    QRegularExpression regexTel("^(032|033|034|037|038)[0-9]{7}$");
    QRegularExpressionValidator *validatorTel = new QRegularExpressionValidator(regexTel, this);
    ui->lineEdit_5->setValidator(validatorTel);
}

form_enseignant::~form_enseignant()
{
    delete ui;
}

void form_enseignant::on_buttonBox_accepted()
{
    QString trilogie = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString email = ui->lineEdit_4->text();
    QString telephone = ui->lineEdit_5->text();

    if (trilogie.isEmpty() || nom.isEmpty() || prenom.isEmpty()){
        QMessageBox::information(this, "Enseignant", "Veuiller remplir tout les champs.");
        return;
    }

    QSqlQuery enseignant;
    enseignant.prepare("INSERT INTO enseignant (Trilogie_ens, nom_enseignant, prenom_enseignant, telephone_enseignant, mail_enseignant)"
                       " VALUES (:trilogie, :nom, :prenom, :telephone, :email)");
    enseignant.bindValue(":trilogie", trilogie);
    enseignant.bindValue(":nom", nom);
    enseignant.bindValue(":prenom", prenom);
    enseignant.bindValue(":email", email);
    enseignant.bindValue(":telephone", telephone);

    if(!enseignant.exec()){
        QMessageBox::warning(this, "Enseignant", "Erreur lors de l'inscription de l'enseignant.");
        qDebug()<<"Erreur de la requète de l'enseignant : "<<enseignant.lastError().text();
    }else{
        QMessageBox::information(this, "Enseignant","L'inscription de l'enseignant réussie.");

        MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
        if (mw) {
            mw->loadEnseignants();
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
    }
}


void form_enseignant::on_buttonBox_rejected()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    this->close();
}

