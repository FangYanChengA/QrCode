/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_com;
    QPushButton *pushButton_down;
    QPushButton *pushButton_clear;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_path;
    QTextEdit *textEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_refresh;
    QLabel *label;
    QComboBox *uart_comboBox;
    QComboBox *print_comboBox;
    QPushButton *print_pushButton;
    QLabel *code_label_3;
    QPushButton *auto_pushButton;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QDoubleSpinBox *widgt_doubleSpinBox;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QDoubleSpinBox *high_doubleSpinBox_2;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *net_radioButton;
    QRadioButton *com_radioButton;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QComboBox *buard_comboBox;
    QLabel *label_6;
    QComboBox *paper_comboBox;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *enterprint_lineEdit;
    QLabel *label_5;
    QComboBox *mode_comboBox;
    QPushButton *enterprint_pushButton;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QTextEdit *lan_textEdit;
    QLabel *label_9;
    QTextEdit *wlan_textEdit;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout;
    QLabel *label_10;
    QSpinBox *PaperCountspinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(510, 705);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 240, 451, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_com = new QPushButton(layoutWidget);
        pushButton_com->setObjectName(QStringLiteral("pushButton_com"));
        pushButton_com->setSizeIncrement(QSize(40, 40));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pushButton_com->setFont(font);
        pushButton_com->setAutoRepeatInterval(100);

        horizontalLayout->addWidget(pushButton_com);

        pushButton_down = new QPushButton(layoutWidget);
        pushButton_down->setObjectName(QStringLiteral("pushButton_down"));
        pushButton_down->setFont(font);

        horizontalLayout->addWidget(pushButton_down);

        pushButton_clear = new QPushButton(layoutWidget);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));
        pushButton_clear->setFont(font);

        horizontalLayout->addWidget(pushButton_clear);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 110, 451, 51));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEdit_path = new QLineEdit(layoutWidget1);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));

        horizontalLayout_4->addWidget(lineEdit_path);

        pushButton_path = new QPushButton(layoutWidget1);
        pushButton_path->setObjectName(QStringLiteral("pushButton_path"));
        pushButton_path->setFont(font);

        horizontalLayout_4->addWidget(pushButton_path);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(30, 170, 451, 31));
        textEdit->setReadOnly(true);
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 40, 451, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_refresh = new QPushButton(layoutWidget2);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));

        horizontalLayout_2->addWidget(pushButton_refresh);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        uart_comboBox = new QComboBox(layoutWidget2);
        uart_comboBox->setObjectName(QStringLiteral("uart_comboBox"));

        horizontalLayout_2->addWidget(uart_comboBox);

        print_comboBox = new QComboBox(centralWidget);
        print_comboBox->setObjectName(QStringLiteral("print_comboBox"));
        print_comboBox->setGeometry(QRect(30, 320, 451, 31));
        print_pushButton = new QPushButton(centralWidget);
        print_pushButton->setObjectName(QStringLiteral("print_pushButton"));
        print_pushButton->setGeometry(QRect(380, 530, 101, 71));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setWeight(75);
        print_pushButton->setFont(font1);
        code_label_3 = new QLabel(centralWidget);
        code_label_3->setObjectName(QStringLiteral("code_label_3"));
        code_label_3->setGeometry(QRect(30, 360, 251, 251));
        code_label_3->setAutoFillBackground(false);
        auto_pushButton = new QPushButton(centralWidget);
        auto_pushButton->setObjectName(QStringLiteral("auto_pushButton"));
        auto_pushButton->setGeometry(QRect(380, 431, 101, 70));
        auto_pushButton->setFont(font1);
        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(320, 360, 168, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        widgt_doubleSpinBox = new QDoubleSpinBox(layoutWidget3);
        widgt_doubleSpinBox->setObjectName(QStringLiteral("widgt_doubleSpinBox"));
        widgt_doubleSpinBox->setMinimum(-200);
        widgt_doubleSpinBox->setMaximum(200);
        widgt_doubleSpinBox->setValue(0);

        horizontalLayout_5->addWidget(widgt_doubleSpinBox);

        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(320, 390, 168, 25));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font2;
        font2.setFamily(QStringLiteral("AngsanaUPC"));
        label_4->setFont(font2);

        horizontalLayout_6->addWidget(label_4);

        high_doubleSpinBox_2 = new QDoubleSpinBox(layoutWidget4);
        high_doubleSpinBox_2->setObjectName(QStringLiteral("high_doubleSpinBox_2"));
        high_doubleSpinBox_2->setMinimum(-200);
        high_doubleSpinBox_2->setMaximum(200);
        high_doubleSpinBox_2->setValue(0);

        horizontalLayout_6->addWidget(high_doubleSpinBox_2);

        layoutWidget5 = new QWidget(centralWidget);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(30, 10, 451, 20));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        net_radioButton = new QRadioButton(layoutWidget5);
        net_radioButton->setObjectName(QStringLiteral("net_radioButton"));
        net_radioButton->setChecked(true);

        horizontalLayout_3->addWidget(net_radioButton);

        com_radioButton = new QRadioButton(layoutWidget5);
        com_radioButton->setObjectName(QStringLiteral("com_radioButton"));

        horizontalLayout_3->addWidget(com_radioButton);

        layoutWidget6 = new QWidget(centralWidget);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(31, 80, 451, 24));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget6);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_8->addWidget(label_2);

        buard_comboBox = new QComboBox(layoutWidget6);
        buard_comboBox->setObjectName(QStringLiteral("buard_comboBox"));

        horizontalLayout_8->addWidget(buard_comboBox);

        label_6 = new QLabel(layoutWidget6);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        horizontalLayout_8->addWidget(label_6);

        paper_comboBox = new QComboBox(layoutWidget6);
        paper_comboBox->setObjectName(QStringLiteral("paper_comboBox"));

        horizontalLayout_8->addWidget(paper_comboBox);

        layoutWidget7 = new QWidget(centralWidget);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(30, 621, 451, 25));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget7);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        enterprint_lineEdit = new QLineEdit(layoutWidget7);
        enterprint_lineEdit->setObjectName(QStringLiteral("enterprint_lineEdit"));
        enterprint_lineEdit->setMaxLength(8);

        horizontalLayout_7->addWidget(enterprint_lineEdit);

        label_5 = new QLabel(layoutWidget7);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        mode_comboBox = new QComboBox(layoutWidget7);
        mode_comboBox->setObjectName(QStringLiteral("mode_comboBox"));

        horizontalLayout_7->addWidget(mode_comboBox);

        enterprint_pushButton = new QPushButton(layoutWidget7);
        enterprint_pushButton->setObjectName(QStringLiteral("enterprint_pushButton"));
        enterprint_pushButton->setSizeIncrement(QSize(0, 0));
        enterprint_pushButton->setIconSize(QSize(16, 16));

        horizontalLayout_7->addWidget(enterprint_pushButton);

        layoutWidget8 = new QWidget(centralWidget);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(30, 210, 451, 27));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget8);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        lan_textEdit = new QTextEdit(layoutWidget8);
        lan_textEdit->setObjectName(QStringLiteral("lan_textEdit"));
        lan_textEdit->setMaximumSize(QSize(16777215, 25));
        lan_textEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(lan_textEdit);

        label_9 = new QLabel(layoutWidget8);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        wlan_textEdit = new QTextEdit(layoutWidget8);
        wlan_textEdit->setObjectName(QStringLiteral("wlan_textEdit"));
        wlan_textEdit->setMaximumSize(QSize(16777215, 25));
        wlan_textEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(wlan_textEdit);

        layoutWidget9 = new QWidget(centralWidget);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(330, 480, 42, 70));
        verticalLayout = new QVBoxLayout(layoutWidget9);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget9);
        label_10->setObjectName(QStringLiteral("label_10"));
        QFont font3;
        font3.setFamily(QStringLiteral("Aharoni"));
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        label_10->setFont(font3);

        verticalLayout->addWidget(label_10);

        PaperCountspinBox = new QSpinBox(layoutWidget9);
        PaperCountspinBox->setObjectName(QStringLiteral("PaperCountspinBox"));

        verticalLayout->addWidget(PaperCountspinBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 510, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_com->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", 0));
        pushButton_down->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\344\277\241\346\201\257", 0));
        pushButton_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", 0));
        pushButton_path->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\344\270\213\350\275\275\350\267\257\345\276\204", 0));
        pushButton_refresh->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", 0));
        label->setText(QApplication::translate("MainWindow", "               \344\270\262\345\217\243\357\274\232", 0));
        print_pushButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\215\260", 0));
        code_label_3->setText(QString());
        auto_pushButton->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\n"
"\346\211\223\345\215\260", 0));
        label_3->setText(QApplication::translate("MainWindow", "\346\260\264\345\271\263\345\201\217\347\247\273\344\277\256\346\255\243\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\236\202\347\233\264\345\201\217\347\247\273\344\277\256\346\255\243\357\274\232", 0));
        net_radioButton->setText(QApplication::translate("MainWindow", "\347\275\221\347\273\234\350\277\236\346\216\245            ", 0));
        com_radioButton->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\350\277\236\346\216\245", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", 0));
        buard_comboBox->clear();
        buard_comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "115200", 0)
         << QApplication::translate("MainWindow", "9600", 0)
         << QApplication::translate("MainWindow", "1200", 0)
         << QApplication::translate("MainWindow", "2400", 0)
         << QApplication::translate("MainWindow", "4800", 0)
         << QApplication::translate("MainWindow", "19200", 0)
         << QApplication::translate("MainWindow", "38400", 0)
         << QApplication::translate("MainWindow", "57600", 0)
        );
        label_6->setText(QApplication::translate("MainWindow", "          \346\211\223\345\215\260\347\272\270\345\274\240\357\274\232", 0));
        paper_comboBox->clear();
        paper_comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "20*20", 0)
         << QApplication::translate("MainWindow", "12*12", 0)
        );
        label_7->setText(QApplication::translate("MainWindow", "\347\275\221\345\205\263ID\357\274\232", 0));
        label_5->setText(QApplication::translate("MainWindow", "    \345\236\213\345\217\267\357\274\232", 0));
        mode_comboBox->clear();
        mode_comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "AJB-G6", 0)
         << QApplication::translate("MainWindow", "AJB-G5", 0)
         << QApplication::translate("MainWindow", "AJB-G4", 0)
        );
        enterprint_pushButton->setText(QApplication::translate("MainWindow", "\346\211\213\345\212\250\350\276\223\345\205\245\346\211\223\345\215\260", 0));
        label_8->setText(QApplication::translate("MainWindow", "\346\234\211\347\272\277\347\275\221MAC\345\234\260\345\235\200\357\274\232", 0));
        label_9->setText(QApplication::translate("MainWindow", "\346\227\240\347\272\277\347\275\221MAC\345\234\260\345\235\200\357\274\232", 0));
        label_10->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\211\223\n"
"\345\215\260\345\274\240\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
