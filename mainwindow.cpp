#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form_etudiant.h"
#include "form_groupe.h"
#include "form_enseignant.h"
#include "form_theme.h"
#include "modif_etudiant.h"
#include "modif_groupe.h"
#include "modif_enseignant.h"
#include "modif_theme.h"
#include "connexionbd.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QFont>
#include <QBrush>
#include <QColor>
#include <QGraphicsDropShadowEffect>


QSqlDatabase db;

void MainWindow::reset_buttons()
{
    ui->btn_dashboard->setChecked(false);
    ui->btn_etudiants->setChecked(false);
    ui->btn_groupes->setChecked(false);
    ui->btn_enseignants->setChecked(false);
    ui->btn_themes->setChecked(false);
    ui->btn_evaluation->setChecked(false);

    ui->btn_icone_dashboard->setChecked(false);
    ui->btn_icone_etudiants->setChecked(false);
    ui->btn_icone_groupes->setChecked(false);
    ui->btn_icone_enseignants->setChecked(false);
    ui->btn_icone_themes->setChecked(false);
    ui->btn_icone_evaluation->setChecked(false);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->showMaximized();

    db = connexionBd::connectBase();

    connect(ui->btn_etudiantsansnote, &QPushButton::clicked,
            this, &MainWindow::on_btn_etudiantsansnote_clicked);

    connect(ui->recherche, &QLineEdit::textChanged,
            this, &MainWindow::on_recherche_textChanged);

    connect(ui->filtre_groupe_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_filtre_groupe_2_currentIndexChanged);

    ui->containers_widget->setCurrentIndex(0);

    ui->table_themes->setStyleSheet(
        "QTableView::item { vertical-align: top; }"
        );
    connect(ui->filtre_classe, &QComboBox::currentTextChanged, this, &MainWindow::updateGroupesCombo);
    connect(ui->filtre_groupe, &QComboBox::currentTextChanged, this, &MainWindow::filterEtudiants);
    connect(ui->recherche_etudiants, &QLineEdit::textChanged, this, &MainWindow::on_recherche_etudiants_textChanged);
    updateGroupesCombo(ui->filtre_classe->currentText());

    connect(ui->btn_icone_dashboard, &QPushButton::clicked, this, &MainWindow::on_btn_dashboard_clicked);
    connect(ui->btn_icone_etudiants, &QPushButton::clicked, this, &MainWindow::on_btn_etudiants_clicked);
    connect(ui->btn_icone_groupes, &QPushButton::clicked, this, &MainWindow::on_btn_groupes_clicked);
    connect(ui->btn_icone_enseignants, &QPushButton::clicked, this, &MainWindow::on_btn_enseignants_clicked);
    connect(ui->btn_icone_themes, &QPushButton::clicked, this, &MainWindow::on_btn_themes_clicked);
    connect(ui->btn_icone_evaluation, &QPushButton::clicked, this, &MainWindow::on_btn_evaluation_clicked);

    ui->containers_widget->setCurrentIndex(0);
    ui->btn_dashboard->setChecked(true);
    ui->btn_icone_dashboard->setChecked(true);

    loadEtudiants();
    loadGroupes();
    loadEnseignants();
    loadThemes();
    loadEvaluationTable();
    afficherStatEtudiants();
    afficherStatGroupes();
    afficherStatEnseignants();
    afficherStatThemes();
    chargerFiltreEncadreurs();
    chargerFiltreClasses();
    chargerFiltreClassesEtudiant();

    initialiserFiltreParcours(); //theme
    applyShadowToCards();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::applyShadowToCards() {
    const QList<QFrame*> allCards = {
        ui->card1_1, ui->card1_2, ui->card1_3, ui->card1_4,
        ui->card2_1, ui->card2_2, ui->card2_3, ui->card2_4
    };

    for (QFrame* card : allCards) {
        auto shadow = new QGraphicsDropShadowEffect(card);
        shadow->setBlurRadius(18);
        shadow->setOffset(0, 4);
        card->setGraphicsEffect(shadow);
    }
}
// nav
void MainWindow::on_btn_dashboard_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(0);
    ui->btn_dashboard->setChecked(true);
    ui->btn_icone_dashboard->setChecked(true);
}

void MainWindow::on_btn_etudiants_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(1);
    ui->btn_etudiants->setChecked(true);
    ui->btn_icone_etudiants->setChecked(true);
}

void MainWindow::on_btn_groupes_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(2);
    ui->btn_groupes->setChecked(true);
    ui->btn_icone_groupes->setChecked(true);
}

void MainWindow::on_btn_enseignants_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(3);
    ui->btn_enseignants->setChecked(true);
    ui->btn_icone_enseignants->setChecked(true);
}

