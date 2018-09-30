#include "vartabclass.h"
#include "ui_vartabclass.h"

VarTabClass::VarTabClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VarTabClass)
{
    ui->setupUi(this);

    ui->Yes->setVisible(false);
    ui->No->setVisible(false);
    ui->Yes->setEnabled(false);
    ui->No->setEnabled(false);
    ui->line->setVisible(true);
    id=-1;
}

VarTabClass::~VarTabClass()
{
    delete ui;
}

void VarTabClass::on_DeleteBranch_clicked()
{
    ui->DeleteBranch->setDisabled(true);
    ui->DeleteBranch->setText("Удалить?");
    ui->Yes->setVisible(true);
    ui->No->setVisible(true);
    ui->Yes->setEnabled(true);
    ui->No->setEnabled(true);
    ui->line->setVisible(false);
}

void VarTabClass::on_Yes_clicked()
{
    emit deleteit(id);
}

void VarTabClass::on_No_clicked()
{
    ui->DeleteBranch->setEnabled(true);
    ui->DeleteBranch->setText("Удалить ветвь");
    ui->Yes->setVisible(false);
    ui->No->setVisible(false);
    ui->Yes->setEnabled(false);
    ui->No->setEnabled(false);
    ui->line->setVisible(true);
}

void VarTabClass::on_ButtonText_textEdited(const QString &arg1)
{
    emit SendButtonText(id, arg1);
}

void VarTabClass::on_NumberOfOutcomes_valueChanged(int arg1)
{
    emit SendNumberOfOutcomes(id, arg1);
}

void VarTabClass::slotfillbuttonText(QString txt)
{
    ui->ButtonText->setText(txt);
}

void VarTabClass::slotfillNumberOfOutcomes(int NOO)
{
    ui->NumberOfOutcomes->setValue(NOO);
}
