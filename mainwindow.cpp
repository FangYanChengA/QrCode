#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cstring"
#include <QTime>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QPixmapCache>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QEvent>
#include <QSettings>
#include "ajb_qrcode/code.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialqueue = new Queue(1024*1024);
    finish = true;
    autostart = false;
    netdeal = true;
    paper_w = 200;
    paper_h = 200;
    textSzie = 6;
    memset(szinfo,0,64);
    CodeInfo.append("null");
    //初始化手动输入的网关类型
    GatewayMode = "AJB-G6";
    //初始化打印纸张的数量
    PaperCount = 1;
    ui->PaperCountspinBox->setValue(PaperCount);

    //获取电脑上打印机的名称
    QList<QPrinterInfo> list = QPrinterInfo::availablePrinters();
    ui->print_comboBox->clear();
    for (int i = 0 ;i<list.size();i++)
    {
//        qDebug() << "打印机" << i <<  list.at(i).printerName();//乱码;
        qDebug() <<"打印机" << i << list.at(i).printerName().toStdString().c_str(); //正确输出中文
        ui->print_comboBox->addItem( list.at(i).printerName() );
    }

    QString relativepath = QDir::currentPath();  //得到相对路径Release
    qDebug() <<"当前路径 " << relativepath;
    QDir dir(relativepath);
    if (!dir.exists("code"))
    {
        dir.mkdir(QString::fromLocal8Bit("code"));
    }
    //在显示二维码的label上画上底图
    QImage image(250, 250, QImage::Format_Mono);
    image.fill(255);
    image.save("./code/empty.png");
    ui->code_label_3->setScaledContents(true);
    ui->code_label_3->setVisible(true);
    ui->code_label_3->setPixmap(QPixmap("./code/empty.png"));

    connect(this, SIGNAL(signal_eventautoprintcode(bool)), this, SLOT(signal_eventautoprintcode(bool)));
    connect(&autoprintTimer, SIGNAL(timeout()), this, SLOT(AutoPrintTimeout()));
    connect(&DecodeTimer, SIGNAL(timeout()), this, SLOT(DecodeTimeout()));
    DecodeTimer.start(500);

    QFileInfo fi("./init.ini");
    if(fi.exists())
    {
        QSettings settingsread("./init.ini",QSettings::IniFormat);
        width_fix = settingsread.value("fixlocation/width").toDouble();
        ui->widgt_doubleSpinBox->setValue(width_fix);
        high_fix = settingsread.value("fixlocation/high").toDouble();
        ui->high_doubleSpinBox_2->setValue(high_fix);
    }
    else
    {
        QFile inifile("./init.ini");
        inifile.open( QIODevice::ReadWrite | QIODevice::Text );
        inifile.close();
        QSettings settings("./init.ini",QSettings::IniFormat);
        settings.beginGroup("fixlocation");
        settings.setValue("high",0);
        settings.setValue("width",0);
        width_fix = 0;
        high_fix = 0;
    }
}

MainWindow::~MainWindow()
{
    delete serialqueue;
    delete ui;
}
//选择并设置串口
void MainWindow::on_uart_comboBox_currentIndexChanged(int index)
{
    if(index<0)
    {
        return;
    }
    // 填充text
    useruart.serial_name =  ui->uart_comboBox->currentText();
    qDebug() <<"串口 -- " << useruart.serial_name;
}

