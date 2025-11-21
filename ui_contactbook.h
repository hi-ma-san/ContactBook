/********************************************************************************
** Form generated from reading UI file 'contactbook.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTBOOK_H
#define UI_CONTACTBOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ContactBook
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableW;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *insertButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *importButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *exportButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *exitButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *ContactBook)
    {
        if (ContactBook->objectName().isEmpty())
            ContactBook->setObjectName("ContactBook");
        ContactBook->resize(800, 600);
        verticalLayout = new QVBoxLayout(ContactBook);
        verticalLayout->setObjectName("verticalLayout");
        tableW = new QTableWidget(ContactBook);
        tableW->setObjectName("tableW");

        verticalLayout->addWidget(tableW);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(ContactBook);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        label_3 = new QLabel(ContactBook);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        lineEdit_2 = new QLineEdit(ContactBook);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_2);

        lineEdit_3 = new QLineEdit(ContactBook);
        lineEdit_3->setObjectName("lineEdit_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEdit_3);

        lineEdit_4 = new QLineEdit(ContactBook);
        lineEdit_4->setObjectName("lineEdit_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_4);

        label_4 = new QLabel(ContactBook);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        label = new QLabel(ContactBook);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lineEdit = new QLineEdit(ContactBook);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        insertButton = new QPushButton(ContactBook);
        insertButton->setObjectName("insertButton");

        horizontalLayout_2->addWidget(insertButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        importButton = new QPushButton(ContactBook);
        importButton->setObjectName("importButton");

        horizontalLayout_2->addWidget(importButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        exportButton = new QPushButton(ContactBook);
        exportButton->setObjectName("exportButton");

        horizontalLayout_2->addWidget(exportButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        exitButton = new QPushButton(ContactBook);
        exitButton->setObjectName("exitButton");

        horizontalLayout_2->addWidget(exitButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ContactBook);

        QMetaObject::connectSlotsByName(ContactBook);
    } // setupUi

    void retranslateUi(QDialog *ContactBook)
    {
        ContactBook->setWindowTitle(QCoreApplication::translate("ContactBook", "ContactBook", nullptr));
        label_2->setText(QCoreApplication::translate("ContactBook", "\347\217\255\347\264\232\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("ContactBook", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("ContactBook", "\351\233\273\350\251\261\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("ContactBook", "\345\255\270\350\231\237\357\274\232", nullptr));
        insertButton->setText(QCoreApplication::translate("ContactBook", "\346\226\260\345\242\236", nullptr));
        importButton->setText(QCoreApplication::translate("ContactBook", "\345\214\257\345\205\245", nullptr));
        exportButton->setText(QCoreApplication::translate("ContactBook", "\345\214\257\345\207\272", nullptr));
        exitButton->setText(QCoreApplication::translate("ContactBook", "\347\265\220\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContactBook: public Ui_ContactBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTBOOK_H
