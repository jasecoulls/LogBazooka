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
		
		// For each character, get it's ascii value in Hex.
		std::wstring hex;
		for (size_t char_index = 0; char_index < chunks[chunk_idx].size(); char_index++)
		{
			wchar_t buffer[5];
			swprintf_s(buffer, L"%02X ", chunks[chunk_idx][char_index]);
			hex += buffer;

			// If we hit the breakPosition, add the break with a " - ".
			if (char_index == breakPosition - 1)
			{
				hex += L" - ";
			}
		}

		// Pad with 00's if the chunk is not full.
		int thisChunkSize = chunks[chunk_idx].size();
		if (thisChunkSize < chunkSize)
		{
			for (int i = 0; i < chunkSize - thisChunkSize; i++)
			{
				hex += L"00 ";
				// If we hit the breakPosition, add the break with a " - ".
				if (i == breakPosition - 1)
				{
					hex += L" - ";
				}
			}
		}

		// Add a \n
		hex += L"\n";

		// Add the hex string to the output.
		output += hex;

	}
	
	return output;
	
}