//刷新按钮，获取串口列表，设置选择串口和波特率
void MainWindow::on_pushButton_refresh_clicked()
{
    QVector<QString>::iterator iter;
    useruart.Uart_FindAllUart();
    ui->uart_comboBox->clear();
    for(iter=useruart.namelist.begin();iter!=useruart.namelist.end();iter++)
    {
        if(iter != NULL)
            ui->uart_comboBox->addItem( *iter );
    }
    useruart.serial_name =  ui->uart_comboBox->currentText();
    useruart.buard = ui->buard_comboBox->currentText();
    qDebug() <<"当前选择的串口 -- " << useruart.serial_name;
    qDebug() <<"当前选择的波特率 -- " << useruart.buard;
}
//设置波特率
void MainWindow::on_buard_comboBox_currentIndexChanged(int index)
{
    if(index<0)
    {
        return;
    }
    useruart.buard =  ui->buard_comboBox->currentText();
    qDebug() <<"波特率 -- " << useruart.buard;
}
//点击连接，连接选中的串口
void MainWindow::on_pushButton_com_clicked(bool checked)
{
    if(netdeal == false)
    {
        if(useruart.Uart_Connect())
        {
            ui->pushButton_com->setText("断开");
        }
        else if(useruart.Uart_Disconnect())
        {
            ui->pushButton_com->setText("连接");
        }
    }
}
//获取二维码信息
void MainWindow::on_pushButton_down_clicked(bool checked)
{
    if(netdeal == false)
    {
        if(useruart.connect == false || !finish)
            return ;
        long long res = 0;
        // Init
        finish = false;
        readcount = 0;
        //emit signal_eventrecv_update(true);
        res = useruart.serial.write("/home/info.sh\r\n");
        qDebug() << "send: " << res;
    }
    else  // 网络发送
    {
        userudpsocket.udpBroadRquest();
    }
}
//清空按钮
void MainWindow::on_pushButton_clear_clicked(bool checked)
{
    ui->textEdit->clear();
    ui->lan_textEdit->clear();
    ui->wlan_textEdit->clear();
    //qApp->processEvents();
    //QPixmap::clear();
    ui->code_label_3->setPixmap(QPixmap("./code/empty.png"));
}
//设置保存二维码
void MainWindow::on_pushButton_path_clicked()
{
    DownloadFilePath.clear();
    DownloadFilePath = QFileDialog::getExistingDirectory( this, "请选择下载路径","./"  );
    ui->lineEdit_path->clear();
    ui->lineEdit_path->setText( DownloadFilePath );
    ui->code_label_3->setPixmap(QPixmap("./code/empty.png"));
    qDebug() <<"下载路径：" << DownloadFilePath;
}
//自动打印槽函数，5秒钟执行一次
void MainWindow::AutoPrintTimeout()
{
    if(netdeal == false)
    {
        if(useruart.connect == false || !finish)
            return ;
        long long res = 0;
        // Init
        finish = false;
        readcount = 0;
        res = useruart.serial.write("reset\n/home/info.sh\n");
        qDebug() << "send: " << res;
    }
    else  // 网络发送
    {
        userudpsocket.udpBroadRquest();
    }
}

