#pragma once

#include <cstdint>
#include <tchar.h>
#include <string>
#include "utility.h"
#include "UserConfig.h"

class USERCONFIG_API Schema
{
private:
	using NarrowChar = char;
	using LiteralNarrowString = const NarrowChar[];

private:
	Schema();
	~Schema();

public:
	static constexpr LiteralNarrowString kDatabaseName = _NSTR("UserConfig.sqlite");
	static constexpr int kDatabaseVersion = 1; // TODO: Mark user_version with SQLite PRAGMA command.

	class TableImpl
	{
	protected:
		class ColumnName
		{
		public:
			static constexpr LiteralNarrowString kId =        _NSTR("_id");
			static constexpr LiteralNarrowString kTimestamp = _NSTR("timestamp");
			static constexpr LiteralNarrowString kData =      _NSTR("_data");
			static constexpr LiteralNarrowString kNote =      _NSTR("note");
		};

	private:
		using TIMESTAMP = uint64_t;

	protected:
		class Record
		{
		protected:
			long _id;

		public:
			TIMESTAMP _timestamp;
			tstring _data;
		};
	};

	template <class T>
	class Table: public TableImpl
	{
	public:
		static std::string SqlCreate()
		{
			static const std::string result = 
				std::string(_NSTR("CREATE TABLE IF NOT EXISTS ")) + T::kTableName + 
				_NSTR(" (") 
					_NSTR("_id")       _NSTR(" INTEGER PRIMARY KEY AUTOINCREMENT, ") 
					_NSTR("timestamp") _NSTR(" DATETIME DEFAULT CURRENT_TIMESTAMP, ") 
					_NSTR("_data")     _NSTR(" TEXT, ") // Commonly used to store an external filename. 
					_NSTR("note")      _NSTR(" TEXT, ") + 
					T::kSqlAttributes + 
				_NSTR(")") _NSTR(";");

			return result;
		}

		static std::string SqlDrop()
		{
			static const std::string result = 
				std::string(_NSTR("DROP TABLE IF EXISTS ")) + T::kTableName + _NSTR(";");

			return result;
		}
	};

	class USERCONFIG_API WorkgroupTable : public Table<WorkgroupTable>
	{
	public:
		static constexpr LiteralNarrowString kTableName = _NSTR("Workgroup");

		class USERCONFIG_API ColumnName : public Table<WorkgroupTable>::ColumnName
		{
		public:
			static constexpr LiteralNarrowString uk_name = _NSTR("uk_name");
			static constexpr LiteralNarrowString access  = _NSTR("access");
		};

		class Record : public Table<WorkgroupTable>::Record
		{
		public:
			tstring uk_name_;
			unsigned access_;
		};

		static constexpr LiteralNarrowString kSqlAttributes =
			_NSTR("uk_name") _NSTR(" TEXT UNIQUE NOT NULL, ")
			_NSTR("access")  _NSTR(" INTEGER NOT NULL");
	};

	class USERCONFIG_API UserTable : public Table<UserTable>
	{
	public:
		static constexpr LiteralNarrowString kTableName = _NSTR("User");

		class USERCONFIG_API ColumnName : public Table<UserTable>::ColumnName
		{
		public:
			static constexpr LiteralNarrowString uk_name         = _NSTR("uk_name");
			static constexpr LiteralNarrowString fk_workgroup_id = _NSTR("fk_workgroup_id");
			static constexpr LiteralNarrowString email           = _NSTR("email");
			static constexpr LiteralNarrowString sms             = _NSTR("sms");
			static constexpr LiteralNarrowString tag             = _NSTR("tag");
		};

		class Record : public Table<UserTable>::Record
		{
		public:
			tstring uk_name_;
			tstring fk_workgroup_id_;
			tstring email_;
			tstring sms_;
			tstring tag_;
		};

		static constexpr LiteralNarrowString kSqlAttributes = 
			_NSTR("uk_name")         _NSTR(" TEXT UNIQUE NOT NULL, ")
			_NSTR("fk_workgroup_id") _NSTR(" INTEGER NOT NULL, ")
			_NSTR("email")           _NSTR(" TEXT NOT NULL, ")
			_NSTR("sms")             _NSTR(" TEXT NOT NULL, ")
			_NSTR("tag")             _NSTR(" TEXT NOT NULL, ")
			_NSTR("FOREIGN KEY(fk_workgroup_id) REFERENCES Workgroup(_id)");
	};

	static const std::string SqlCreate()
	{
		static const std::string result = 
			std::string(_NSTR("BEGIN TRANSACTION;")) + 
				WorkgroupTable::SqlCreate() + 
				UserTable::SqlCreate() + 
			_NSTR("COMMIT TRANSACTION;");

		return result;
	}

	static const std::string SqlDrop()
	{
		static const std::string result =
			std::string(_NSTR("BEGIN TRANSACTION;")) + 
				WorkgroupTable::SqlDrop() + 
				UserTable::SqlDrop() + 
			_NSTR("COMMIT TRANSACTION;");

		return result;
	}
};