void MainWindow::on_btn_themes_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(4);
    ui->btn_themes->setChecked(true);
    ui->btn_icone_themes->setChecked(true);
}

void MainWindow::on_btn_evaluation_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(5);
    ui->btn_evaluation->setChecked(true);
    ui->btn_icone_evaluation->setChecked(true);
    loadEvaluationTable();
}

// OUVERTURE FORMULAIRES
void MainWindow::on_btn_add_etudiants_clicked()
{
    form_etudiant *form = new form_etudiant(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_groupes_clicked()
{
    form_groupe *form = new form_groupe(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_enseignants_clicked()
{
    form_enseignant *form = new form_enseignant(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_themes_clicked()
{
    form_theme *form = new form_theme(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_etudiant_clicked()
{
    on_btn_add_etudiants_clicked();
}

void MainWindow::on_btn_add_groupe_clicked()
{
    on_btn_add_groupes_clicked();
}

void MainWindow::on_btn_add_enseignant_clicked()
{
    on_btn_add_enseignants_clicked();
}

void MainWindow::on_btn_add_theme_clicked()
{
    on_btn_add_themes_clicked();
}

// read

void MainWindow::loadEtudiants(const QString& sqlFilter)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString queryStr = "SELECT "
                       "E.Matricule, E.Nom_etudiant, E.Prenom_etudiant, "
                       "E.Telephone_etudiant, E.Mail_etudiant, "
                       "E.CLASSE_num_classe, "
                       "COALESCE(E.GROUPE_num_groupe, 'Sans groupe') AS Groupe, "
                       "E.note_presentation "
                       "FROM ETUDIANT E "
                       "LEFT JOIN GROUPE G ON E.GROUPE_num_groupe = G.num_groupe AND E.CLASSE_num_classe = G.CLASSE_num_classe ";

    if (!sqlFilter.isEmpty()) {
        queryStr += " WHERE " + sqlFilter;
    }

    queryStr += " ORDER BY E.Nom_etudiant ASC";

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL loadEtudiants :" << model->lastError().text();
        QMessageBox::critical(this, "Erreur BD", "Impossible de charger les étudiants : " + model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Matricule");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Email");
    model->setHeaderData(5, Qt::Horizontal, "Classe");
    model->setHeaderData(6, Qt::Horizontal, "Groupe");
    model->setHeaderData(7, Qt::Horizontal, "Note Présentation");

    ui->table_etudiants->setModel(model);
    ui->table_etudiants->resizeColumnsToContents();
    ui->table_etudiants->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::loadGroupes(const QString& encadreurTrilogie, const QString& numGroupeFiltre)
{
    QSqlQueryModel *model_groupes = new QSqlQueryModel(this);

    QString queryStr = "SELECT "
                       "g.num_groupe, "
                       "c.num_classe, "
                       "t.libelle, "
                       "CONCAT(e.Nom_enseignant, ' ', e.Prenom_enseignant) AS NomEncadreur, "
                       "g.note_rapport, "
                       "g.note_application "
                       "FROM GROUPE g "
                       "LEFT JOIN ENSEIGNANT e ON g.ENSEIGNANT_Trilogie_ens = e.Trilogie_ens "
                       "LEFT JOIN THEME t ON g.THEME_num_theme = t.num_theme "
                       "LEFT JOIN CLASSE c ON g.CLASSE_num_classe = c.num_classe ";

    QStringList conditions;

    if (!encadreurTrilogie.isEmpty()) {
        conditions << QString("g.ENSEIGNANT_Trilogie_ens = '%1'").arg(encadreurTrilogie);
    }

    if (!numGroupeFiltre.isEmpty()) {
        conditions << QString("g.num_groupe LIKE '%%1%'").arg(numGroupeFiltre);
    }

    if (!conditions.isEmpty()) {
        queryStr += " WHERE " + conditions.join(" AND ");
    }

    queryStr += " ORDER BY g.num_groupe ASC";

    model_groupes->setQuery(queryStr);

    if (model_groupes->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Impossible d'afficher la liste des groupes : " + model_groupes->lastError().text());
        qDebug() << "Erreur de requête GROUPES:" << model_groupes->lastError().text();
        return;
    }

    model_groupes->setHeaderData(0, Qt::Horizontal, "Groupe");
    model_groupes->setHeaderData(1, Qt::Horizontal, "Classe");
    model_groupes->setHeaderData(2, Qt::Horizontal, "Thème");
    model_groupes->setHeaderData(3, Qt::Horizontal, "Encadreur");
    model_groupes->setHeaderData(4, Qt::Horizontal, "Note de Rapport");
    model_groupes->setHeaderData(5, Qt::Horizontal, "Note Application");

    ui->table_groupes->setModel(model_groupes);

    ui->table_groupes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_groupes->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->table_groupes->resizeColumnsToContents();
    ui->table_groupes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::loadEnseignants()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT Trilogie_ens, Nom_enseignant, Prenom_enseignant, Telephone_enseignant, Mail_enseignant FROM enseignant");

    if(model->lastError().isValid()){
        QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Trilogie");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Email");

    ui->table_enseignants->setModel(model);
    ui->table_enseignants->resizeColumnsToContents();
    ui->table_enseignants->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::loadThemes()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT t.num_theme, "
                    "COALESCE(t.PARCOURS_code_parcours, 'Générique') AS Parcours, "
                    "t.libelle, "
                    "CONCAT(e.Nom_enseignant, ' ', e.Prenom_enseignant) AS Enseignant, "
                    "t.description "
                    "FROM theme t "
                    "LEFT JOIN enseignant e ON t.ENSEIGNANT_Trilogie_ens = e.Trilogie_ens "
                    "ORDER BY t.num_theme");

    if (model->lastError().isValid()){
        QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Numéro");
    model->setHeaderData(1, Qt::Horizontal, "Parcours");
    model->setHeaderData(2, Qt::Horizontal, "Libellé");
    model->setHeaderData(3, Qt::Horizontal, "Enseignant");
    model->setHeaderData(4, Qt::Horizontal, "Description");

    ui->table_themes->setModel(model);
    ui->table_themes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_themes->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->table_themes->setWordWrap(true);
    ui->table_themes->setAlternatingRowColors(true);
    ui->table_themes->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    ui->table_themes->resizeColumnsToContents();
    ui->table_themes->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->table_themes->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}

void MainWindow::loadEvaluationTable(const QString& sqlFilter, bool isSimpleMode)
{
    QString queryStr = "SELECT "
                       "G.num_groupe, C.num_classe, "
                       "E.Matricule, E.Nom_etudiant, E.Prenom_etudiant, "
                       "E.note_presentation, "
                       "G.note_rapport, "
                       "G.note_application "
                       "FROM GROUPE G "
                       "JOIN ETUDIANT E ON G.num_groupe = E.GROUPE_num_groupe AND G.CLASSE_num_classe = E.CLASSE_num_classe "
                       "JOIN CLASSE C ON G.CLASSE_num_classe = C.num_classe ";

    if (!sqlFilter.isEmpty()) {
        queryStr += " WHERE " + sqlFilter;
    }

    queryStr += " ORDER BY G.num_groupe ASC, E.Nom_etudiant ASC";

    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Erreur Requête Évaluation:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur BD", "Impossible de charger l'évaluation.");
        return;
    }

    if (isSimpleMode || !sqlFilter.isEmpty())
    {
        QStandardItemModel *modeleSimple = new QStandardItemModel(this);
        modeleSimple->setHorizontalHeaderLabels({
            "Groupe", "Classe", "Matricule", "Nom Étudiant", "Prénom",
            "Note Présentation", "Note Rapport", "Note Application", "Note Définitive"
        });

        int row = 0;
        while (query.next()) {
            QString numGroupe = query.value(0).toString();
            QString numClasse = query.value(1).toString();
            QString matricule = query.value(2).toString();
            QString nomEtudiant = query.value(3).toString();
            QString prenomEtudiant = query.value(4).toString();
            QVariant notePresentation = query.value(5);
            QVariant noteRapport = query.value(6);
            QVariant noteApplication = query.value(7);

            // note def
            QString noteDefinitive = "";
            if (!notePresentation.isNull() && !noteRapport.isNull() && !noteApplication.isNull()) {
                double moyenne = (notePresentation.toDouble() +
                                  noteRapport.toDouble() +
                                  noteApplication.toDouble()) / 3.0;
                noteDefinitive = QString::number(round(moyenne * 100) / 100, 'f', 2);
            }

            modeleSimple->setItem(row, 0, new QStandardItem(numGroupe));
            modeleSimple->setItem(row, 1, new QStandardItem(numClasse));
            modeleSimple->setItem(row, 2, new QStandardItem(matricule));
            modeleSimple->setItem(row, 3, new QStandardItem(nomEtudiant));
            modeleSimple->setItem(row, 4, new QStandardItem(prenomEtudiant));
            modeleSimple->setItem(row, 5, new QStandardItem(notePresentation.isNull() ? "" : notePresentation.toString()));
            modeleSimple->setItem(row, 6, new QStandardItem(noteRapport.isNull() ? "" : noteRapport.toString()));
            modeleSimple->setItem(row, 7, new QStandardItem(noteApplication.isNull() ? "" : noteApplication.toString()));
            modeleSimple->setItem(row, 8, new QStandardItem(noteDefinitive));

            row++;
        }

        ui->table_evaluation->setModel(modeleSimple);
    }
    else
    {
        QStandardItemModel *model = new QStandardItemModel(this);

        model->setHorizontalHeaderLabels({
            "Groupe", "Classe", "Nom & Prénom Étudiant",
            "Note Présentation", "Note Rapport", "Note Application", "Note Définitive"
        });

        QString currentGroup = "";
        int row = 0;

        while (query.next())
        {
            QString numGroupe = query.value(0).toString();
            QString numClasse = query.value(1).toString();
            QString nomEtudiant = query.value(3).toString();
            QString prenomEtudiant = query.value(4).toString();
            QVariant notePresentation = query.value(5);
            QVariant noteRapport = query.value(6);
            QVariant noteApplication = query.value(7);

            // note def
            QString noteDefinitive = "";
            if (!notePresentation.isNull() && !noteRapport.isNull() && !noteApplication.isNull()) {
                double moyenne = (notePresentation.toDouble() +
                                  noteRapport.toDouble() +
                                  noteApplication.toDouble()) / 3.0;
                noteDefinitive = QString::number(round(moyenne * 100) / 100, 'f', 2);
            }

            model->setItem(row, 0, new QStandardItem(numGroupe));
            model->setItem(row, 1, new QStandardItem(numClasse));
            model->setItem(row, 2, new QStandardItem(QString("%1 %2").arg(nomEtudiant, prenomEtudiant)));
            model->setItem(row, 3, new QStandardItem(notePresentation.isNull() ? "" : notePresentation.toString()));
            model->setItem(row, 4, new QStandardItem(noteRapport.isNull() ? "" : noteRapport.toString()));
            model->setItem(row, 5, new QStandardItem(noteApplication.isNull() ? "" : noteApplication.toString()));
            model->setItem(row, 6, new QStandardItem(noteDefinitive));

            // Mettre en gras
            if (numGroupe != currentGroup) {
                for (int col = 0; col < model->columnCount(); ++col) {
                    if (model->item(row, col)) {
                        model->item(row, col)->setFont(QFont("Arial", 10, QFont::Bold));
                    }
                }
                currentGroup = numGroupe;
            }

            row++;
        }

        ui->table_evaluation->setModel(model);
    }

    ui->table_evaluation->resizeColumnsToContents();
    ui->table_evaluation->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
// STATISTIQUES
void MainWindow::afficherStatEtudiants()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM etudiant"))
    {
        if (query.next()) {
            int totalEtudiants = query.value(0).toInt();
            ui->label_3->setText(QString::number(totalEtudiants));
        }
    }
    else {
        qDebug() << "Erreur de la requête étudiants :" << query.lastError().text();
    }
}

void MainWindow::afficherStatGroupes()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM groupe"))
    {
        if (query.next()){
            int totalGroupe = query.value(0).toInt();
            ui->lbl_total_groupes->setText(QString::number(totalGroupe));
        }
    }
    else {
        qDebug() <<"Erreur de la requête groupes :" << query.lastError().text();
    }
}

void MainWindow::afficherStatEnseignants()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM enseignant"))
    {
        if (query.next()){
            int totalEnseignant = query.value(0).toInt();
            ui->lbl_total_enseignants->setText(QString::number(totalEnseignant));
        }
    }
    else {
        qDebug() << "Erreur de la requête enseignants :" << query.lastError().text();
    }
}

void MainWindow::afficherStatThemes()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM theme"))
    {
        if (query.next()){
            int totalTheme = query.value(0).toInt();
            ui->lbl_total_themes->setText(QString::number (totalTheme));
        }
    }
    else {
        qDebug() <<"Erreur de la requête themes :" << query.lastError().text();
    }
}

// filtres
void MainWindow::chargerFiltreEncadreurs()
{
    ui->filtre_encadreur->clear();
    ui->filtre_encadreur->addItem("Tous les Encadreurs");

    QSqlQuery query;
    if (query.exec("SELECT Trilogie_ens, Nom_enseignant, Prenom_enseignant FROM ENSEIGNANT ORDER BY Nom_enseignant")) {
        while (query.next()) {
            QString trilogie = query.value(0).toString();
            QString nomComplet = query.value(1).toString() + " " + query.value(2).toString();
            ui->filtre_encadreur->addItem(nomComplet, trilogie);
        }
    } else {
        qDebug() << "Erreur de chargement des encadreurs :" << query.lastError().text();
    }
}

void MainWindow::chargerFiltreClassesEtudiant()
{
    ui->filtre_classe->clear();
    ui->filtre_classe->addItem("Toutes les Classes");

    QSqlQuery query;
    if (query.exec("SELECT num_classe FROM CLASSE ORDER BY num_classe")) {
        while (query.next()) {
            ui->filtre_classe->addItem(query.value(0).toString());
        }
    } else {
        qDebug() << "Erreur de chargement des classes étudiant :" << query.lastError().text();
    }
}

void MainWindow::updateGroupesCombo(const QString &classe)
{
    ui->filtre_groupe->clear();
    ui->filtre_groupe->addItem("Tous les Groupes", QVariant());

    QSqlQuery query;
    QString queryString;

    if (classe == "Toutes les Classes" || classe.isEmpty()) {
        queryString = "SELECT num_groupe, num_groupe FROM GROUPE ORDER BY num_groupe";
    } else {
        queryString = QString(
                          "SELECT G.num_groupe, G.num_groupe FROM GROUPE G "
                          "WHERE G.CLASSE_num_classe = '%1' "
                          "ORDER BY G.num_groupe"
                          ).arg(classe);
    }

    if (query.exec(queryString)) {
        while (query.next()) {
            QString numGroupe = query.value(0).toString();
            ui->filtre_groupe->addItem(numGroupe, numGroupe);
        }
    } else {
        qDebug() << "Erreur SQL updateGroupesCombo:" << query.lastError().text();
    }

    filterEtudiants("");
}

void MainWindow::filterEtudiants(const QString &)
{
    QString classe = ui->filtre_classe->currentText();
    QString numGroupe = ui->filtre_groupe->currentData().toString();

    QString filtreSql = "";
    bool filterApplied = false;

    if (classe != "Toutes les Classes" && !classe.isEmpty()) {
        filtreSql = QString("G.CLASSE_num_classe = '%1'").arg(classe);
        filterApplied = true;
    }

    if (!numGroupe.isEmpty()) {
        if (filterApplied) {
            filtreSql += " AND ";
        }
        filtreSql += QString("E.GROUPE_num_groupe = '%1'").arg(numGroupe);
        filterApplied = true;
    }

    if (ui->recherche_etudiants->text().isEmpty()) {
        loadEtudiants(filtreSql);
    }
}

// recherche
void MainWindow::on_recherche_etudiants_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        filterEtudiants("");
        return;
    }

    QString valeur = "%" + text + "%";
    QString filtreSql = QString(
                            "E.Matricule LIKE '%1' OR E.Nom_etudiant LIKE '%1' OR E.Prenom_etudiant LIKE '%1'"
                            ).arg(valeur);

    loadEtudiants(filtreSql);
}

void MainWindow::on_filtre_encadreur_currentIndexChanged(int index)
{
    QString trilogie = ui->filtre_encadreur->currentData().toString();

    if (trilogie.isEmpty()) {
        loadGroupes("", ui->recherche_groupes->text().trimmed());
    } else {
        loadGroupes(trilogie, ui->recherche_groupes->text().trimmed());
    }
}

void MainWindow::on_recherche_groupes_textChanged(const QString &arg1)
{
    QString numGroupeFiltre = arg1;
    QString encadreurTrilogie = ui->filtre_encadreur->currentData().toString();
    loadGroupes(encadreurTrilogie, numGroupeFiltre);
}

// page evaluation
void MainWindow::on_btn_etudiantsansnote_clicked()
{
    QString filter = "E.note_presentation IS NULL OR G.note_rapport IS NULL OR G.note_application IS NULL";
    loadEvaluationTable(filter, true);
}

void MainWindow::on_recherche_textChanged(const QString &texteRecherche)
{
    QString filtre = "";

    if (!texteRecherche.isEmpty()) {
        filtre = QString("(G.num_groupe LIKE '%%1%') OR (E.Matricule LIKE '%%1%')").arg(texteRecherche);
    }

    loadEvaluationTable(filtre);
}

void MainWindow::chargerFiltreClasses()
{
    ui->filtre_groupe_2->clear();
    ui->filtre_groupe_2->addItem("Toutes les Classes", QVariant());

    QSqlQuery query;
    if (query.exec("SELECT num_classe FROM CLASSE ORDER BY num_classe")) {
        while (query.next()) {
            QString numClasse = query.value(0).toString();
            ui->filtre_groupe_2->addItem(numClasse, numClasse);
        }
    } else {
        qDebug() << "Erreur de chargement des classes :" << query.lastError().text();
    }
}

void MainWindow::on_filtre_groupe_2_currentIndexChanged(int index)
{
    QString numClasseFiltre = ui->filtre_groupe_2->currentData().toString();

    QString filtreSql = "";
    if (!numClasseFiltre.isEmpty()) {
        filtreSql = QString("C.num_classe = '%1'").arg(numClasseFiltre);
    }

    loadEvaluationTable(filtreSql);
}

void MainWindow::on_recherche_enseignants_textChanged(const QString &text)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare(
        "SELECT Trilogie_ens, nom_enseignant, prenom_enseignant, telephone_enseignant, mail_enseignant "
        "FROM enseignant "
        "WHERE Trilogie_ens LIKE :val OR nom_enseignant LIKE :val OR prenom_enseignant LIKE :val"
        );
    query.bindValue(":val", "%" + text + "%");

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur SQL", query.lastError().text());
        return;
    }

    model->setQuery(std::move(query));

    ui->table_enseignants->setModel(model);
    ui->table_enseignants->resizeColumnsToContents();
    ui->table_enseignants->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// Delete eseignant
void MainWindow::on_btn_supprimer_enseignants_clicked()
{
    QModelIndexList selection = ui->table_enseignants->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un enseignant à supprimer.");
        return;
    }

    QString trilogie = selection.at(0).sibling(selection.at(0).row(), 0).data().toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        "Voulez-vous vraiment supprimer cet enseignant (Trilogie_ens : " + trilogie + ") ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM enseignant WHERE Trilogie_ens = :trilogie");
        query.bindValue(":trilogie", trilogie);

        if (query.exec()) {
            QMessageBox::information(this, "Succès", "L'enseignant a été supprimé avec succès !");
        } else {
            QMessageBox::warning(this, "Erreur", "La suppression a échoué : " + query.lastError().text());
        }

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT Trilogie_ens, Nom_enseignant, Prenom_enseignant, Telephone_enseignant, Mail_enseignant FROM enseignant");
        ui->table_enseignants->setModel(model);
    }
}