void MainWindow::DecodeTimeout()
{
    if(netdeal == false)
    {
        unsigned int readlen;
        if(useruart.connect == false || finish == true)
        {
            if(useruart.connect != false)
            {
                readlen = useruart.Uart_Received(serialqueue);
                serialqueue->DelectDataFromQueue(serialqueue->GetQueueDataSize());
            }
            return ;
        }
        char szcodeinfo[1024*50] = {0};
        //char szinfo[64] = {0};
        //char szmd[64] = {0};
        //char *readpos = szcodeinfo;
        //char *codeendpos = NULL;
        //int codelength = 0;
        //int md5length = 0;
        //QByteArray getmd;
        //QByteArray calmd;
        readlen = useruart.Uart_Received(serialqueue);
        //qDebug() << "recieve" << readlen;
        if( readlen > 0) // 解析
        {
            if( serialqueue->GetQueueDataSize() >= 70)
            {
                unsigned int getsize = serialqueue->ReadDataFromQueue(0,szcodeinfo,1024 * 50);
                qDebug() << szcodeinfo;

                if(useruart.Uart_ParseInfo(szcodeinfo,getsize))
                {
                    ui->textEdit->clear();
                    ui->textEdit->append(useruart.uart_qrinfo);
                    ui->lan_textEdit->clear();
                    ui->lan_textEdit->append(useruart.uart_ethmac);
                    ui->wlan_textEdit->clear();
                    ui->wlan_textEdit->append(useruart.uart_wlanmac);
                    //  szinfo解析新的信息
                    CodeInfo.clear();
                    CodeInfo.append(useruart.uart_qrinfo);
                    GwId=useruart.uart_gwid;
                    if(CodeInfo != LastCodeInfo || autostart == false)
                    {
                        AJB_QRCode qrcode(CodeInfo);
                        qrcode.setMargin(10);
                        QImage image(250, 250, QImage::Format_Mono);

                        TargetFilePath.clear();
                        TargetFilePath.append("./code/");
                        TargetFilePath += GwId;
                        TargetFilePath.append(".png");

                        qDebug() << "GwId:" << GwId;

                        qrcode.painterdraw(&image,TargetFilePath,GwId);

                        if(DownloadFilePath.size() > 0)
                        {
                            QString GetDownload;
                            GetDownload = DownloadFilePath;
                            QFile codefile(TargetFilePath);
                            GetDownload.append("/");
                            GetDownload += GwId;
                            GetDownload.append(".png");
                            codefile.copy(GetDownload);
                            qDebug() << "TargetFilePath: " << TargetFilePath << "DownloadFilePath: " <<DownloadFilePath;
                        }
                        if(TargetFilePath.size() > 13)
                        {
                            ui->code_label_3->setPixmap(QPixmap(TargetFilePath));
                        }
                        if(autostart)
                            emit signal_eventautoprintcode(true);// 发送信号
                    }
                    else
                    {
                        ui->code_label_3->setPixmap(QPixmap(TargetFilePath));
                    }

                    serialqueue->DelectDataFromQueue(serialqueue->GetQueueDataSize());
                    finish = true;
                    return ;
                }
                else
                {
                    serialqueue->DelectDataFromQueue(serialqueue->GetQueueDataSize());
                    readcount++;
                    if(readcount >= 5)
                        finish = true;
                }

#if 0
                while(readpos[0] != '\0' && readpos-szcodeinfo < 1024*50 -2)
                {
                    if(readpos[0] == '*' && readpos[1] == '#')
                    {
                        readpos += 2;
                        codeendpos = readpos;
                        while(codeendpos[0] != '*' && codeendpos[1] != '#')
                        {
                            codeendpos++;
                            if(codeendpos[0] == '\0')
                                break;
                        }
                        if(codeendpos[0] != '\0')
                        {
                            codelength = codeendpos - readpos;
                            memcpy(szinfo,readpos,codelength);
                            codeendpos+=4;
                            if(codeendpos[0] == '\0')
                            {
                                return ;
                            }
                            readpos = codeendpos;
                            while(codeendpos[0] != '*' && codeendpos[1] != '#')
                            {
                                codeendpos++;
                                if(codeendpos[0] == '\0')
                                    break;
                            }
                            if(codeendpos[0] != '\0')
                            {
                                md5length = codeendpos - readpos;
                                memcpy(szmd,readpos,md5length);
                                getmd.append(szmd);
                                QCryptographicHash hash(QCryptographicHash::Md5);
                                hash.addData(szinfo,strlen(szinfo));
                                calmd = hash.result();
                                calmd = calmd.toHex();
                                if(calmd == getmd)
                                {
                                    ui->textEdit->clear();
                                    ui->textEdit->append(szinfo);
                                    //  szinfo解析新的信息
                                    CodeInfo.clear();
                                    CodeInfo.append(szinfo);
                                    GwId=CodeInfo.mid(11,8);
                                    if(CodeInfo != LastCodeInfo || autostart == false)
                                    {
                                        AJB_QRCode qrcode(CodeInfo);
                                        qrcode.setMargin(50);
                                        QImage image(250, 250, QImage::Format_Mono);

                                        TargetFilePath.clear();
                                        TargetFilePath.append("./code/");
                                        TargetFilePath += GwId;
                                        TargetFilePath.append(".png");
                                        qrcode.painterdraw(&image,TargetFilePath,GwId);
                                        if(DownloadFilePath.size() > 0)
                                        {
                                            QString GetDownload;
                                            GetDownload = DownloadFilePath;
                                            QFile codefile(TargetFilePath);
                                            GetDownload.append("/");
                                            GetDownload += GwId;
                                            GetDownload.append(".png");
                                            codefile.copy(GetDownload);
                                            qDebug() << "TargetFilePath: " << TargetFilePath << "DownloadFilePath: " <<DownloadFilePath;
                                        }
                                        if(TargetFilePath.size() > 13)
                                        {
                                            ui->code_label_3->setPixmap(QPixmap(TargetFilePath));
                                        }
                                        if(autostart)
                                            emit signal_eventautoprintcode(true);// 发送信号
                                    }
                                    else
                                    {
                                        ui->code_label_3->setPixmap(QPixmap(TargetFilePath));
                                    }
                                }
                                serialqueue->DelectDataFromQueue(serialqueue->GetQueueDataSize());
                                finish = true;
                                return ;
                            }
                        }
                    }
                    else
                    {
                        readpos += 1;
                    }
                }




                serialqueue->DelectDataFromQueue(serialqueue->GetQueueDataSize());
                readcount++;
                if(readcount >= 5)
                    finish = true;
#endif

            }
        }
        else
        {
            readcount++;
            if(readcount >= 5)
                finish = true;
        }
    }
    else  // 网络解析部分
    {
        if(userudpsocket.udpGetReady() == UDP_GETDATA)
        {
            char szinfo[64] = {0};
            char szmd[64] = {0};
            char szethmac[64] = {0};
            char szwlanmac[64] = {0};
            //QByteArray getmd;
            //QByteArray calmd;

            strcpy(szinfo,userudpsocket.qrcodeInfo.toLatin1().data());
            strcpy(szmd,userudpsocket.crcInfo.toLatin1().data());
            strcpy(szethmac,userudpsocket.ethmac.toLatin1().data());
            strcpy(szwlanmac,userudpsocket.wlanmac.toLatin1().data());
            //getmd.append(szmd);
            //QCryptographicHash hash(QCryptographicHash::Md5);
            //hash.addData(szinfo,strlen(szinfo));
            //calmd = hash.result();
            //calmd = calmd.toHex();
            //if(calmd == getmd)
            {
                ui->textEdit->clear();
                ui->textEdit->append(szinfo);
                ui->lan_textEdit->clear();
                ui->lan_textEdit->append(szethmac);
                ui->wlan_textEdit->clear();
                ui->wlan_textEdit->append(szwlanmac);
                CodeInfo.clear();
                CodeInfo.append(szinfo);
                int begin = CodeInfo.indexOf("%");
                int second = CodeInfo.indexOf("%",begin+1);
                GwId=CodeInfo.mid(second+1,8);
                if(CodeInfo != LastCodeInfo || autostart == false)
                {
                    AJB_QRCode qrcode(CodeInfo);
                    qrcode.setMargin(10);
                    QImage image(250, 250, QImage::Format_Mono);

                    TargetFilePath.clear();
                    TargetFilePath.append("./code/");
                    TargetFilePath += GwId;
                    TargetFilePath.append(".png");
                    qrcode.painterdraw(&image,TargetFilePath,GwId);
                    if(DownloadFilePath.size() > 0)
                    {
                        QString GetDownload;
                        GetDownload = DownloadFilePath;
                        QFile codefile(TargetFilePath);
                        GetDownload.append("/");
                        GetDownload += GwId;
                        GetDownload.append(".png");
                        codefile.copy(GetDownload);
                        qDebug() << "TargetFilePath: " << TargetFilePath << "DownloadFilePath: " <<DownloadFilePath;
                    }
                    if(TargetFilePath.size() > 13)
                    {
                        ui->code_label_3->setPixmap(QPixmap(TargetFilePath));
                    }
                    if(autostart)
                        emit signal_eventautoprintcode(true);// 发送信号
                }
                else
                {
                    ui->code_label_3->setPixmap(QPixmap(TargetFilePath));
                }
            }
            userudpsocket.udpBackToWait();
        }
    }
}

