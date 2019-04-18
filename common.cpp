#include "common.hpp"
#include <thread>

sqlite3 *db = nullptr;

void db_close()
{
	if (db) {
		sqlite3_close(db);
	}
	db = nullptr;
}

void _fatal(const char *msg, const char *fname, int line)
{
	fprintf(stderr, "fatal: %s (%s:%d)\n", msg, fname, line);
	db_close();
	exit(1);
}

void _db_exec(const char *sql, const char *fname, int line)
{
	char *err;
	int r = sqlite3_exec(db, sql, nullptr, 0, &err);
	if (r != SQLITE_OK) {
		fprintf(stderr, "sqlite3 error while performing query (%s:%d)\n  %s\n", fname, line, err);
		sqlite3_free(err);
		db_close();
		exit(1);
	}
}

void _db_prepare(const char *sql, sqlite3_stmt **stmt, const char *fname, int line)
{
	int r = sqlite3_prepare_v2(db, sql, -1, stmt, nullptr);
	if (r != SQLITE_OK) {
		fprintf(stderr, "sqlite3 error while making prepared statement (%s:%d)\n  %s\n", fname, line, sqlite3_errmsg(db));
		db_close();
		exit(1);
	}
}

void _db_step_all(sqlite3_stmt *stmt, const char *fname, int line)
{
	for ( ; ; ) {
		int r = sqlite3_step(stmt);
		switch (r) {
		case SQLITE_DONE:
			return;
		case SQLITE_BUSY:
			std::this_thread::yield();
			break;
		default:
		fprintf(stderr, "sqlite3 error while stepping (%s:%d)\n  %s\n", fname, line, sqlite3_errmsg(db));
			db_close();
			exit(1);
			break;
		}
	}
}

void db_exec_file(const char *fname)
{
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace(fname);
		perror("cannot open");
		exit(1);
	}
	char *buf = new char[4096];
	size_t n = fread(buf, 1, 4096, f);
	if (n == 4096) {
		trace(fname);
		fatal("file too big");
	}
	fclose(f);
	buf[n] = '\0';
	char *err;
	int r = sqlite3_exec(db, buf, nullptr, 0, &err);
	if (r != SQLITE_OK) {
		fprintf(stderr, "sqlite3 error while performing query (%s)\n  %s\n", fname, err);
		sqlite3_free(err);
		db_close();
		exit(1);
	}
}
