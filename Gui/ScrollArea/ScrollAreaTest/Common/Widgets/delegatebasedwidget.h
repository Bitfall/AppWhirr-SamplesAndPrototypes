#ifndef DELEGATEBASEDWIDGET_H
#define DELEGATEBASEDWIDGET_H

#include <QWidget>

class DelegateBasedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DelegateBasedWidget(QWidget *parent = 0);

Q_SIGNALS:
    void resizeHappened(QResizeEvent *e);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *e);
};

#endif // DELEGATEBASEDWIDGET_H
