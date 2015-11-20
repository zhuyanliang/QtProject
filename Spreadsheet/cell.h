#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();

    QTableWidgetItem *clone() const;

    QVariant data(int role) const;

    void setData(int role, const QVariant &value);
    void setDirty();

    QString formula() const;

private:
    QVariant value() const;

    QVariant evalExpression(const QString &str,int &pos) const;
    QVariant evalTerm(const QString &str,int &pos) const;
    QVariant evalFactor(const QString &str,int &pos) const;

    mutable QVariant cachedValue;
    mutable bool cachedIsDirty;
};

#endif // CELL_H
