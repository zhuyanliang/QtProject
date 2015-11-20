#ifndef SPRADSHEET_H
#define SPRADSHEET_H
#include <QTableWidget>

class Cell;

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    Spreadsheet(QWidget *parent = 0);
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void clear();
    QTableWidgetSelectionRange selectedRange() const;
    QString currentLocation() const;
    QString currentFormula();

public slots:
    void cut();
    void copy();
    void paste();
    void del();
    void selectCurrentRow();
    void selectCurrentColumn();
    void recalculate();
    void somethingChanged();

signals:
    void modified();

private:
    enum{MagicNumber = 0x7F51C883,RowCount = 999,ColumnCount = 26};
    QString formula(int,int);
    Cell *cell(int,int);
    void setFormula(int row,int column,const QString &str);
    bool autoRecalc;
};

#endif // SPRADSHEET_H
