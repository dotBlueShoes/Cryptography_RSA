#pragma once
#include "Framework.hpp"
#include "Windows/Windows.hpp"

namespace FileIO {

	namespace WinAPI {

		// block Sample() {
		// 
		// 	/* Whats 0 stays 0 ... */
		// 
		// 	OPENFILENAME ofn { 0 };
		// 	array<wchar, 512> readFilePath { 0 };
		// 	ofn.lStructSize = sizeof ofn;					// length of structure
		// 	// ofn.hwndOwner = nullptr;						// parent			
		// 
		// 	// ofn.hInstance
		// 
		// 	// Filters
		// 	//  double null-termination at the end.
		// 	ofn.lpstrFilter = L"All\0"
		// 		"*.*\0"
		// 		"Text\0"
		// 		"*.TXT\0";
		// 
		// 	ofn.nFilterIndex = 1;							// currently selected filter.
		// 
		// 	ofn.nMaxFile = readFilePath.size();		// size of the buffer (should be at least 256) characters long
		// 	ofn.lpstrFile = readFilePath.data();			//
		// 
		// 	// ofn.lpstrFileTitle = nullptr;				//
		// 	// ofn.nMaxFileTitle = 0;
		// 
		// 	// ofn.lpstrFile[0] = '\0';						// has to be null-terminated
		// 	// ofn.lpstrInitialDir = nullptr;				//
		// 
		// 	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		// 
		// 	GetOpenFileName(&ofn);
		// 
		// 	// Now simpley display the file name 
		// 	MessageBox(NULL, ofn.lpstrFile, L"File Name", MB_OK);
		// 	return 0;
		// }

		OPENFILENAME openedFile;

		block OpenFilePrompt(
			IN const Windows::Handle& parentWindow
		) {
			array<wchar, 512> readFilePath { 0 };

			openedFile = { 0 };
			openedFile.lStructSize = sizeof openedFile;
			openedFile.hwndOwner = parentWindow;

			openedFile.nFilterIndex = 1;
			openedFile.lpstrFilter = L"All\0"
				"*.*\0"
				"Text\0"
				"*.TXT\0";

			openedFile.nMaxFile = readFilePath.size();
			openedFile.lpstrFile = readFilePath.data();

			openedFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			GetOpenFileName(&openedFile);

			//{ // Debug
			//	MessageBox(NULL, openedFile.lpstrFile, L"File Name", MB_OK);
			//}
		}

		block SaveFilePrompt(
			IN const Windows::Handle& parentWindow
		) {
			array<wchar, 512> readFilePath { 0 };

			openedFile = { 0 };
			openedFile.lStructSize = sizeof openedFile;
			openedFile.hwndOwner = parentWindow;

			openedFile.lpstrFilter = L"All Files(*.*)\0"
								   "*.*\0"
							       "Text Files (*.txt)\0"
							       "*.txt\0";

			openedFile.lpstrFile = readFilePath.data();
			openedFile.nMaxFile = readFilePath.size();

			openedFile.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			GetSaveFileName(&openedFile);

			//{ // DEBUG
			//	MessageBox(NULL, openedFile.lpstrFile, L"File Name", MB_OK);
			//}
		}
	}

	namespace Read {

		auto File(
			IN	const wchar* const filePath
		) {
			std::ifstream inputFile(filePath, std::ios::binary);

			// READ
			std::vector<byte> buffer(std::istreambuf_iterator<char>(inputFile), {});
			inputFile.close();

			return buffer;
		}

	}

	namespace Write {

		auto File(
			IN	const wchar* const filePath,
			IN	const size bufferCount,
			IN	const byte* const buffer
		) {
			std::ofstream outputFile(filePath, std::ios::binary);

			for (size i = 0; i < bufferCount; ++i) {
				outputFile << buffer[i];
			}

			outputFile.close();
		}

	}

}