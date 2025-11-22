#ifndef MODIF_THEME_H
#define MODIF_THEME_H

#include <QDialog>

namespace Ui {
class modif_theme;
}

class modif_theme : public QDialog
{
    Q_OBJECT

public:
    explicit modif_theme(QWidget *parent = nullptr);
    ~modif_theme();

    void remplirFormulaire(int num_theme, const QString &libelle, const QString &description,
                           const QString &enseignant_trilogie, const QString &parcours_code);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modif_theme *ui;
    int originalNumTheme;
};

#endif // MODIF_THEME_H
