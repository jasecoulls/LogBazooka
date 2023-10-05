#include "HexDumper.h"
#include <vector>

std::wstring HexView(std::wstring source, size_t size)
{
	// Convert the source string to string containing the bytes as hex, separated by spaces
	// along with the ASCII representation of the bytes to the right.
	
	// The output string
	std::wstring output;
	
	// The line chunk size in characters.
	size_t chunkSize = 16;
	// Break (using a space) after this many characters.
	size_t breakPosition = 8;
	
	// Break the source string into chunks of size chunkSize.
	std::vector<std::wstring> chunks;
	for (size_t i = 0; i < source.size(); i += chunkSize)
	{
		chunks.push_back(source.substr(i, chunkSize));
	}
	
	// Loop through the chunks.
	for (size_t chunk_idx = 0; chunk_idx < chunks.size(); chunk_idx++)
	{
		
		// For each character, get it's ascii value in Hex and its regular representation.
		std::wstring hex;
		std::wstring characters;  // New string for characters

		for (size_t char_index = 0; char_index < chunks[chunk_idx].size(); char_index++)
		{
			wchar_t buffer[5];
			swprintf_s(buffer, L"%02X ", chunks[chunk_idx][char_index]);
			hex += buffer;

			// Add to the characters string
			wchar_t ch = chunks[chunk_idx][char_index];
			if (ch >= L' ' && ch <= L'~')  // Check if the character is a printable ASCII character
			{
				characters += ch;
			}
			else
			{
				characters += L'.';  // Add a period for non-printable characters
			}

			// If we hit the breakPosition, add the break
			if (char_index == breakPosition - 1)
			{
				hex += L"- ";	// Note, no space before the dash
				characters += L" - ";  // Add the same break to the characters string
			}
		}

		// Pad with 00's if the chunk is not full.
		int thisChunkSize = chunks[chunk_idx].size();
		if (thisChunkSize < chunkSize)
		{
			for (int i = thisChunkSize; i < chunkSize; i++)
			{
				hex += L"00 ";
				characters += L".";

				// If we hit the breakPosition, add the break with a " - ".
				if (i == breakPosition - 1)
				{
					hex += L"- ";
					characters += L" - ";
				}
			}
		}

		// Add the hex string to the output.
		std::wstring this_line = hex + L"  " + characters + L"\r\n";;
		output += this_line;

	}
	
	return output;
	
}