//选择并设置打印机
void MainWindow::on_print_comboBox_currentIndexChanged(int index)
{
    if(index<0)
    {
        return;
    }
    PrintName = ui->print_comboBox->currentText();
    qDebug() << "PrintName： " << PrintName << __FUNCTION__ << __LINE__;;
}

//手动点击 打印 按钮
void MainWindow::on_print_pushButton_clicked()
{
#if 1
    for(int i = 1 ; i <= PaperCount ; i++ ){
        //实例化打印机
        QPrinter printer;
        QImage QrCode_Image;
        //AJB_QrCode qr;
 #if 0
        qreal left, top, right, bottom;
        qDebug() << QString("设置前").toStdString().c_str();
        qDebug() << printer.printerName() << __FILE__ << __LINE__;
        qDebug() << printer.supportedPaperSources() << __FILE__ << __LINE__;
        qDebug() << printer.supportedResolutions() << __FILE__ << __LINE__;
        qDebug() << printer.orientation() << __FILE__ << __LINE__;
        qDebug() << printer.fullPage() << __FILE__ << __LINE__;
        qDebug() << printer.paperName() << __FILE__ << __LINE__;
        qDebug() << printer.paperSize() << __FILE__ << __LINE__; //0/A4
        qDebug() << printer.paperRect() << __FILE__ << __LINE__;
        qDebug() << printer.pageRect() << __FILE__ << __LINE__;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::Millimeter);
        qDebug() << left << top << right << bottom << __FILE__ << __LINE__;
#endif

        //设置打印机名称,setPageSizeMM 这个函数和 setPaperSize 和这个函数设置纸张大小的效果一样的，只不过前者固定了纸张的单位，后者需要设置纸张的单位
        printer.setPrinterName( PrintName );
//        printer.setPageSizeMM(QSizeF(300,300)); //大小
//        printer.setPaperSize(QSizeF(paper_w,paper_h), QPrinter::Millimeter);
        if( 200  == paper_w && 200 == paper_h )
            printer.setPaperSize(QSizeF(20,20), QPrinter::Millimeter);
        else if(120  == paper_w && 120 == paper_h )
            printer.setPaperSize(QSizeF(12,12), QPrinter::Millimeter);

        printer.setPageMargins(0,0,0,0, QPrinter::Millimeter);
        printer.setOrientation(QPrinter::Portrait);
        printer.setResolution(300);//分辨率 203

 #if 0
        qDebug() << QString("设置后").toStdString().c_str();
        qDebug() << printer.printerName() << __FILE__ << __LINE__;
        qDebug() << printer.supportedPaperSources() << __FILE__ << __LINE__;
        qDebug() << printer.supportedResolutions() << __FILE__ << __LINE__;
        qDebug() << printer.orientation() << __FILE__ << __LINE__;
        qDebug() << printer.fullPage() << __FILE__ << __LINE__;
        qDebug() << printer.paperName() << __FILE__ << __LINE__;
        qDebug() << printer.paperSize() << __FILE__ << __LINE__; //0/A4
        qDebug() << printer.paperRect() << __FILE__ << __LINE__;
        qDebug() << printer.pageRect() << __FILE__ << __LINE__;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::Millimeter);
        qDebug() << left << top << right << bottom << __FILE__ << __LINE__;
