#ifndef TEXTANDACCEPTCANCELBUTTONSNOTIFICATIONWIDGET_H
#define TEXTANDACCEPTCANCELBUTTONSNOTIFICATIONWIDGET_H

#include "Browser/Notification/selftimeoutingnotificationwidgetbase.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TextAndAcceptCancelButtonsNotificationWidget : public SelfTimeoutingNotificationWidgetBase
{
    Q_OBJECT
public:
    explicit TextAndAcceptCancelButtonsNotificationWidget(QString titleText, QString acceptButtonText, QString cancelButtonText, QWidget *parent = 0);

Q_SIGNALS:
    void acceptOptionSelected();
    void cancelOptionSelected();

private Q_SLOTS:
    void _acceptButtonClicked();
    void _cancelButtonClicked();

};

#endif // TEXTANDACCEPTCANCELBUTTONSNOTIFICATIONWIDGET_H