// Delete etudiant
void MainWindow::on_btn_supprimer_etudiants_clicked()
{
    QModelIndexList selection = ui->table_etudiants->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un étudiant à supprimer.");
        return;
    }

    QString matricule = selection.at(0).sibling(selection.at(0).row(), 0).data().toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous vraiment supprimer cet étudiant (Matricule : " + matricule + ") ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM etudiant WHERE Matricule = :matricule");
        query.bindValue(":matricule", matricule);

        if (query.exec()) {
            QMessageBox::information(this, "Succès", "L'étudiant a été supprimé avec succès !");
            loadEtudiants();
        } else {
            QMessageBox::warning(this, "Erreur SQL", "La suppression a échoué : " + query.lastError().text());
        }
    }
}

// Update etudiant
void MainWindow::on_btn_modifier_etudiants_clicked()
{
    QModelIndexList selection = ui->table_etudiants->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un étudiant à modifier.");
        return;
    }

    int row = selection.at(0).row();

    QString matricule = ui->table_etudiants->model()->index(row, 0).data().toString();
    QString nom = ui->table_etudiants->model()->index(row, 1).data().toString();
    QString prenom = ui->table_etudiants->model()->index(row, 2).data().toString();
    QString telephone = ui->table_etudiants->model()->index(row, 3).data().toString();
    QString mail = ui->table_etudiants->model()->index(row, 4).data().toString();
    QString classe = ui->table_etudiants->model()->index(row, 5).data().toString();
    QString groupe = "";

    if (ui->table_etudiants->model()->columnCount() > 6) {
        groupe = ui->table_etudiants->model()->index(row, 6).data().toString();
    }

    modif_etudiant *form = new modif_etudiant(this);
    form->remplirFormulaire(matricule, nom, prenom, telephone, mail, classe, groupe);
    form->setWindowTitle("Modifier un étudiant");
    form->exec();

    loadEtudiants();
}

