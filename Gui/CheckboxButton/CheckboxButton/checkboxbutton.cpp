#include "checkboxbutton.h"

#include <QLabel>
#include <QCheckBox>
#include <QSpacerItem>
#include <QHBoxLayout>

#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>

#include <QEvent>
#include <QMouseEvent>

// TMP DEBUG
#include <QDebug>

CheckboxButton::CheckboxButton(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    _titleLabel = new QLabel;
    mainLayout->addWidget(_titleLabel);

    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    _checkbox = new QCheckBox;
    mainLayout->addWidget(_checkbox);

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->setObjectName(getDefaultObjectName());
}

void CheckboxButton::paintEvent(QPaintEvent *e)
{
    // must be provided for widgets inherits directly from QWidget if you want to style it with css
    //  check QWidget section here: http://doc.qt.nokia.com/4.7-snapshot/stylesheet-reference.html

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CheckboxButton::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
}

void CheckboxButton::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
}

void CheckboxButton::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void CheckboxButton::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
}

void CheckboxButton::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "mouse relese";
    _checkbox->setChecked(!_checkbox->isChecked());
    QWidget::mouseReleaseEvent(e);
}

void CheckboxButton::setTitleText(QString titleText)
{
    _titleLabel->setText(titleText);
}

void CheckboxButton::setCheckboxChecked(bool isChecked)
{
    _checkbox->setChecked(isChecked);
}
