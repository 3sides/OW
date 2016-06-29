#include "stdafx.h"
#include "User.h"

#include <sstream>
#include "Log.h"
#include "DbHelper.h"
#include "UserConfigDB.h"

User::User(const char uk_name[], const char fk_workgroup_id[], const char email[], const char sms[], const char tag[])
{
	tableRecord_.uk_name_ = uk_name;
	tableRecord_.fk_workgroup_id_ = fk_workgroup_id;
	tableRecord_.email_ = email;
	tableRecord_.sms_ = sms;
	tableRecord_.tag_ = tag;
}

User::~User()
{
}

int User::dbRecordCreate() const
{
	static const char* const comma = DbHelper::comma;
	static const char* const squote = DbHelper::squote;

	const std::string sql =
		std::string(_NSTR("INSERT INTO ")) + Schema::UserTable::kTableName + 
		_NSTR(" (") + 
			Schema::UserTable::ColumnName::uk_name +         comma + 
			Schema::UserTable::ColumnName::fk_workgroup_id + comma + 
			Schema::UserTable::ColumnName::email +           comma + 
			Schema::UserTable::ColumnName::sms +             comma + 
			Schema::UserTable::ColumnName::tag + 
		_NSTR(") ")
		_NSTR("VALUES ")
		_NSTR("(") + 
			squote + tableRecord_.uk_name_ +         squote + comma + 
			         tableRecord_.fk_workgroup_id_          + comma + 
			squote + tableRecord_.email_ +           squote + comma + 
			squote + tableRecord_.sms_ +             squote + comma + 
			squote + tableRecord_.tag_ +             squote + 
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

int User::dbRecordRead()
{
	// TODO: Implement
	return -1;
}

int User::dbRecordUpdate() const
{
	// TODO: Implement
	return -1;
}

int User::dbRecordDelete()
{
	// TODO: Implement
	return -1;
}