// Update enseignant
void MainWindow::on_btn_modifier_enseignants_clicked()
{
    QModelIndexList selection = ui->table_enseignants->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un enseignant à modifier.");
        return;
    }

    int row = selection.at(0).row();

    QString trilogie = ui->table_enseignants->model()->index(row, 0).data().toString();
    QString nom = ui->table_enseignants->model()->index(row, 1).data().toString();
    QString prenom = ui->table_enseignants->model()->index(row, 2).data().toString();
    QString telephone = ui->table_enseignants->model()->index(row, 3).data().toString();
    QString mail = ui->table_enseignants->model()->index(row, 4).data().toString();

    modif_enseignant *form = new modif_enseignant(this);
    form->remplirFormulaire(trilogie, nom, prenom, telephone, mail);
    form->setWindowTitle("Modifier un enseignant");
    form->exec();

    loadEnseignants();
}

// Update theme
void MainWindow::on_btn_modifier_themes_clicked()
{
    QModelIndexList selection = ui->table_themes->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un thème à modifier.");
        return;
    }

    int row = selection.at(0).row();

    int num_theme = ui->table_themes->model()->index(row, 0).data().toInt();
    QString parcours_code = ui->table_themes->model()->index(row, 1).data().toString();
    QString libelle = ui->table_themes->model()->index(row, 2).data().toString();
    QString enseignant_nom = ui->table_themes->model()->index(row, 3).data().toString();
    QString description = ui->table_themes->model()->index(row, 4).data().toString();

    QString enseignant_trilogie = "";
    if (parcours_code == "Générique") {
        parcours_code = "";
    }

    // recup trilogie
    QSqlQuery query;
    query.prepare("SELECT ENSEIGNANT_Trilogie_ens FROM theme WHERE num_theme = :num_theme");
    query.bindValue(":num_theme", num_theme);
    if (query.exec() && query.next()) {
        enseignant_trilogie = query.value(0).toString();
    }

    modif_theme *form = new modif_theme(this);
    form->remplirFormulaire(num_theme, libelle, description, enseignant_trilogie, parcours_code);
    form->setWindowTitle("Modifier un thème");
    form->exec();

    loadThemes();
}

