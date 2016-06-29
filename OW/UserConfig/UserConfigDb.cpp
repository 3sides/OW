#include "stdafx.h"

#include "UserConfigDb.h"

#include "Log.h"
#include "Schema.h"
#include "DbHelper.h"
#include "resstrings.h"

UserConfigDb::UserConfigDb(): 
	DbSqlite(Schema::kDatabaseName, Schema::SqlCreate())
{
}

UserConfigDb& UserConfigDb::instance()
{
	static UserConfigDb result;
	return result;
}

bool UserConfigDb::isValid() const
{
	const bool result = (dbSqlite_ != nullptr);
	return result;
}

sqlite3& UserConfigDb::getSqlite() const
{
	const bool valid = isValid();
	if (!valid)
	{
		const Values::ResStrings& logStrings = Values::ResStrings::instance();
		const std::string message = logStrings.getText(Values::ResStrings::StringID::error_db_local_get);

		LOG(Log::Severity::error, Log::Category::database | Log::Category::initialize, message);
	}
	sqlite3& result = *dbSqlite_;
	return result;
}

int UserConfigDb::create() const
{
	sqlite3& sqlite = getSqlite();
	const std::string& sqlCreate = Schema::SqlCreate();
	const int rc = DbHelper::dbCreate(&sqlite, sqlCreate);
	return rc;
}

int UserConfigDb::drop() const
{
	sqlite3& sqlite = getSqlite();
	const std::string& sqlDrop = Schema::SqlDrop();
	const int rc = DbHelper::dbDrop(&sqlite, sqlDrop);
	return rc;
}

int UserConfigDb::execute(const char sql[]) const
{
	sqlite3& sqlite = getSqlite();
	const int rc = DbHelper::dbExecute(&sqlite, sql);
	return rc;
}