#endif
        QPainter painter( &printer );
        AJB_QRCode qrcode(CodeInfo);
        //qrcode.setMargin(30);
        qrcode.paintQR( &painter,QSize(paper_w,paper_w),GwId,width_fix,high_fix,textSzie );
        qDebug() << "clicked Manual PaperCount " << PaperCount << "i " << i;
        painter.end();
     }

#else
    qDebug() << "print: " << CodeInfo ;
#endif
}
//水平偏移修正
void MainWindow::on_widgt_doubleSpinBox_valueChanged(double arg1)
{
    width_fix = arg1;
    QSettings settings("./init.ini",QSettings::IniFormat);
    settings.beginGroup("fixlocation");
    settings.setValue("width",arg1);
    qDebug()<< "w:" << arg1;
}
//垂直偏移修正
void MainWindow::on_high_doubleSpinBox_2_valueChanged(double arg1)
{
    high_fix = arg1;
    QSettings settings("./init.ini",QSettings::IniFormat);
    settings.beginGroup("fixlocation");
    settings.setValue("high",arg1);
    qDebug()<< "h:" << arg1;
}

void MainWindow::signal_eventautoprintcode(bool doit)
{
    if(LastCodeInfo != CodeInfo && doit)
    {
#if 1
    for(int i = 1 ; i <= PaperCount ; i++ ){
        QPrinter printer;
        QImage QrCode_Image;
        printer.setPrinterName( PrintName );
        printer.setPageSizeMM(QSizeF(300,300)); //大小
        if( 200  == paper_w && 200 == paper_h )
            printer.setPaperSize(QSizeF(20,20), QPrinter::Millimeter);
        else if(120  == paper_w && 120 == paper_h )
            printer.setPaperSize(QSizeF(12,12), QPrinter::Millimeter);
        printer.setPageMargins(0,0,0,0, QPrinter::Millimeter);
        printer.setOrientation(QPrinter::Portrait);
        printer.setResolution(300);//分辨率 203
        QPainter painter( &printer );
        AJB_QRCode qrcode(CodeInfo);
        //qrcode.setMargin(30);
        // qrcode.paintQR( &painter,QSize(200,200),GwId,width_fix,high_fix );
        // qrcode.paintQR( &painter,QSize(paper_w*10,paper_h*10),GwId,width_fix,high_fix );
        qrcode.paintQR( &painter,QSize(paper_w,paper_w),GwId,width_fix,high_fix,textSzie );
        qDebug() << "auto PaperCount " << PaperCount << "i " << i;
        painter.end();
    }

#else
        qDebug() << "print: " << CodeInfo << "has print:" << LastCodeInfo;
#endif
        LastCodeInfo = CodeInfo;
    }
}
// 自动打印 按钮
void MainWindow::on_auto_pushButton_clicked(bool checked)
{
    if(netdeal == false && useruart.connect == false)
        return ;
    if(autostart)
    {
        ui->auto_pushButton->setText("自动\n打印");
        autostart = false;
        //emit signal_eventautoprint(false);// 发送信号
        autoprintTimer.stop();
    }
    else
    {
        ui->auto_pushButton->setText("停止\n打印");
        autostart = true;
        autoprintTimer.start(5000);
        //emit signal_eventautoprint(true);// 发送信号
    }
}
//手动输入打印
void MainWindow::on_enterprint_pushButton_clicked()
{

   for(int i = 1 ; i <= PaperCount ; i++ ){
    QString EnterPrint;
    QPrinter printer;
    QImage QrCode_Image;
    QString devtype;
    printer.setPrinterName( PrintName );
//    printer.setPageSizeMM(QSizeF(250,250)); //大小
    if( 200  == paper_w && 200 == paper_h )
        printer.setPaperSize(QSizeF(20,20), QPrinter::Millimeter);
    else if(120  == paper_w && 120 == paper_h )
        printer.setPaperSize(QSizeF(12,12), QPrinter::Millimeter);
    printer.setPageMargins(0,0,0,0, QPrinter::Millimeter);
    printer.setOrientation(QPrinter::Portrait);
    printer.setResolution(300);//分辨率 203

    QPainter painter( &printer );
    QByteArray  _CodeInfo;

    EnterPrint = ui->enterprint_lineEdit->text();
    EnterPrint = EnterPrint.toUpper();

    if(GatewayMode == "AJB-G6")
    {
         devtype = "66";
    }
    else if(GatewayMode == "AJB-G4")
    {
         devtype = "35";
    }
    else if(GatewayMode == "AJB-G5")
    {
         devtype = "75";
    }
    else
    {
     return;
    }
    QDate CurrentDate = QDate::currentDate();
//    QString DateStr = CurrentDate.toString();
//    qDebug() << "date:" <<CurrentDate.year() << CurrentDate.month() << CurrentDate.day();
//    qDebug() << "date:" <<DateStr.toStdString().c_str();
    //QString("%1-%2-%3")
    QString dateTime = QString("%1%2%3")
                            .arg(CurrentDate.year())
                            .arg(CurrentDate.month(), 2, 10, QChar('0'))  // 表示2个字宽，10进制，未满字宽用'0'填补
                            .arg(CurrentDate.day(), 2, 10, QChar('0'));
     qDebug() << "dateTime:" <<dateTime.toStdString().c_str();

    _CodeInfo.clear();
    _CodeInfo.append("AnjuBao");
    _CodeInfo.append("%");
    _CodeInfo.append(devtype);
    _CodeInfo.append("%");
    _CodeInfo.append(EnterPrint);
    _CodeInfo.append("%");
    _CodeInfo.append(GatewayMode);
    _CodeInfo.append("%");
    _CodeInfo.append(dateTime);
//    _CodeInfo.append("20210408");

    AJB_QRCode qrcode(_CodeInfo);

    qDebug() << "GatewayMode:" <<GatewayMode;
    qDebug() << "CodeInfo:" <<_CodeInfo.toStdString().c_str();

    qDebug() <<"i" << i << "GatewayMode:" << GatewayMode << "CodeInfo:" <<_CodeInfo.toStdString().c_str();
    qrcode.paintQR( &painter,QSize(paper_w,paper_w),EnterPrint,width_fix,high_fix ,textSzie);
    painter.end();
   }
}
//选择并设置网关型号
void MainWindow::on_mode_comboBox_currentIndexChanged(int index)
{
    if(index<0)
    {
        return;
    }
    GatewayMode =  ui->mode_comboBox->currentText();
}
//选择并设置打印纸张的尺寸大小
void MainWindow::on_paper_comboBox_currentIndexChanged(int index)
{
    if(index<0)
    {
        return;
    }
    QString GetPaper =  ui->paper_comboBox->currentText();
    if(GetPaper == "20*20")
    {
        paper_w = 200;
        paper_h = 200;
        textSzie = 6;
    }
    else if(GetPaper == "12*12")
    {
        paper_w = 120;
        paper_h = 120;
        textSzie = 5;
    }
    qDebug() << "paper_w:" << paper_w << "paper_h:" << paper_h << "textSzie:" << textSzie;
}
//选择网络连接
void MainWindow::on_net_radioButton_pressed()
{
    if(netdeal == false && autostart == true)
    {
        ui->auto_pushButton->setText("自动\n打印");
        autostart = false;
        autoprintTimer.stop();
        finish = true;
        useruart.Uart_Disconnect();
        ui->pushButton_com->setText("连接");
        netdeal = true;
    }
    else if(netdeal == false)
    {
        finish = true;
        useruart.Uart_Disconnect();
        ui->pushButton_com->setText("连接");
        netdeal = true;
    }
    qDebug() << "netdeal" << netdeal;
}
//选择串口连接
void MainWindow::on_com_radioButton_pressed()
{
    if(netdeal == true && autostart == true)
    {
        ui->auto_pushButton->setText("自动\n打印");
        autostart = false;
        autoprintTimer.stop();
        netdeal = false;
    }
    else if(netdeal == true)
    {
        netdeal = false;
    }
    qDebug() << "netdeal:" << netdeal;
}
//设置一次打印的数量
void MainWindow::on_PaperCountspinBox_valueChanged(int arg1)
{
    PaperCount = arg1;
    qDebug() << "PaperCount" << PaperCount ;
}
