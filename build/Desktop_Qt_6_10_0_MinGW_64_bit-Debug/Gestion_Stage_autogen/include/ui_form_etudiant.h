/********************************************************************************
** Form generated from reading UI file 'form_etudiant.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ETUDIANT_H
#define UI_FORM_ETUDIANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_form_etudiant
{
public:
    QVBoxLayout *verticalLayout_4;
    QWidget *widget;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *form_etudiant)
    {
        if (form_etudiant->objectName().isEmpty())
            form_etudiant->setObjectName("form_etudiant");
        form_etudiant->resize(635, 698);
        form_etudiant->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(form_etudiant);
        verticalLayout_4->setObjectName("verticalLayout_4");
        widget = new QWidget(form_etudiant);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QDWidget {\n"
"    /* Bleu tr\303\250s clair pour le fond de la fen\303\252tre */\n"
"    background-color: #E6F7FF; \n"
"    border-radius: 12px; \n"
"}"));
        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, -50, 551, 141));
        frame->setStyleSheet(QString::fromUtf8("QLabel#label {\n"
"    /* Couleur du texte, coh\303\251rente avec votre interface */\n"
"    color: #004D99; \n"
"    /* Taille de police beaucoup plus grande */\n"
"    font-size: 24px; \n"
"    /* Police en gras */\n"
"    font-weight: bold;\n"
"    /* Marge interne pour l'espacement */\n"
"    padding: 20px 0 10px 20px;\n"
"}"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(label);

        frame_2 = new QFrame(widget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(40, 70, 521, 511));
        frame_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:#333333;\n"
"QLabel	font-size:14px;\n"
"font: 700 9pt \"Segoe UI\";\n"
"}\n"
"QLineEdit, QComboBox {\n"
"    /* Hauteur standard pour le champ */\n"
"    min-height: 30px; \n"
"    /* Arri\303\250re-plan */\n"
"    background-color: white; \n"
"    /* Bordure fine */\n"
"    border: 1px solid #CCCCCC;\n"
"    /* Coins l\303\251g\303\250rement arrondis */\n"
"    border-radius: 8px; \n"
"    /* Espace interne pour le texte */\n"
"    padding: 0 10px; \n"
"}\n"
"\n"
"/* Style au survol ou \303\240 la s\303\251lection pour un feedback visuel */\n"
"QLineEdit:focus, QComboBox:focus {\n"
"    border: 2px solid #007BFF; /* Bordure bleue plus \303\251paisse */\n"
"}\n"
"QFrame {\n"
"    /* Blanc cass\303\251 pour le conteneur des champs */\n"
"    background-color: #FAFAFA; \n"
"    border-radius: 10px; /* Optionnel : pour les bords internes */\n"
"    /* Ajouter un peu d'ombre pour le faire ressortir (un peu plus complexe, mais tr\303\250s bel effet) */\n"
"    /* box-shadow: 2px 2px 5px rgba(0, 0,"
                        " 0, 0.1); */\n"
"}"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(frame_2);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        lineEdit_2 = new QLineEdit(frame_2);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        lineEdit_3 = new QLineEdit(frame_2);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout_3->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        lineEdit_4 = new QLineEdit(frame_2);
        lineEdit_4->setObjectName("lineEdit_4");

        horizontalLayout_4->addWidget(lineEdit_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        lineEdit_5 = new QLineEdit(frame_2);
        lineEdit_5->setObjectName("lineEdit_5");

        horizontalLayout_5->addWidget(lineEdit_5);


        verticalLayout->addLayout(horizontalLayout_5);

        frame_3 = new QFrame(widget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(360, 600, 191, 53));
        frame_3->setStyleSheet(QString::fromUtf8("QDialogButtonBox{\n"
"background-color: #28a745; \n"
"color: white;\n"
" border-radius: 8px;\n"
" font-weight: bold;\n"
" padding: 5px 15px;\n"
"}"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        buttonBox = new QDialogButtonBox(frame_3);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_3->addWidget(buttonBox);


        verticalLayout_4->addWidget(widget);


        retranslateUi(form_etudiant);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, form_etudiant, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, form_etudiant, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(form_etudiant);
    } // setupUi

    void retranslateUi(QDialog *form_etudiant)
    {
        form_etudiant->setWindowTitle(QCoreApplication::translate("form_etudiant", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("form_etudiant", "Formulaire d'ajout d'un nouveau etudiant", nullptr));
        label_2->setText(QCoreApplication::translate("form_etudiant", "Matricule :", nullptr));
        label_3->setText(QCoreApplication::translate("form_etudiant", "Nom :", nullptr));
        label_4->setText(QCoreApplication::translate("form_etudiant", "Prenom(s) :", nullptr));
        label_5->setText(QCoreApplication::translate("form_etudiant", "Email :", nullptr));
        label_6->setText(QCoreApplication::translate("form_etudiant", "Telephone :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class form_etudiant: public Ui_form_etudiant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ETUDIANT_H
