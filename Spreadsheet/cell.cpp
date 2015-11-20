#include "cell.h"

Cell::Cell()
{
    setDirty();
}

void Cell::setData(int role, const QVariant &value)
{
    QTableWidgetItem::setData(role,value);
    if(role==Qt::EditRole)
        setDirty();
}

QTableWidgetItem *Cell::clone() const
{
    return new Cell(*this);
}

void Cell::setDirty()
{
    cachedIsDirty = true;
}

QVariant Cell::data(int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(value().isValid()){
            return value().toString();
        }else{
            return value().toString();
        }
    }
    else if(role == Qt::TextAlignmentRole)
    {
        if(value().type() == QVariant::String)
        {
            return int(Qt::AlignLeft|Qt::AlignVCenter);
        }
        else
        {
            return int(Qt::AlignRight|Qt::AlignVCenter);
        }
    }
    else
    {
        return QTableWidgetItem::data(role);
    }
}

const QVariant Invalid;

QVariant Cell::value() const
{
    if(cachedIsDirty)
    {
        QString formulaStr = formula();
        if(formulaStr.startsWith('\''))
        {
            cachedValue = formulaStr.mid(1);
        }
        else if(formulaStr.startsWith('='))
        {
            cachedValue = Invalid;
            QString expr = formulaStr.mid(1);
            expr.replace(" ","");
            expr.append(QChar::Null);

            int pos = 0;
            //cachedValue = evalExpression(expr,pos);
            if(expr[pos] != QChar::Null)
                cachedValue = Invalid;
        }

        cachedIsDirty = false;
    }
    cachedValue = formula();

    return cachedValue;
}

void Cell::setFormula(const QString &str)
{
    setData(Qt::EditRole,str);
}

QString Cell::formula() const
{
    return data(Qt::EditRole).toString();
}
