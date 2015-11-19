#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();

private:
    QVariant cachedValue;
    bool cachedIsDirty;
};

#endif // CELL_H
