#include "dl.h"

int main(int argc, char* argv[]) {
	if(!dolt_is_initialized()) {
		int res = dolt_init();
		if(res != 0) {
			return res;
		}
	}
	int res = dolt_status();
	if(res != 0) {
		return res;
	}
	res = dolt_sql_query("CREATE TABLE IF NOT EXISTS test (pk BIGINT PRIMARY KEY AUTO_INCREMENT, v1 BIGINT);");
	if(res != 0) {
		return res;
	}
	res = dolt_sql_query("INSERT INTO test (v1) VALUES (0), (1);");
	if(res != 0) {
		return res;
	}
	res = dolt_sql_query("SELECT * FROM test;");
	if(res != 0) {
		return res;
	}
	res = dolt_status();
	if(res != 0) {
		return res;
	}
	return 0;
}
