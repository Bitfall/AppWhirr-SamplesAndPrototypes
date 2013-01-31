#ifndef SIMPLEIMAGEPRESENTERWIDGET_H
#define SIMPLEIMAGEPRESENTERWIDGET_H

#include <QWidget>
#include <QPixmap>

class SimpleImagePresenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleImagePresenterWidget(QWidget *parent = 0);
    explicit SimpleImagePresenterWidget(QString imagePath, QWidget *parent = 0);

    void setAutoResizeToImageSize(bool isAutoResize);
    void setImageByPath(QString imagePath);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent * event);

signals:
    void clicked();

public slots:

private:
    void resizeToImageSize();
    void commonInit();

private:
    QPixmap imageToPresent;
    bool isAutoResizeToImageSize;
};

#endif // SIMPLEIMAGEPRESENTERWIDGET_H
