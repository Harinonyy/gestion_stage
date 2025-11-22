#include "form_theme.h"
#include "ui_form_theme.h"
#include "connexionbd.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QCompleter>
#include <QSqlQueryModel>

form_theme::form_theme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::form_theme)
{
    ui->setupUi(this);

    // Connexion
    if (!db.open()){
        db = connexionBd::connectBase();
    }

    ui->comboBox->setEditable(true);
    ui->comboBox_3->setEditable(true);

    // charge les enseignants
    QSqlQueryModel *modelEnseignant = new QSqlQueryModel(this);
    modelEnseignant->setQuery("SELECT Trilogie_ens, CONCAT(Nom_enseignant, ' ', Prenom_enseignant) FROM enseignant", db);

    // charge les parcours
    QSqlQueryModel *modelParcours = new QSqlQueryModel(this);
    modelParcours->setQuery("SELECT code_parcours, code_parcours FROM parcours ORDER BY code_parcours", db);

    ui->comboBox->setModel(modelEnseignant);
    ui->comboBox->setModelColumn(1);

    // comboBox parcours avec misy generique
    ui->comboBox_3->clear();
    ui->comboBox_3->addItem("Thème générique (Tous parcours)", "");

    // tt les parcours
    for (int i = 0; i < modelParcours->rowCount(); ++i) {
        QString code = modelParcours->index(i, 0).data().toString();
        ui->comboBox_3->addItem(code, code);
    }

    // num theme auto
    genererNumeroTheme();

    // insaisissable
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setStyleSheet("background-color: #f8f8f8; color: #666;");

    QCompleter *completerEns = new QCompleter(modelEnseignant, this);
    completerEns->setCompletionColumn(1);
    completerEns->setCaseSensitivity(Qt::CaseInsensitive);
    completerEns->setFilterMode(Qt::MatchContains);

    QCompleter *completerPar = new QCompleter(ui->comboBox_3->model(), this);
    completerPar->setCompletionColumn(0);
    completerPar->setCaseSensitivity(Qt::CaseInsensitive);
    completerPar->setFilterMode(Qt::MatchContains);

    ui->comboBox->setCompleter(completerEns);
    ui->comboBox_3->setCompleter(completerPar);
}

form_theme::~form_theme()
{
    delete ui;
}

void form_theme::genererNumeroTheme()
{
    QSqlQuery query(db);
    query.prepare("SELECT COALESCE(MAX(num_theme), 0) + 1 FROM theme");

    if (query.exec() && query.next()) {
        int nouveauNumero = query.value(0).toInt();
        ui->lineEdit->setText(QString::number(nouveauNumero));
    } else {
        ui->lineEdit->setText("1");
    }
}

void form_theme::on_buttonBox_accepted()
{
    int num = ui->lineEdit->text().toInt();
    QString libelle = ui->lineEdit_2->text();
    QString description = ui->textEdit->toPlainText();

    // Recup la trilogie enseignant
    QModelIndex currentIndex = ui->comboBox->model()->index(ui->comboBox->currentIndex(), 0);
    QString enseignant = ui->comboBox->model()->data(currentIndex).toString();

    // Recup le parcours
    QString parcour = ui->comboBox_3->currentData().toString();

    //champs obligatoire
    if (libelle.isEmpty() || enseignant.isEmpty()) {
        QMessageBox::warning(this, "Champs obligatoires", "Le libellé et l'enseignant sont obligatoires !");
        return;
    }

    QSqlQuery theme;
    theme.prepare("INSERT INTO theme (num_theme, libelle, description, ENSEIGNANT_Trilogie_ens, PARCOURS_code_parcours) "
                  "VALUES (:num, :libelle, :description, :enseignant, :parcour)");
    theme.bindValue(":num", num);
    theme.bindValue(":libelle", libelle);
    theme.bindValue(":description", description);
    theme.bindValue(":enseignant", enseignant);


    if (parcour.isEmpty()) {
        theme.bindValue(":parcour", QVariant());
    } else {
        theme.bindValue(":parcour", parcour);
    }

    if(!theme.exec()){
        QMessageBox::warning(this, "Theme", "Erreur lors de l'enregistrement du theme: " + theme.lastError().text());
        qDebug() << "Erreur de la requête theme : " << theme.lastError().text();
    } else {
        QMessageBox::information(this, "Theme", "L'ajout du thème réussi.");

        MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
        if (mw) {
            mw->loadThemes();
        }

        ui->lineEdit_2->clear();
        ui->textEdit->clear();
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_3->setCurrentIndex(0);

        // recup num theme suivant
        genererNumeroTheme();
    }
}

void form_theme::on_buttonBox_rejected()
{
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    this->close();
}
