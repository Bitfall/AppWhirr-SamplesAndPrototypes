#include "textandacceptcancelbuttonsnotificationwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

TextAndAcceptCancelButtonsNotificationWidget::TextAndAcceptCancelButtonsNotificationWidget(QString titleText, QString acceptButtonText, QString cancelButtonText, QWidget *parent) :
    SelfTimeoutingNotificationWidgetBase(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *titleLabel = new QLabel;
    titleLabel->setText(titleText);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(titleLabel);

    // some spacing
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QPushButton *acceptButton = new QPushButton;
    acceptButton->setText(acceptButtonText);
    acceptButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(_acceptButtonClicked()));
    mainLayout->addWidget(acceptButton);

    QPushButton *cancelButton = new QPushButton;
    cancelButton->setText(cancelButtonText);
    cancelButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(_cancelButtonClicked()));
    mainLayout->addWidget(cancelButton);
}

void TextAndAcceptCancelButtonsNotificationWidget::_acceptButtonClicked()
{
    Q_EMIT this->notificationFinished();
    Q_EMIT acceptOptionSelected();
}

void TextAndAcceptCancelButtonsNotificationWidget::_cancelButtonClicked()
{
    Q_EMIT this->notificationFinished();
    Q_EMIT cancelOptionSelected();
}
