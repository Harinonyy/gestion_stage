#ifndef MODIF_GROUPE_H
#define MODIF_GROUPE_H

#include <QDialog>

namespace Ui {
class modif_groupe;
}

class modif_groupe : public QDialog
{
    Q_OBJECT

public:
    explicit modif_groupe(QWidget *parent = nullptr);
    ~modif_groupe();

    void remplirFormulaire(const QString& nomGroupe, const QString& classe,
                           const QString& encadreur, const QString& theme,
                           const QStringList& matriculesEtudiants,
                           const QString& noteRapport, const QString& noteApplication);

private slots:
    void on_comboBox_7_currentIndexChanged(int index);
    void on_comboBox_9_currentIndexChanged(int index);
    void on_buttonBox_accepted();

    void onEncadreurChanged(int index);
    void chargerThemesParEncadreur(const QString& trilogieEncadreur);

private:
    Ui::modif_groupe *ui;
    QString originalNomGroupe;
    QString originalClasse;
};

#endif // MODIF_GROUPE_H
