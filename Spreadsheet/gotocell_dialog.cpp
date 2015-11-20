#include "gotocell_dialog.h"
#include "ui_gotocell_dialog.h"

GotoCell_Dialog::GotoCell_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp,this));
}

void GotoCell_Dialog::on_lineEdit_textChanged()
{
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}

QString GotoCell_Dialog::getCellLocation()
{
    return ui->lineEdit->text();
}

GotoCell_Dialog::~GotoCell_Dialog()
{
    delete ui;
}
