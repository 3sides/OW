#include "stdafx.h"
#include "Workgroup.h"

#include <sstream>
#include "Log.h"
#include "DbHelper.h"
#include "UserConfigDb.h"

Workgroup::Workgroup(const char uk_name[], const unsigned access)
{
	tableRecord_.uk_name_ = uk_name;
	tableRecord_.access_ = access;
}

Workgroup::~Workgroup()
{
}

int Workgroup::dbRecordCreate() const
{
	static const char* const comma = DbHelper::comma;
	static const char* const squote = DbHelper::squote;

	const std::string sql =
		std::string(_NSTR("INSERT INTO ")) + Schema::WorkgroupTable::kTableName + 
		_NSTR(" (") + 
			Schema::WorkgroupTable::ColumnName::uk_name + comma + 
			Schema::WorkgroupTable::ColumnName::access  + 
		_NSTR(") ")
		_NSTR("VALUES ")
		_NSTR(" (") + 
			squote + tableRecord_.uk_name_ + squote + comma + 
			std::to_string(tableRecord_.access_) + 
		_NSTR(")") _NSTR(";");

	UserConfigDb& userConfigDb = UserConfigDb::instance();
	const char* const sqlStr = sql.c_str();
	const int rc = userConfigDb.execute(sqlStr);
	if (rc != SQLITE_OK)
	{
		LOG(Log::Severity::error, Log::Category::database | Log::Category::write, sql + " " + SQLITE_STR_RC(rc));
	}
	return rc;
}

int Workgroup::dbRecordRead()
{
	// TODO: Implement
	return -1;
}

int Workgroup::dbRecordUpdate() const
{
	// TODO: Implement
	return -1;
}

int Workgroup::dbRecordDelete()
{
	// TODO: Implement
	return -1;
}
