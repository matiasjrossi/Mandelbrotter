#include "progressdialog.h"
#include "ui_progressdialog.h"
#include <QCloseEvent>

ProgressDialog::ProgressDialog(QString title, QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    ui->label->setText(text);
    setWindowTitle(title);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ProgressDialog::closeEvent(QCloseEvent *e)
{
    e->ignore();
}
