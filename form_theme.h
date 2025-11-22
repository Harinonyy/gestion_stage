#ifndef FORM_THEME_H
#define FORM_THEME_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class form_theme;
}

class form_theme : public QDialog
{
    Q_OBJECT

public:
    explicit form_theme(QWidget *parent = nullptr);
    ~form_theme();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void genererNumeroTheme();

private:
    Ui::form_theme *ui;
    QSqlDatabase db;
};

#endif // FORM_THEME_H
