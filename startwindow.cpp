#include "startwindow.h"
#include "ui_startwindow.h"

QString StartWriterName;
int OrderID;

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp1251"));
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_EnterSystem_clicked()
{
    int WriterID = ui->comboBoxWriters->currentIndex();
    if (WriterID == 1) StartWriterName = "Yan";
    if (WriterID == 2) StartWriterName = "Vasya";
    if (WriterID == 3) StartWriterName = "Yasha";
    if (WriterID == 1 ||WriterID == 2||WriterID == 3)
    {
        OrderID = 0;
        QFile logfile;
        logfile.setFileName("LoginInfo.txt");
        logfile.open(QIODevice::Append | QIODevice::Text);
        QTextStream writeStream(&logfile);
        writeStream << "WriterName $" << StartWriterName << endl;
        writeStream << "QuestsCounter $" << 0 << endl;
        writeStream << endl;
        logfile.close();
        close();
    }
    else QMessageBox::information(0, "Вы не авторизовались", "Выберите свой профиль");
}
