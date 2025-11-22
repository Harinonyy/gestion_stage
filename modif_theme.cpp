#include "modif_theme.h"
#include "ui_modif_theme.h"
#include "connexionbd.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QCompleter>
#include <QSqlQueryModel>

extern QSqlDatabase db;

modif_theme::modif_theme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::modif_theme)
{
    ui->setupUi(this);

    if (!db.isOpen()) {
        db = connexionBd::connectBase();
    }

    ui->comboBox->setEditable(true);
    ui->comboBox_3->setEditable(true);

    // enseignants
    QSqlQueryModel *modelEnseignant = new QSqlQueryModel(this);
    modelEnseignant->setQuery("SELECT Trilogie_ens, CONCAT(Nom_enseignant, ' ', Prenom_enseignant) FROM enseignant", db);

    // parcours
    QSqlQueryModel *modelParcours = new QSqlQueryModel(this);
    modelParcours->setQuery("SELECT code_parcours, code_parcours FROM parcours ORDER BY code_parcours", db);

    ui->comboBox->setModel(modelEnseignant);
    ui->comboBox->setModelColumn(1);

    ui->comboBox_3->clear();
    ui->comboBox_3->addItem("Thème générique (Tous parcours)", "");

    // parcours existants
    for (int i = 0; i < modelParcours->rowCount(); ++i) {
        QString code = modelParcours->index(i, 0).data().toString();
        ui->comboBox_3->addItem(code, code);
    }

    // Num non saisissable
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

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &modif_theme::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &modif_theme::reject);
}

modif_theme::~modif_theme()
{
    delete ui;
}

void modif_theme::remplirFormulaire(int num_theme, const QString &libelle, const QString &description,
                                    const QString &enseignant_trilogie, const QString &parcours_code)
{
    ui->lineEdit->setText(QString::number(num_theme));
    ui->lineEdit_2->setText(libelle);
    ui->textEdit->setPlainText(description);


    QAbstractItemModel *model = ui->comboBox->model();
    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->index(i, 0).data().toString() == enseignant_trilogie) {
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }

    // select parcours
    if (parcours_code.isEmpty()) {
        ui->comboBox_3->setCurrentIndex(0);
    } else {
        ui->comboBox_3->setCurrentText(parcours_code);
    }

    originalNumTheme = num_theme;
}

void modif_theme::on_buttonBox_accepted()
{
    int num = ui->lineEdit->text().toInt();
    QString libelle = ui->lineEdit_2->text();
    QString description = ui->textEdit->toPlainText();

    // recup trilogie enseignant
    QModelIndex currentIndex = ui->comboBox->model()->index(ui->comboBox->currentIndex(), 0);
    QString enseignant = ui->comboBox->model()->data(currentIndex).toString();

    // recup le parcours
    QString parcour = ui->comboBox_3->currentData().toString();

    // champs obligatoires
    if (libelle.isEmpty() || enseignant.isEmpty()) {
        QMessageBox::warning(this, "Champs obligatoires", "Le libellé et l'enseignant sont obligatoires !");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE theme SET "
                  "libelle = :libelle, "
                  "description = :description, "
                  "ENSEIGNANT_Trilogie_ens = :enseignant, "
                  "PARCOURS_code_parcours = :parcour "
                  "WHERE num_theme = :ancienNum");

    query.bindValue(":libelle", libelle);
    query.bindValue(":description", description);
    query.bindValue(":enseignant", enseignant);

    if (parcour.isEmpty()) {
        query.bindValue(":parcour", QVariant());
    } else {
        query.bindValue(":parcour", parcour);
    }

    query.bindValue(":ancienNum", originalNumTheme);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la mise à jour : " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "Le thème a été modifié avec succès !");
        accept();
    }
}
