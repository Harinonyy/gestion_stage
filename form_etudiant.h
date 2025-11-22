#ifndef FORM_ETUDIANT_H
#define FORM_ETUDIANT_H

#include <QDialog>
#include "connexionbd.h"
#include <QSqlDatabase>


namespace Ui {
class form_etudiant;
}

class form_etudiant : public QDialog
{
    Q_OBJECT

public:
    explicit form_etudiant(QWidget *parent = nullptr);
    ~form_etudiant();


    void remplirFormulaire(const QString &matricule, const QString &nom, const QString &prenom,
                           const QString &telephone, const QString &mail, const QString &classe, QString groupe);

    void mettreAJourEtudiant(const QString &ancienMatricule);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::form_etudiant *ui;
    QSqlDatabase db;
    QString originalMatricule;
    bool isEditMode = false;

};
#endif // FORM_ETUDIANT_H
