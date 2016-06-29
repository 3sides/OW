#pragma once

#include "sqlite3.h"
#include "DbSqlite.h"
#include "UserConfig.h"

class USERCONFIG_API UserConfigDb: public DbSqlite // Singleton
{
private:
	UserConfigDb();
	// ~UserConfigDb();

public:
	static UserConfigDb& instance();

private:
	sqlite3& getSqlite() const;

public:
	bool isValid() const;

public:
	int create() const;
	int drop() const;

public:
	int execute(const char sql[]) const;
};
