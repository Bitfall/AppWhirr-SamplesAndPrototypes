#ifndef TESTINGFORM_H
#define TESTINGFORM_H

#include <QWidget>

namespace Ui {
    class TestingForm;
}

class TestingForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestingForm(QWidget *parent = 0);
    ~TestingForm();

private:
    Ui::TestingForm *ui;
};

#endif // TESTINGFORM_H
