#include "framework.h"
#include "LogRoutines.h"
#include <Commdlg.h>


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

BOOL FileExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


void SaveLog(HWND hEdit, HWND MainWindow)
{
	// Get the path to save to. 
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = MainWindow;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetSaveFileName(&ofn);
	
	// Did we choose a file?
	if (ofn.lpstrFile != NULL)
	{
		// Does that file exist?
		if (FileExists(ofn.lpstrFile))
		{
			// Ask the user if we should overwrite the file?
			int msgboxID = MessageBox(
				MainWindow,
				(LPCWSTR)L"File already exists. Overwrite?",
				(LPCWSTR)L"Overwrite?",
				MB_ICONWARNING | MB_YESNO
			);
			// Exit if they say NO.
			if (msgboxID == IDNO)
			{
				return;
			}
			else {
				// Delete the file.
				DeleteFile(ofn.lpstrFile);
			}
		}
		
		// Get the text from the log window.
		int len = GetWindowTextLength(hEdit);
		TCHAR* buffer = new TCHAR[len + 1];
		GetWindowText(hEdit, buffer, len + 1);
		
		// Open the file.
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(MainWindow, L"Error opening file.", L"Error", MB_ICONERROR);
			return;
		}

		// Write the BOM for UTF-16
		BYTE bom[] = { 0xFF, 0xFE };
		DWORD dwBytesWritten = 0;
		WriteFile(hFile, bom, sizeof(bom), &dwBytesWritten, NULL);

		// Write the text to the file.
		WriteFile(hFile, buffer, len * sizeof(wchar_t), &dwBytesWritten, NULL);

		// Close the file.
		CloseHandle(hFile);
		
		// Free the buffer.
		delete[] buffer;
		
		// Tell the user we saved the file.
		MessageBox(MainWindow, L"Log saved.", L"Success", MB_ICONINFORMATION);
		
	}
	
}
