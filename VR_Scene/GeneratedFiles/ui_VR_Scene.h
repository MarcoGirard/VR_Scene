/********************************************************************************
** Form generated from reading UI file 'VR_Scene.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VR_SCENE_H
#define UI_VR_SCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VR_SceneClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VR_SceneClass)
    {
        if (VR_SceneClass->objectName().isEmpty())
            VR_SceneClass->setObjectName(QStringLiteral("VR_SceneClass"));
        VR_SceneClass->resize(600, 400);
        menuBar = new QMenuBar(VR_SceneClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        VR_SceneClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VR_SceneClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VR_SceneClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(VR_SceneClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        VR_SceneClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VR_SceneClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VR_SceneClass->setStatusBar(statusBar);

        retranslateUi(VR_SceneClass);

        QMetaObject::connectSlotsByName(VR_SceneClass);
    } // setupUi

    void retranslateUi(QMainWindow *VR_SceneClass)
    {
        VR_SceneClass->setWindowTitle(QApplication::translate("VR_SceneClass", "VR_Scene", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VR_SceneClass: public Ui_VR_SceneClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VR_SCENE_H
