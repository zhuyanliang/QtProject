#ifndef SPRADSHEET_H
#define SPRADSHEET_H
#include <QTableWidget>

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    Spreadsheet(QWidget *parent = 0);
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void clear();

private:
    enum{RowCount = 999,ColumnCount = 26};
};

#endif // SPRADSHEET_H
