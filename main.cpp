//#define DEBUG
#include "common.hpp"
#ifdef DEBUG
#include <unistd.h>
#endif
#include <string.h>
#include <cctype>

static void trim_front(char *&str)
{
	while (*str == ' ')
		++str;
}

static void trim_end(char *str)
{
	char *end = str + strlen(str) - 1;
	while (end != str && *end == ' ') {
		*end = '\0';
		--end;
	}
}


static void lower_case(char *str)
{
	for (char *c = str; *c; ++c) {
		*c = std::tolower(*c);
	}
}

static void fmt_date(char *str)
{
	// puts in yyyy-mm-dd format
	// allows easier sorting
	int month, day, year;
	if (sscanf(str, "%d/%d/%d", &month, &day, &year) != 3)
		return;
	sprintf(str, "%04d-%02d-%02d", year, month, day);
}

static void delim(char *line, char **ptr)
{
	int i = 1;
	ptr[0] = line;
	for (char *c = line; *c; ++c) {
		if (*c == '\t') {
			*c = '\0';
			ptr[i] = c + 1;
			++i;
		} else if (*c == '\r' || *c == '\n') {
			*c = '\0';
			break;
		}
	}
	if (i != 38) {
		fatal("malformed data");
	}
	for (i = 0; i < 38; ++i) {
		trim_front(ptr[i]);
		trim_end(ptr[i]);
		if (i == 21 || i == 22) {
			fmt_date(ptr[i]);
		} else {
			lower_case(ptr[i]);
		}
	}
}

static inline void read_stdin()
{
	db_exec("BEGIN TRANSACTION;");
	static char line[1024];
	const char *const sql = "INSERT INTO voters (id, county, last_name, first_name, middle_name, name_suffix, is_private, addr_1, addr_2, city, state, zipcode, mailing_addr_1, mailing_addr_2, mailing_addr_3, mailing_city, mailing_state, mailing_zip, mailing_country, gender, race, dob, dor, party, precinct, precinct_group, precinct_split, precinct_suffix, is_active, congressional_district, house_district, senate_district, county_commision_district, school_board_district, phone_area, phone, phone_ext, email_addr) VALUES (?2, ?1, ?3, ?5, ?6, ?4, ?7, ?8, ?9, ?10, ?11, ?12, ?13, ?14, ?15, ?16, ?17, ?18, ?19, ?20, ?21, ?22, ?23, ?24, ?25, ?26, ?27, ?28, ?29, ?30, ?31, ?32, ?33, ?34, ?35, ?36, ?37, ?38)";
	sqlite3_stmt *stmt;
	db_prepare(sql, &stmt);
	int counter = 0;
	while (fgets(line, 1024, stdin)) {
		++counter;
		if ((counter & 0xFFFF) == 0) {
			printf("processed %dK rows\n", counter / 1000);
		}
		char *ptr[38];
		delim(line, ptr);
		for (int i = 1; i <= 38; ++i) {
			trace(ptr[i - 1]);
			sqlite3_bind_text(stmt, i, ptr[i - 1], -1, SQLITE_STATIC);
		}
		db_step_all(stmt);
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);
	}
	sqlite3_finalize(stmt);
	db_exec("COMMIT;");
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fatal("provide db name as an argument");
	}
#ifdef DEBUG
	unlink(argv[1]);
#endif
	if (sqlite3_open(argv[1], &db)) {
		trace(sqlite3_errmsg(db));
		fatal("can't open database");
		sqlite3_close(db);
	}
	db_exec_file("pre_init.sql");
	read_stdin();
	db_exec_file("post_init.sql");
	db_close();
}
