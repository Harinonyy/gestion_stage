/********************************************************************************
** Form generated from reading UI file 'modif_groupe.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIF_GROUPE_H
#define UI_MODIF_GROUPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_modif_groupe
{
public:
    QWidget *widget;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_14;
    QComboBox *comboBox_7;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_15;
    QLineEdit *lineEdit_13;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_16;
    QComboBox *comboBox_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_17;
    QComboBox *comboBox_9;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_18;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_19;
    QLineEdit *lineEdit_19;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_20;
    QLineEdit *lineEdit_20;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_9;
    QDialogButtonBox *buttonBox_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;

    void setupUi(QDialog *modif_groupe)
    {
        if (modif_groupe->objectName().isEmpty())
            modif_groupe->setObjectName("modif_groupe");
        modif_groupe->resize(665, 744);
        widget = new QWidget(modif_groupe);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 20, 621, 711));
        frame_8 = new QFrame(widget);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(20, 120, 571, 501));
        frame_8->setStyleSheet(QString::fromUtf8("QLabel{\n"
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
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_8);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_14 = new QLabel(frame_8);
        label_14->setObjectName("label_14");

        horizontalLayout_11->addWidget(label_14);

        comboBox_7 = new QComboBox(frame_8);
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName("comboBox_7");

        horizontalLayout_11->addWidget(comboBox_7);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_12->setContentsMargins(-1, -1, 0, -1);
        label_15 = new QLabel(frame_8);
        label_15->setObjectName("label_15");

        horizontalLayout_12->addWidget(label_15);

        lineEdit_13 = new QLineEdit(frame_8);
        lineEdit_13->setObjectName("lineEdit_13");

        horizontalLayout_12->addWidget(lineEdit_13);


        verticalLayout_8->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_16 = new QLabel(frame_8);
        label_16->setObjectName("label_16");

        horizontalLayout_13->addWidget(label_16);

        comboBox_8 = new QComboBox(frame_8);
        comboBox_8->setObjectName("comboBox_8");

        horizontalLayout_13->addWidget(comboBox_8);


        verticalLayout_8->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        label_17 = new QLabel(frame_8);
        label_17->setObjectName("label_17");

        horizontalLayout_14->addWidget(label_17);

        comboBox_9 = new QComboBox(frame_8);
        comboBox_9->setObjectName("comboBox_9");

        horizontalLayout_14->addWidget(comboBox_9);


        verticalLayout_8->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_18 = new QLabel(frame_8);
        label_18->setObjectName("label_18");

        horizontalLayout_15->addWidget(label_18);

        lineEdit_14 = new QLineEdit(frame_8);
        lineEdit_14->setObjectName("lineEdit_14");

        horizontalLayout_15->addWidget(lineEdit_14);

        lineEdit_15 = new QLineEdit(frame_8);
        lineEdit_15->setObjectName("lineEdit_15");

        horizontalLayout_15->addWidget(lineEdit_15);

        lineEdit_16 = new QLineEdit(frame_8);
        lineEdit_16->setObjectName("lineEdit_16");

        horizontalLayout_15->addWidget(lineEdit_16);

        lineEdit_17 = new QLineEdit(frame_8);
        lineEdit_17->setObjectName("lineEdit_17");

        horizontalLayout_15->addWidget(lineEdit_17);

        lineEdit_18 = new QLineEdit(frame_8);
        lineEdit_18->setObjectName("lineEdit_18");

        horizontalLayout_15->addWidget(lineEdit_18);


        verticalLayout_8->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label_19 = new QLabel(frame_8);
        label_19->setObjectName("label_19");

        horizontalLayout_16->addWidget(label_19);

        lineEdit_19 = new QLineEdit(frame_8);
        lineEdit_19->setObjectName("lineEdit_19");

        horizontalLayout_16->addWidget(lineEdit_19);


        verticalLayout_8->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        label_20 = new QLabel(frame_8);
        label_20->setObjectName("label_20");

        horizontalLayout_17->addWidget(label_20);

        lineEdit_20 = new QLineEdit(frame_8);
        lineEdit_20->setObjectName("lineEdit_20");

        horizontalLayout_17->addWidget(lineEdit_20);


        verticalLayout_8->addLayout(horizontalLayout_17);

        frame_9 = new QFrame(widget);
        frame_9->setObjectName("frame_9");
        frame_9->setGeometry(QRect(410, 630, 191, 53));
        frame_9->setStyleSheet(QString::fromUtf8("QDialogButtonBox{\n"
"background-color: #28a745; \n"
"color: white;\n"
" border-radius: 8px;\n"
" font-weight: bold;\n"
" padding: 5px 15px;\n"
"}"));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_9);
        verticalLayout_9->setObjectName("verticalLayout_9");
        buttonBox_3 = new QDialogButtonBox(frame_9);
        buttonBox_3->setObjectName("buttonBox_3");
        buttonBox_3->setOrientation(Qt::Orientation::Horizontal);
        buttonBox_3->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_9->addWidget(buttonBox_3);

        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 10, 551, 91));
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


        retranslateUi(modif_groupe);

        QMetaObject::connectSlotsByName(modif_groupe);
    } // setupUi

    void retranslateUi(QDialog *modif_groupe)
    {
        modif_groupe->setWindowTitle(QCoreApplication::translate("modif_groupe", "Dialog", nullptr));
        label_14->setText(QCoreApplication::translate("modif_groupe", " Classe :", nullptr));
        comboBox_7->setItemText(0, QCoreApplication::translate("modif_groupe", "L1", nullptr));
        comboBox_7->setItemText(1, QCoreApplication::translate("modif_groupe", "M1", nullptr));

        label_15->setText(QCoreApplication::translate("modif_groupe", " Nom Groupe :                                    ", nullptr));
        label_16->setText(QCoreApplication::translate("modif_groupe", "Encadreur :", nullptr));
        label_17->setText(QCoreApplication::translate("modif_groupe", "Theme attribu\303\251 :", nullptr));
        label_18->setText(QCoreApplication::translate("modif_groupe", "Etudiants membres :", nullptr));
        label_19->setText(QCoreApplication::translate("modif_groupe", "Note Rapport :                                  ", nullptr));
        label_20->setText(QCoreApplication::translate("modif_groupe", "Note Application :                           ", nullptr));
        label->setText(QCoreApplication::translate("modif_groupe", "            Informations du groupe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class modif_groupe: public Ui_modif_groupe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIF_GROUPE_H
