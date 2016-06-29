#include "SqlQueryUserConfigModel.h"
#include "QSqlRecord"
#include "Schema.h"

SqlQueryUserConfigModel::SqlQueryUserConfigModel(QObject* const parent) :  QSqlTableModel (parent)
{
    static constexpr const char* columnNames[] =
    {
        Schema::UserTable::ColumnName::kId,
        Schema::UserTable::ColumnName::kTimestamp,
        Schema::UserTable::ColumnName::kData,
        Schema::UserTable::ColumnName::kNote,
        Schema::UserTable::ColumnName::uk_name,
        Schema::UserTable::ColumnName::fk_workgroup_id,
        Schema::UserTable::ColumnName::email,
        Schema::UserTable::ColumnName::sms,
        Schema::UserTable::ColumnName::tag
    };

    std::size_t i;
    i = _countof(columnNames);
    while (i != 0)
    {
        --i;
        const auto key = static_cast<int>(ENUM_INDEX(Qt::UserRole)+i);
        roleNamesHash_.insert(key, QByteArray(columnNames[i]));
    }

    setTable(Schema::UserTable::kTableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
    std::size_t n = _countof(columnNames);
    while (n != 0)
    {
        --n;
        const auto section = static_cast<int>(n);
        setHeaderData(section, Qt::Horizontal, columnNames[n]);
    }
}

QVariant SqlQueryUserConfigModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    if (role < Qt::UserRole)
    {
        result = QSqlQueryModel::data(index, role);
    }
    else
    {
        const auto r = record(index.row());
        result = r.value(role - Qt::UserRole);
    }
    return result;
}
