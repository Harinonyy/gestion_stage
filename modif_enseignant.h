#ifndef MODIF_ENSEIGNANT_H
#define MODIF_ENSEIGNANT_H

#include <QDialog>

namespace Ui {
class modif_enseignant;
}

class modif_enseignant : public QDialog
{
    Q_OBJECT

public:
    explicit modif_enseignant(QWidget *parent = nullptr);
    ~modif_enseignant();

    // pre remplir form
    void remplirFormulaire(const QString &trilogie, const QString &nom,
                           const QString &prenom, const QString &telephone,
                           const QString &email);

private slots:

    void on_buttonBox_accepted();

private:
    Ui::modif_enseignant *ui;
    QString originalTrilogie;
};

#endif // MODIF_ENSEIGNANT_H
