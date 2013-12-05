#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class ProgressDialog;
}

class ProgressDialog : public QDialog {
    Q_OBJECT
public:
    ProgressDialog(QString title, QString text, QWidget *parent = 0);
    ~ProgressDialog();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);

private:
    Ui::ProgressDialog *ui;
};

#endif // PROGRESSDIALOG_H
