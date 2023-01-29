#include "framework.h"
#include "LogRoutines.h"

/// <summary>
/// Clears the log window.
/// </summary>
/// <param name="hEdit">The handle to the Edit control to clear. </param>
void ClearLog(HWND hEdit)
{
	// Clear the log
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"LogBazooka - Ready...");

}


std::string int_to_hex(int i)
{
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(sizeof(int) * 2)
		<< std::hex << i;
	return stream.str();
}
