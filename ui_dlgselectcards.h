/********************************************************************************
** Form generated from reading UI file 'dlgselectcards.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSELECTCARDS_H
#define UI_DLGSELECTCARDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgSelectCards
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *listView;

    void setupUi(QDialog *DlgSelectCards)
    {
        if (DlgSelectCards->objectName().isEmpty())
            DlgSelectCards->setObjectName(QStringLiteral("DlgSelectCards"));
        DlgSelectCards->resize(400, 300);
        verticalLayout = new QVBoxLayout(DlgSelectCards);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(DlgSelectCards);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        listView = new QListView(DlgSelectCards);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);


        retranslateUi(DlgSelectCards);

        QMetaObject::connectSlotsByName(DlgSelectCards);
    } // setupUi

    void retranslateUi(QDialog *DlgSelectCards)
    {
        DlgSelectCards->setWindowTitle(QApplication::translate("DlgSelectCards", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DlgSelectCards", "Select cards", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DlgSelectCards: public Ui_DlgSelectCards {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSELECTCARDS_H
