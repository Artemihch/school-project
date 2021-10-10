#include "qr_creator.h"
#include "ui_qr_creator.h"
#include "qrcodegen.hpp"
#include <QPainter>

using namespace qrcodegen;

void paintQR(QPainter &painter, const QSize sz, const QString &data)
{
    // NOTE: At this point you will use the API to get the encoding and format you want, instead of my hardcoded stuff:
    QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::HIGH);
    const int s=qr.getSize()>0?qr.getSize():1;
    const double w=sz.width();
    const double h=sz.height();
    const double aspect=w/h;
    const double size=((aspect>1.0)?h:w);
    const double scale=size/(s+2);
    // NOTE: For performance reasons my implementation only draws the foreground parts in supplied color.
    // It expects background to be prepared already (in white or whatever is preferred).

    painter.setPen(Qt::NoPen);
    // Setting the background color....
    painter.setBrush(QColor("White"));
    for(int y=0; y<400; y++) {
        for(int x=0; x<400; x++) {
            QRectF r(x, y, 1, 1);
            painter.drawRects(&r,1);
        }
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("Black"));
    for(int y=0; y<s; y++) {
        for(int x=0; x<s; x++) {
            const int color=qr.getModule(x, y);  // 0 for white, 1 for black
            if(0x0!=color) {
                const double rx1=(x+1)*scale, ry1=(y+1)*scale;
                QRectF r(rx1, ry1, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }
}

QR_creator::QR_creator(QWidget *parent, QString secret_key)
    : QMainWindow(parent)
    , ui(new Ui::QR_creator)
{
    ui->setupUi(this);
    QPixmap map(400,400);
    QPainter painter(&map);
    //"otpauth://totp/" + НАЗВАНИЕ + "?secret=" + парольчик
    //paintQR(painter,QSize(400,400),"otpauth://totp/SCHOOL?secret=JBSWY3DPEHPK3PXP");
    paintQR(painter,QSize(400,400),"otpauth://totp/PasswordManager?secret=" + secret_key);
    ui->QR->setPixmap(map);
    ui->secret_code->setText(secret_key);
}

QR_creator::~QR_creator()
{
    delete ui;
}

