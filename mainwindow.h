#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ajb_uart/uart.h"
#include "ajb_net/ajb_socket.h"
#include <QTimer>
#include <qprinter.h>
#include <qprinterinfo.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    AJB_SocketControl userudpsocket;
    uart useruart;
    Queue* serialqueue;
    bool finish;
    bool autostart;
    bool netdeal;
    int id;
    char szinfo[64];
    int readcount;
    QTimer DecodeTimer;
    QTimer autoprintTimer;
    QByteArray  CodeInfo; //打印信息
    QByteArray  LastCodeInfo; //上次打印信息
    QString     TargetFilePath;  //目标文件绝对路径
    QString     DownloadFilePath;  //目标文件绝对路径
    QString     PrintName; //打印机名称
    QString     GwId;
    QString     GatewayMode; // 网关型号
    double      width_fix;
    double      high_fix;
    int         paper_w; //纸张宽度
    int         paper_h; //纸张高度

    int         textSzie;  //打印字体的大小
    int         PaperCount;//打印的纸张数量
signals:


private slots:

    void on_uart_comboBox_currentIndexChanged(int index);

    void on_pushButton_refresh_clicked();

    void on_buard_comboBox_currentIndexChanged(int index);

    void on_pushButton_com_clicked(bool checked);

    void on_pushButton_down_clicked(bool checked);

    void on_pushButton_clear_clicked(bool checked);

    void on_pushButton_path_clicked();

    void AutoPrintTimeout();

    void DecodeTimeout();

    void on_print_comboBox_currentIndexChanged(int index);

    void on_print_pushButton_clicked();

    void on_widgt_doubleSpinBox_valueChanged(double arg1);

    void on_high_doubleSpinBox_2_valueChanged(double arg1);

    void on_auto_pushButton_clicked(bool checked);

    void signal_eventautoprintcode(bool);

    void on_enterprint_pushButton_clicked();

    void on_mode_comboBox_currentIndexChanged(int index);

    void on_paper_comboBox_currentIndexChanged(int index);

    void on_net_radioButton_pressed();

    void on_com_radioButton_pressed();

    void on_PaperCountspinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