// Update theme
void MainWindow::on_btn_supprimer_themes_clicked()
{
    QModelIndexList selection = ui->table_themes->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un thème à supprimer.");
        return;
    }

    int row = selection.at(0).row();
    int num_theme = ui->table_themes->model()->index(row, 0).data().toInt();
    QString libelle = ui->table_themes->model()->index(row, 1).data().toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        "Voulez-vous vraiment supprimer le thème : " + libelle + " (N°" + QString::number(num_theme) + ") ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM theme WHERE num_theme = :num_theme");
        query.bindValue(":num_theme", num_theme);

        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Le thème a été supprimé avec succès !");
            loadThemes();
        } else {
            QMessageBox::warning(this, "Erreur", "La suppression a échoué : " + query.lastError().text());
        }
    }
}

//recherche sy filtre theme
void MainWindow::on_recherche_themes_textChanged(const QString &text)
{
    QString filtreParcours = ui->filtre_parcours->currentData().toString();
    chargerThemesAvecFiltres(text, filtreParcours);
}

void MainWindow::on_filtre_parcours_currentIndexChanged(int index)
{
    QString recherche = ui->recherche_themes->text();
    QString filtreParcours = ui->filtre_parcours->currentData().toString();
    chargerThemesAvecFiltres(recherche, filtreParcours);
}

