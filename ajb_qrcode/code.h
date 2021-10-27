#ifndef CODE_H
#define CODE_H

#include <QWidget>
#include <QIcon>
#include <QPainter>
#include <QByteArray>
#include "qrencode/qrencode.h"

class AJB_QRCode:public QWidget {
    Q_OBJECT
public:
    enum QR_MODE {
        MODE_NUL = QR_MODE_NUL,
        MODE_NUM = QR_MODE_NUM,
        MODE_AN = QR_MODE_AN,
        MODE_8 = QR_MODE_8,
        MODE_KANJI = QR_MODE_KANJI,
        MODE_STRUCTURE = QR_MODE_STRUCTURE,
        MODE_ECI = QR_MODE_ECI,
        MODE_FNC1FIRST = QR_MODE_FNC1FIRST,
        MODE_FNC1SECOND = QR_MODE_FNC1SECOND
    };
    
    enum QR_LEVEL {
        LEVEL_L = QR_ECLEVEL_L,
        LEVEL_M = QR_ECLEVEL_M,
        LEVEL_Q = QR_ECLEVEL_Q,
        LEVEL_H = QR_ECLEVEL_H
    };

    AJB_QRCode(const QByteArray &text,QWidget *parent = 0);
    
    void setMargin(const int &margin);
    
    void caseSensitive(bool flag);
 
    void paintQR(QPainter *painter, const QSize& sz, QString &mytext, double widthfix, double highfix, int textSize );

    void painterdraw(QImage *printer,QString &filestring,QString &mytext);
    
    void simpleArrayQR(QString &gwid,QString &devtype,QString &devmode);
private:
    bool casesen;
    int qrmargin;
    qreal percent;
    QByteArray qrtext;
    QColor foreground;
    QColor background;
    QR_MODE mode;
    QR_LEVEL level;
    double qrscale;

};
#endif // CODE_H
