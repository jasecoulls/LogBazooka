#pragma once
#include <string>
#include <sstream>
#include <iomanip>


// Enum of logtypes.
enum LogType {
	LOGTYPE_NONE = -1,
	LOGTYPE_INT = 0,
	LOGTYPE_STRING = 1,
	LOGTYPE_HEX = 2
};


// Function prototypes.
void ClearLog(HWND hEdit);

std::string int_to_hex(int i);