void MainWindow::chargerThemesAvecFiltres(const QString &recherche, const QString &filtreParcours)
{
    QStringList conditions;

    // Filtre par recherche
    if (!recherche.isEmpty()) {
        conditions << QString("t.libelle LIKE '%%1%'").arg(recherche);
    }

    // Filtre par parcours
    if (filtreParcours == "generique") {
        conditions << "t.PARCOURS_code_parcours IS NULL";
    } else if (!filtreParcours.isEmpty()) {
        conditions << QString("t.PARCOURS_code_parcours = '%1'").arg(filtreParcours);
    }

    QString whereClause = conditions.isEmpty() ? "" : "WHERE " + conditions.join(" AND ");

    QString queryStr = QString(
                           "SELECT t.num_theme, "
                           "COALESCE(t.PARCOURS_code_parcours, 'Générique') AS Parcours, "
                           "t.libelle, "
                           "CONCAT(e.Nom_enseignant, ' ', e.Prenom_enseignant) AS Enseignant, "
                           "t.description "
                           "FROM theme t "
                           "LEFT JOIN enseignant e ON t.ENSEIGNANT_Trilogie_ens = e.Trilogie_ens "
                           "%1 "
                           "ORDER BY t.num_theme"
                           ).arg(whereClause);

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryStr);

    if (model->lastError().isValid()){
        qDebug() << "Erreur SQL chargerThemesAvecFiltres:" << model->lastError().text();
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Numéro");
    model->setHeaderData(1, Qt::Horizontal, "Parcours");
    model->setHeaderData(2, Qt::Horizontal, "Libellé");
    model->setHeaderData(3, Qt::Horizontal, "Enseignant");
    model->setHeaderData(4, Qt::Horizontal, "Description");

    ui->table_themes->setModel(model);
    ui->table_themes->resizeColumnsToContents();
    ui->table_themes->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->table_themes->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}
