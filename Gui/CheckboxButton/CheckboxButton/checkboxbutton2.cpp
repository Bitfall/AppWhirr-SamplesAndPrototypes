#include "checkboxbutton2.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLayout>

CheckboxButton2::CheckboxButton2(QWidget *parent) :
    QPushButton(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    QCheckBox *checkbox = new QCheckBox;
    mainLayout->addWidget(checkbox);
}
