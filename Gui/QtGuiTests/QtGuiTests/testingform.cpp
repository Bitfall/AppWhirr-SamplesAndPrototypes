#include "testingform.h"
#include "ui_testingform.h"

TestingForm::TestingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestingForm)
{
    ui->setupUi(this);
}

TestingForm::~TestingForm()
{
    delete ui;
}
