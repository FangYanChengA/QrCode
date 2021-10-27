#include "code.h"
#include <QPixmapCache>
#include <QDateTime>
#include <QDebug>
AJB_QRCode::AJB_QRCode(const QByteArray &text,QWidget *parent)
{
    if (text.length () == 0)
    {
        qrtext = QByteArray("http://github.com/chinat");
    }
    else
    {
        qrtext = text;
    }
    qrmargin = 10;
    foreground = QColor("black");
    background = QColor("white");
    casesen = true;
    mode = MODE_8;
    level = LEVEL_L;//LEVEL_Q;
    percent = 0.23;
    qrscale = 0.09;//0.09;
}

void AJB_QRCode::setMargin(const int &margin)
{
    qrmargin = margin;
}

void AJB_QRCode::caseSensitive(bool flag)
{
    casesen = flag;
}

void AJB_QRCode::paintQR(QPainter *painter, const QSize& sz, QString &mytext, double widthfix, double highfix, int textSize )
{
     qDebug() << "qrtext.data:" << qrtext.data ();
     qDebug() << "mytext:" << mytext;
    QRcode *qrcode = QRcode_encodeString(qrtext.data (), 3, (QRecLevel)level, (QRencodeMode)mode, casesen ? 1 : 0);
    if(0 != qrcode) {
        unsigned char *point = qrcode->data;
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->background);
        double tempwidth = sz.width();
        double tempheight = sz.height();
        painter->drawRect(0, 0, tempwidth, tempheight);
        double size = (tempwidth/tempheight > 1.0 )?tempheight:tempwidth;
        double maxsize = (tempwidth/tempheight > 1.0 )?tempwidth:tempheight;
        bool widthislong = (tempwidth > tempheight)?true:false;
        const double tempmargin = qrscale*size; //0.09*200=18  边距?
        double scale = (size - 3.0 * tempmargin) / qrcode->width; // (200-3.0*18)/45  比例
        double pointx,pointy;
        painter->setBrush(this->foreground);
        qDebug() << " qrcode->width: " <<  qrcode->width << "scale: " << scale;
        qDebug() << " tempwidth: " <<  tempwidth << "tempheight: " << tempheight;
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    if(widthislong)
                    {
                        pointx = tempmargin + x * scale+widthfix+(maxsize-size)/2;
                        pointy = tempmargin/2 + y * scale-highfix;
                    }
                    else
                    {
                        pointx = tempmargin + x * scale+widthfix;
                        pointy = tempmargin/2 + y * scale-highfix+(maxsize-size)/2;
                    }
                    QRectF r(pointx,pointy, scale, scale);//x,y,w,h
                    painter->drawRects(&r, 1);
                   // qDebug() << "(" <<  pointx<<","<< pointy <<")";
                }
                point ++;
            }
        }

        QFont font("Arial",textSize,QFont::Bold,false);//6
        font.setCapitalization(QFont::AllUppercase);      //设置字母大小写
        //font.setStretch(12);
#if 1
        painter->setFont(font);
        painter->setPen( QColor( 0, 0, 0 ) );
        if(widthislong)
            painter->drawText( widthfix+(maxsize-size)/2,
                              (tempmargin)+(size - 3*tempmargin)-highfix,
                              (size ),
                              2*tempmargin,
                              Qt::AlignCenter,
                              mytext);
        else
            painter->drawText(widthfix,(tempmargin)+(size - 3*tempmargin)-highfix+(maxsize-size)/2,(size),2*tempmargin,Qt::AlignCenter,mytext);

#endif
        point = NULL;

        QRcode_free(qrcode);
    }
}

void AJB_QRCode::painterdraw(QImage *image,QString &filestring,QString &mytext)
{
#if 0
    QPainter painter(image);
    QFont font("Arial",15,QFont::Normal,false);
    font.setCapitalization(QFont::AllUppercase);      //设置字母大小写

    painter.setFont(font);
    painter.setPen( QColor( 0, 0, 0 ) );

    qDebug() << "mytest:" <<mytext;

    painter.drawText(0,
                     0,
                     image->width(),
                     image->height(),
                     Qt::AlignCenter,
                     "123456");
    if(filestring.size() > 0)
    {
        image->save(filestring);
    }
#else
    QRcode *qrcode = QRcode_encodeString(qrtext.data (), 3, (QRecLevel)level, (QRencodeMode)mode, casesen ? 1 : 0);
    QPainter painter(image);
    if(0 != qrcode) {
        unsigned char *point = qrcode->data;
        painter.setPen(Qt::NoPen);
        painter.setBrush(background);
        painter.drawRect(0, 0, image->width(), image->height());
        qrmargin = qrscale*image->width();
        double scale = (image->width () - 2.0 * qrmargin) / qrcode->width;
        painter.setBrush(foreground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(qrmargin + x * scale, qrmargin + y * scale-qrmargin/2, scale, scale);
                    painter.drawRects(&r, 1);
                }
                point ++;
            }
        }

        QFont font("Arial",15,QFont::Normal,false);
        font.setCapitalization(QFont::AllUppercase);      //设置字母大小写

        painter.setFont(font);
        painter.setPen( QColor( 0, 0, 0 ) );

        qDebug() << "mytest:" <<mytext;

        painter.drawText(0,
                         qrmargin/1.5+qrcode->width*scale,
                         image->width(),
                         qrmargin+20,
                         Qt::AlignCenter,
                         mytext);

        point = NULL;

        QRcode_free(qrcode);

    }
    qrcode = NULL;
    if(filestring.size() > 0)
    {
        image->save(filestring);
    }
#endif
}

void AJB_QRCode::simpleArrayQR(QString &gwid,QString &devtype,QString &devmode)
{
    qrtext.clear();
    qrtext.append("AnjuBao%");
    qrtext.append(devtype);
    qrtext.append("%");
    qrtext.append(gwid);
    qrtext.append("%");
    qrtext.append(devmode);
    qrtext.append("%");

    QDateTime CurDate;
    CurDate= QDateTime::currentDateTime();
    QString SetDate = CurDate.toString("yyyyMMdd");
    qrtext.append(SetDate);
}
