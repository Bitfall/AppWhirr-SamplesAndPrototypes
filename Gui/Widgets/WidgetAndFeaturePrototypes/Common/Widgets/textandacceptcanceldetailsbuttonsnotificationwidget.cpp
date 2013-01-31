#include "textandacceptcanceldetailsbuttonsnotificationwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

TextAndAcceptCancelDetailsButtonsNotificationWidget::TextAndAcceptCancelDetailsButtonsNotificationWidget(QString titleText, QString acceptButtonText, QString cancelButtonText, QString detailsButtonText, bool isFinishNotificationWhenDetailsSelected, QWidget *parent) :
    SelfTimeoutingNotificationWidgetBase(parent),
    _isFinishNotificationWhenDetailsSelected(isFinishNotificationWhenDetailsSelected)
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

    QPushButton *detailsButton = new QPushButton;
    detailsButton->setText(detailsButtonText);
    detailsButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(detailsButton, SIGNAL(clicked()), this, SLOT(_detailsButtonClicked()));
    mainLayout->addWidget(detailsButton);
}

void TextAndAcceptCancelDetailsButtonsNotificationWidget::_acceptButtonClicked()
{
    Q_EMIT this->notificationFinished();
    Q_EMIT acceptOptionSelected();
}

void TextAndAcceptCancelDetailsButtonsNotificationWidget::_cancelButtonClicked()
{
    Q_EMIT this->notificationFinished();
    Q_EMIT cancelOptionSelected();
}

void TextAndAcceptCancelDetailsButtonsNotificationWidget::_detailsButtonClicked()
{
    if(this->_isFinishNotificationWhenDetailsSelected) {
        Q_EMIT this->notificationFinished();
    }
    Q_EMIT detailsOptionSelected();
}