void MainWindow::initialiserFiltreParcours()
{
    ui->filtre_parcours->clear();
    ui->filtre_parcours->addItem("Tous les parcours", "");
    ui->filtre_parcours->addItem("Thèmes génériques", "generique");

    QSqlQuery query("SELECT code_parcours FROM parcours ORDER BY code_parcours");
    while (query.next()) {
        QString parcours = query.value(0).toString();
        ui->filtre_parcours->addItem(parcours, parcours);
    }

    connect(ui->recherche_themes, &QLineEdit::textChanged, this, &MainWindow::on_recherche_themes_textChanged);
    connect(ui->filtre_parcours, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_filtre_parcours_currentIndexChanged);
}

//Delete groupe
void MainWindow::on_btn_supprimer_groupes_clicked()
{
    QModelIndexList selection = ui->table_groupes->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un groupe à supprimer.");
        return;
    }

    int row = selection.at(0).row();
    QString numGroupe = ui->table_groupes->model()->index(row, 0).data().toString();
    QString nomClasse = ui->table_groupes->model()->index(row, 1).data().toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        "Voulez-vous vraiment supprimer le groupe : " + numGroupe + " de la classe " + nomClasse + " ?\n\n"
                                                                                                   "⚠️ Cette action supprimera également l'affectation de tous les étudiants de ce groupe.",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QSqlDatabase::database().transaction();

        try {

            QSqlQuery updateEtudiants;
            updateEtudiants.prepare("UPDATE ETUDIANT SET GROUPE_num_groupe = NULL "
                                    "WHERE GROUPE_num_groupe = :groupe");
            updateEtudiants.bindValue(":groupe", numGroupe);

            if (!updateEtudiants.exec()) {
                throw std::runtime_error("Erreur désaffectation étudiants: " + updateEtudiants.lastError().text().toStdString());
            }

            QSqlQuery deleteGroupe;
            deleteGroupe.prepare("DELETE FROM GROUPE WHERE num_groupe = :groupe AND CLASSE_num_classe = :classe");
            deleteGroupe.bindValue(":groupe", numGroupe);
            deleteGroupe.bindValue(":classe", nomClasse);

            if (!deleteGroupe.exec()) {
                throw std::runtime_error("Erreur suppression groupe: " + deleteGroupe.lastError().text().toStdString());
            }

            QSqlDatabase::database().commit();

            QMessageBox::information(this, "Succès",
                                     "Le groupe " + numGroupe + " a été supprimé avec succès !\n"
                                                                "Les étudiants ont été désaffectés du groupe.");


            loadGroupes();
            loadEtudiants();

        } catch (const std::exception& e) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "Erreur",
                                  "La suppression a échoué :\n" + QString::fromStdString(e.what()));
        }
    }
}
//Update groupe
void MainWindow::on_btn_modifier_groupes_clicked()
{
    QModelIndexList selection = ui->table_groupes->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un groupe à modifier.");
        return;
    }

    int row = selection.at(0).row();

    QString numGroupe = ui->table_groupes->model()->index(row, 0).data().toString();
    QString classe = ui->table_groupes->model()->index(row, 1).data().toString();
    QString noteRapport = ui->table_groupes->model()->index(row, 4).data().toString();
    QString noteApplication = ui->table_groupes->model()->index(row, 5).data().toString();

    // recup
    QSqlQuery query;
    query.prepare("SELECT g.ENSEIGNANT_Trilogie_ens, g.THEME_num_theme "
                  "FROM GROUPE g "
                  "WHERE g.num_groupe = :groupe AND g.CLASSE_num_classe = :classe");
    query.bindValue(":groupe", numGroupe);
    query.bindValue(":classe", classe);

    QString encadreurTrilogie = "";
    QString themeId = "";

    if (query.exec() && query.next()) {
        encadreurTrilogie = query.value(0).toString();
        themeId = query.value(1).toString();
    }

    // recup matricule
    QStringList matriculesEtudiants;
    QSqlQuery etudiantsQuery;
    etudiantsQuery.prepare("SELECT Matricule FROM ETUDIANT "
                           "WHERE GROUPE_num_groupe = :groupe "
                           "ORDER BY Matricule");
    etudiantsQuery.bindValue(":groupe", numGroupe);

    if (etudiantsQuery.exec()) {
        while (etudiantsQuery.next()) {
            matriculesEtudiants << etudiantsQuery.value(0).toString();
        }
    }

    modif_groupe *form = new modif_groupe(this);
    form->remplirFormulaire(numGroupe, classe, encadreurTrilogie, themeId,
                            matriculesEtudiants, noteRapport, noteApplication);
    form->setWindowTitle("Modifier un groupe");
    form->exec();

    delete form;

    loadGroupes();
    loadEtudiants();
}

/*void MainWindow::fixStudentClasses()
{
    QSqlQuery query;
    query.prepare("UPDATE ETUDIANT E "
                  "JOIN GROUPE G ON E.GROUPE_num_groupe = G.num_groupe "
                  "SET E.CLASSE_num_classe = G.CLASSE_num_classe "
                  "WHERE E.CLASSE_num_classe IS NULL");

    if(query.exec()) {
        qDebug() << "Student classes updated";
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
}
*/
