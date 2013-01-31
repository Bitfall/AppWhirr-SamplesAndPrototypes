#include "webimage.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QPixmap>
#include <QHttp>
#include <QUrl>
#include <QBuffer>
#include <QByteArray>
#include <QPaintEvent>
#include <QPainter>

WebImage::WebImage(const QString& url, QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(40, 40);

    QHttp* http = new QHttp(this);
    connect(http, SIGNAL(requestFinished(int, bool)),this, SLOT(didFinishRequest(int, bool)));

    QBuffer* buffer = new QBuffer(&bytes, this);
    buffer->open(QIODevice::WriteOnly);

    http->setHost(QUrl(url).host());
    request = http->get (url, buffer);
}

WebImage::~WebImage() {
}

QSize WebImage::sizeHint() const {
    QSize ret(40, 40);
    return ret;
}

void WebImage::didFinishRequest(int requestID, bool error) {
    if (request == requestID){
        QImage img;
        img.loadFromData(bytes);

        image = QPixmap::fromImage(img);

        this->update();
    }
}

void WebImage::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    painter.drawPixmap(this->rect(), image, image.rect());
}
