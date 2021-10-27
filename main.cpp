#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0 //不起作用，后面再研究
   //设置中文字体
   a.setFont(QFont("Microsoft Yahei", 9));
   //设置中文编码
   #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
   #if _MSC_VER
       QTextCodec *codec = QTextCodec::codecForName("GBK");
   #else
       QTextCodec *codec = QTextCodec::codecForName("UTF-8");
   #endif
       QTextCodec::setCodecForLocale(codec);
       QTextCodec::setCodecForCStrings(codec);
       QTextCodec::setCodecForTr(codec);
   #else
       QTextCodec *codec = QTextCodec::codecForName("UTF-8");
       QTextCodec::setCodecForLocale(codec);
   #endif
#endif

       MainWindow w;
       w.show();

    return a.exec();
}
