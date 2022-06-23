#ifndef DOLTLIB_H
#define DOLTLIB_H

#include "stdlib.h"
#include "string.h"
#include "doltlib.h"

int exec(int command, int argCount, char* args[]) {
	GoString* strs = malloc(sizeof(GoString)*argCount);
	for(int i = 0; i < argCount; i++) {
		strs[i].n = (ptrdiff_t)strlen(args[i]);
		strs[i].p = args[i];
	}
	GoSlice goSliceArgs = {strs, (GoInt)argCount, (GoInt)argCount};
	int res = (int)Exec(command, goSliceArgs);
	free(strs);
	return res;
}

int dolt_is_initialized() {
	return (int)IsInitialized();
}

int dolt_init() {
	return exec(0, 0, NULL);
}

int dolt_status() {
	return exec(1, 0, NULL);
}

int dolt_sql_query(char* query) {
	char** args = malloc(sizeof(char*)*2);
	args[0] = "-q";
	args[1] = query;
	int res = (int)exec(7, 2, args);
	free(args);
	return res;
}

int dolt_table_import_update(char* tblName, char* fileName) {
	char** args = malloc(sizeof(char*)*2);
	args[0] = tblName;
	args[1] = "-u";
	args[2] = fileName;
	int res = (int)exec(37, 3, args);
	free(args);
	return res;
}

#endif //DOLTLIB_H
