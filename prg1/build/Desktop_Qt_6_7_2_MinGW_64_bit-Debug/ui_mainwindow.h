/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainwindow.hh"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_5;
    QSplitter *splitter;
    QWidget *layoutWidget_splitter;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_maze;
    QHBoxLayout *horizontalLayout_2_4;
    CustomGraphicsView *graphics_view_maze;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QCheckBox *maze_toggle;
    QCheckBox *contours_checkbox;
    QCheckBox *bites_checkbox;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *zoom_plus;
    QToolButton *zoom_minus;
    QHBoxLayout *horizontalLayout_41;
    QToolButton *zoom_1;
    QToolButton *zoom_fit;
    QLabel *label_9;
    QLCDNumber *pathlength;
    QPlainTextEdit *output;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_0;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_4;
    QLabel *cmd_info_text;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_12_1;
    QLabel *label;
    QComboBox *cmd_select;
    QLabel *label_2;
    QComboBox *number_select;
    QPushButton *file_button;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *stop_button;
    QPushButton *execute_button;
    QPushButton *clear_input_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1202, 898);
        QFont font;
        font.setPointSize(14);
        MainWindow->setFont(font);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");

        horizontalLayout_11->addLayout(verticalLayout_5);


        verticalLayout->addLayout(horizontalLayout_11);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        layoutWidget_splitter = new QWidget(splitter);
        layoutWidget_splitter->setObjectName("layoutWidget_splitter");
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_splitter);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_maze = new QVBoxLayout();
        verticalLayout_maze->setSpacing(6);
        verticalLayout_maze->setObjectName("verticalLayout_maze");
        horizontalLayout_2_4 = new QHBoxLayout();
        horizontalLayout_2_4->setSpacing(6);
        horizontalLayout_2_4->setObjectName("horizontalLayout_2_4");

        verticalLayout_maze->addLayout(horizontalLayout_2_4);


        horizontalLayout_2->addLayout(verticalLayout_maze);

        graphics_view_maze = new CustomGraphicsView(layoutWidget_splitter);
        graphics_view_maze->setObjectName("graphics_view_maze");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphics_view_maze->sizePolicy().hasHeightForWidth());
        graphics_view_maze->setSizePolicy(sizePolicy);
        graphics_view_maze->setInteractive(false);
        graphics_view_maze->setDragMode(QGraphicsView::ScrollHandDrag);

        horizontalLayout_2->addWidget(graphics_view_maze);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        maze_toggle = new QCheckBox(layoutWidget_splitter);
        maze_toggle->setObjectName("maze_toggle");

        verticalLayout_2->addWidget(maze_toggle);

        contours_checkbox = new QCheckBox(layoutWidget_splitter);
        contours_checkbox->setObjectName("contours_checkbox");
        contours_checkbox->setEnabled(true);
        contours_checkbox->setChecked(true);

        verticalLayout_2->addWidget(contours_checkbox);

        bites_checkbox = new QCheckBox(layoutWidget_splitter);
        bites_checkbox->setObjectName("bites_checkbox");
        bites_checkbox->setChecked(true);

        verticalLayout_2->addWidget(bites_checkbox);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");

        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        zoom_plus = new QToolButton(layoutWidget_splitter);
        zoom_plus->setObjectName("zoom_plus");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(zoom_plus->sizePolicy().hasHeightForWidth());
        zoom_plus->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(zoom_plus);

        zoom_minus = new QToolButton(layoutWidget_splitter);
        zoom_minus->setObjectName("zoom_minus");
        sizePolicy1.setHeightForWidth(zoom_minus->sizePolicy().hasHeightForWidth());
        zoom_minus->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(zoom_minus);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName("horizontalLayout_41");
        zoom_1 = new QToolButton(layoutWidget_splitter);
        zoom_1->setObjectName("zoom_1");
        sizePolicy1.setHeightForWidth(zoom_1->sizePolicy().hasHeightForWidth());
        zoom_1->setSizePolicy(sizePolicy1);

        horizontalLayout_41->addWidget(zoom_1);

        zoom_fit = new QToolButton(layoutWidget_splitter);
        zoom_fit->setObjectName("zoom_fit");
        sizePolicy1.setHeightForWidth(zoom_fit->sizePolicy().hasHeightForWidth());
        zoom_fit->setSizePolicy(sizePolicy1);

        horizontalLayout_41->addWidget(zoom_fit);


        verticalLayout_2->addLayout(horizontalLayout_41);

        label_9 = new QLabel(layoutWidget_splitter);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_9);

        pathlength = new QLCDNumber(layoutWidget_splitter);
        pathlength->setObjectName("pathlength");
        pathlength->setSmallDecimalPoint(true);
        pathlength->setDigitCount(7);
        pathlength->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout_2->addWidget(pathlength);


        horizontalLayout_2->addLayout(verticalLayout_2);

        splitter->addWidget(layoutWidget_splitter);
        output = new QPlainTextEdit(splitter);
        output->setObjectName("output");
        output->setUndoRedoEnabled(false);
        output->setLineWrapMode(QPlainTextEdit::NoWrap);
        splitter->addWidget(output);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_0 = new QVBoxLayout(layoutWidget);
        verticalLayout_0->setSpacing(6);
        verticalLayout_0->setContentsMargins(11, 11, 11, 11);
        verticalLayout_0->setObjectName("verticalLayout_0");
        verticalLayout_0->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        cmd_info_text = new QLabel(layoutWidget);
        cmd_info_text->setObjectName("cmd_info_text");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cmd_info_text->sizePolicy().hasHeightForWidth());
        cmd_info_text->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(cmd_info_text);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_4->addWidget(lineEdit);

        horizontalLayout_12_1 = new QHBoxLayout();
        horizontalLayout_12_1->setSpacing(6);
        horizontalLayout_12_1->setObjectName("horizontalLayout_12_1");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12_1->addWidget(label);

        cmd_select = new QComboBox(layoutWidget);
        cmd_select->setObjectName("cmd_select");

        horizontalLayout_12_1->addWidget(cmd_select);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12_1->addWidget(label_2);

        number_select = new QComboBox(layoutWidget);
        number_select->setObjectName("number_select");

        horizontalLayout_12_1->addWidget(number_select);

        file_button = new QPushButton(layoutWidget);
        file_button->setObjectName("file_button");

        horizontalLayout_12_1->addWidget(file_button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12_1->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_12_1);


        horizontalLayout_12->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        stop_button = new QPushButton(layoutWidget);
        stop_button->setObjectName("stop_button");
        stop_button->setEnabled(false);

        verticalLayout_3->addWidget(stop_button);

        execute_button = new QPushButton(layoutWidget);
        execute_button->setObjectName("execute_button");

        verticalLayout_3->addWidget(execute_button);

        clear_input_button = new QPushButton(layoutWidget);
        clear_input_button->setObjectName("clear_input_button");

        verticalLayout_3->addWidget(clear_input_button);


        horizontalLayout_12->addLayout(verticalLayout_3);


        verticalLayout_0->addLayout(horizontalLayout_12);

        splitter->addWidget(layoutWidget);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        maze_toggle->setText(QCoreApplication::translate("MainWindow", "Maze", nullptr));
        contours_checkbox->setText(QCoreApplication::translate("MainWindow", "Contours", nullptr));
        bites_checkbox->setText(QCoreApplication::translate("MainWindow", "Bites", nullptr));
        zoom_plus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        zoom_minus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        zoom_1->setText(QCoreApplication::translate("MainWindow", "1:1", nullptr));
        zoom_fit->setText(QCoreApplication::translate("MainWindow", "Fit", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Path Distance:", nullptr));
        cmd_info_text->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Command:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number:", nullptr));
        file_button->setText(QCoreApplication::translate("MainWindow", "File...", nullptr));
        stop_button->setText(QCoreApplication::translate("MainWindow", "Stop test", nullptr));
        execute_button->setText(QCoreApplication::translate("MainWindow", "execute", nullptr));
        clear_input_button->setText(QCoreApplication::translate("MainWindow", "Clear input", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
