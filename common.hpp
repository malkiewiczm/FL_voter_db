#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "sqlite3/sqlite3.h"

extern sqlite3 *db;
void _fatal(const char *msg, const char *fname, int line);
#define fatal(msg)(_fatal((msg), __FILE__, __LINE__))
#define trace(what)(std::cout << '[' << __FILE__ << ':' << __LINE__ << "] " #what " = " << what << std::endl)
void _db_exec(const char *sql, const char *fname, int line);
#define db_exec(sql)(_db_exec((sql), __FILE__, __LINE__))
void _db_prepare(const char *sql, sqlite3_stmt **stmt, const char *fname, int line);
#define db_prepare(sql, stmt)(_db_prepare((sql), (stmt), __FILE__, __LINE__))
void db_close();
void _db_step_all(sqlite3_stmt *stmt, const char *fname, int line);
#define db_step_all(stmt)(_db_step_all((stmt), __FILE__, __LINE__))
void db_exec_file(const char *fname);
