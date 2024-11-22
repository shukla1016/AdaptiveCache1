/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *keyInput;
    QPushButton *searchButton;
    QPushButton *insertButton;
    QPushButton *deleteButton;
    QPushButton *displayCacheButton;
    QPushButton *exitButton;
    QLabel *resultLabel;
    QLabel *logTextEdit;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        keyInput = new QLineEdit(MainWindow);
        keyInput->setObjectName(QString::fromUtf8("keyInput"));

        verticalLayout->addWidget(keyInput);

        searchButton = new QPushButton(MainWindow);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        verticalLayout->addWidget(searchButton);

        insertButton = new QPushButton(MainWindow);
        insertButton->setObjectName(QString::fromUtf8("insertButton"));

        verticalLayout->addWidget(insertButton);

        deleteButton = new QPushButton(MainWindow);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        verticalLayout->addWidget(deleteButton);

        displayCacheButton = new QPushButton(MainWindow);
        displayCacheButton->setObjectName(QString::fromUtf8("displayCacheButton"));

        verticalLayout->addWidget(displayCacheButton);

        exitButton = new QPushButton(MainWindow);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        verticalLayout->addWidget(exitButton);

        resultLabel = new QLabel(MainWindow);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));

        verticalLayout->addWidget(resultLabel);

        logTextEdit = new QLabel(MainWindow);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));

        verticalLayout->addWidget(logTextEdit);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Adaptive Cache UI", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        insertButton->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        displayCacheButton->setText(QCoreApplication::translate("MainWindow", "Display Cache", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "Results will appear here", nullptr));
        logTextEdit->setText(QCoreApplication::translate("MainWindow", "Logs will appear here", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
