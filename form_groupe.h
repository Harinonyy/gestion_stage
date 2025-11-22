#ifndef FORM_GROUPE_H
#define FORM_GROUPE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class form_groupe;
}

class form_groupe : public QDialog
{
    Q_OBJECT

public:
    explicit form_groupe(QWidget *parent = nullptr);
    ~form_groupe();

private slots:

    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::form_groupe *ui;

    void chargerClasses();
    void chargerParcours();
    void chargerThemes(const QString& codeParcours = "");
    void chargerEncadreurs();
    QString calculerNomGroupeSuivant(const QString& numClasse);
};

#endif // FORM_GROUPE_H

