#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class GotoCell_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GotoCell_Dialog(QWidget *parent = 0);
    ~GotoCell_Dialog();

    QString getCellLocation();
    
private slots:
    void on_lineEdit_textChanged();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
