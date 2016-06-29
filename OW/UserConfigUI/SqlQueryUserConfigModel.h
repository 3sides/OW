#ifndef SQLQUERYUSERCONFIGMODEL_H
#define SQLQUERYUSERCONFIGMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class SqlQueryUserConfigModel : public  QSqlTableModel // QSqlQueryModel
{
    Q_OBJECT

private:
    QHash<int, QByteArray> roleNamesHash_;

public:
    SqlQueryUserConfigModel(QObject* const parent);

private:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const { return roleNamesHash_; }
};

#endif // SQLQUERYUSERCONFIGMODEL_H
