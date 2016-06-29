#include <string>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QSqlRelationalDelegate>
#include <QQuickView>
#include <QSqlError>
#include <QSqlQuery>

#include "Schema.h"

#include "SqlQueryUserConfigModel.h"

// For more details see:
// Qt example: "Table Model Example"
// and
// http://stackoverflow.com/questions/16658360/integrating-sqlite-with-qt-quick
// http://wiki.qt.io/How_to_use_a_QSqlQueryModel_in_QML

QSqlError init()
{
    QSqlError result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // TODO: This appears to be a resource leak, but seems required. Why???
    // Open database file. The driver creates a new file if it doesn't exist yet. Not a priority, but we want it to emit an error if database not found.
    db.setDatabaseName("UserConfig.sqlite");
    // db.setDatabaseName(":memory:");

    if (!db.open())
    {
        result = db.lastError();
    }

    return result;
}

int main(int argc, char **argv)
{
//    static constexpr char comma[] = ", ";
//    static const std::string sqlSelect =
//            std::string("SELECT ") +
//            Schema::UserTable::ColumnName::kId +             comma +
//            Schema::UserTable::ColumnName::kTimestamp +      comma +
//            Schema::UserTable::ColumnName::kData +           comma +
//            Schema::UserTable::ColumnName::kNote +           comma +
//            Schema::UserTable::ColumnName::uk_name +         comma +
//            Schema::UserTable::ColumnName::fk_workgroup_id + comma +
//            Schema::UserTable::ColumnName::email +           comma +
//            Schema::UserTable::ColumnName::sms +             comma +
//            Schema::UserTable::ColumnName::tag +             " "
//            "FROM " + Schema::UserTable::kTableName +        ";";

    init();

    QGuiApplication app(argc, argv);

    SqlQueryUserConfigModel sqlQueryUserConfigModel(nullptr);

    QQuickView view;
    auto context = view.rootContext();
    context->setContextProperty("sqlQueryUserConfigModel", &sqlQueryUserConfigModel);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
