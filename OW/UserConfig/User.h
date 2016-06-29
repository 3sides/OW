#pragma once

#include "utility.h"
#include "Schema.h"

class USERCONFIG_API User
{
private:
#pragma warning(push)
#pragma warning(disable : 4251)
	Schema::UserTable::Record tableRecord_;
#pragma warning(pop)

public:
	User(const char uk_name[], const char fk_workgroup_id[], const char email[], const char sms[], const char tag[]);
	~User();

private: // Not implemented:
	User(const User&);
	void operator=(const User&);

public:
	int dbRecordCreate() const; // Create new record in DB.        (SQL INSERT)
	int dbRecordRead();         // Read record from DB.            (SQL SELECT)
	int dbRecordUpdate() const; // Update existing record in DB.   (SQL UPDATE)
	int dbRecordDelete();       // Delete existing record from DB. (SQL DELETE)
};
