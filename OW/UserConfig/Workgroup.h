#pragma once

#include "utility.h"
#include "Schema.h"

class USERCONFIG_API Workgroup
{
private:
#pragma warning(push)
#pragma warning(disable : 4251)
	Schema::WorkgroupTable::Record tableRecord_;
#pragma warning(pop)

public:
	Workgroup(const char name[], const unsigned access);
	~Workgroup();

	// TODO: Find C++14 generated functions.
private: // Not implemented:
	Workgroup(const Workgroup&);
	void operator=(const Workgroup&);

public:
	int dbRecordCreate() const; // Create new record in DB.        (SQL INSERT)
	int dbRecordRead();         // Read record from DB.            (SQL SELECT)
	int dbRecordUpdate() const; // Update existing record in DB.   (SQL UPDATE)
	int dbRecordDelete();       // Delete existing record from DB. (SQL DELETE)
};
