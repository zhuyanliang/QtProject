#include "spreadsheet.h"
#include "cell.h"
Spreadsheet::Spreadsheet(QWidget *parent):QTableWidget(parent)
{
    setItemPrototype(new Cell);

    setRowCount(RowCount);
    setColumnCount(ColumnCount);
    clear();
}

bool Spreadsheet::readFile(const QString &fileName)
{
    return true;
}

bool Spreadsheet::writeFile(const QString &fileName)
{

    return true;
}

void Spreadsheet::clear()
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for(int i=0;i<ColumnCount;++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A'+i)));
        setHorizontalHeaderItem(i,item);
    }

    setCurrentCell(0,0);
}
