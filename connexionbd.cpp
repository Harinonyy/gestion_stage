 #include "connexionbd.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
connexionBd::connexionBd() {}

#include "connexionbd.h"

QSqlDatabase& connexionBd::connectBase() {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    static bool configured = false;


    if (configured && db.isOpen()) {
        return db;
    }


    if (!configured) {
        db.setHostName("localhost");
        db.setDatabaseName("gestion_stage");
        db.setUserName("root");
        db.setPassword("");
        db.setPort(3307);
        configured = true;
    }


    if (db.open()) {
        qDebug() << " Connexion réussie à la base de données !";
    } else {
        QString errorMsg = " Erreur de connexion MySQL:\n" + db.lastError().text();
        qDebug() << errorMsg;
        QMessageBox::critical(nullptr, "Erreur Base de Données", errorMsg);
    }

    return db;
}

