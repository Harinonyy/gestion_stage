#ifndef MODIF_ETUDIANT_H
#define MODIF_ETUDIANT_H

#include <QDialog>
#include <QString>

namespace Ui {
class modif_etudiant;
}

class modif_etudiant : public QDialog
{
    Q_OBJECT

public:
    explicit modif_etudiant(QWidget *parent = nullptr);
    ~modif_etudiant();

    void remplirFormulaire(const QString &matricule, const QString &nom, const QString &prenom,
                           const QString &telephone, const QString &mail, const QString &classe, QString groupe);

signals:
    void etudiantModifie(); // actualisation apres modif

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::modif_etudiant *ui;
    QString originalMatricule;
};

#endif // MODIF_ETUDIANT_H
