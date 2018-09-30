#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

private slots:
    void on_EnterSystem_clicked();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
