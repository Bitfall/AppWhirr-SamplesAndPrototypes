#ifndef WEBIMAGE_H
#define WEBIMAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QString;
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;
class QBuffer;
class QBytes;
class QPaintEvent;
class QPixmap;
QT_END_NAMESPACE

class WebImage : public QWidget
{
    Q_OBJECT
public:
    explicit WebImage(const QString& url, QWidget *parent = 0);
    ~WebImage();

    QSize sizeHint() const;

signals:

protected slots:
    void didFinishRequest(int requestID, bool error);
    void paintEvent(QPaintEvent* event);
private:
    QNetworkAccessManager*              networkManager;
    int                                 request;
    QBuffer*                            buffer;
    QByteArray                          bytes;
    QPixmap                              image;
};

#endif // WEBIMAGE_H
