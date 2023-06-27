#pragma once
#include "../Framework.hpp"

#include "../IO/FileIO.hpp"
#include "../RSA/RSA.hpp"
#include "MainTab.hpp"

#include <RichEdit.h>

#define MSFTEDIT_DLL_PATH "Msftedit.dll" // a.k.a TextEdit 4.1
#define BUTTON_CLASS L"BUTTON"
#define STRING_RESULT L"Result"

namespace Window {

    // PREDEFINED FUNCTIONS
    ATOM                MyRegisterClass(HINSTANCE&, const wchar* const);
    BOOL                InitInstance(HINSTANCE&, const int&, const wchar* const,const wchar* const);
    LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

    // GLOBALS
    HINSTANCE currentProcess;
    HWND buttonEncodePathPrompt, buttonDecodePathPrompt, buttonEncodePath, buttonDecodePath, buttonEncode, buttonDecode, buttonSubmit,
        pInput, qInput, reInputPath, reOutputPath, reInput, reOutput;

    uint8 aesBytesLeftPath, aesWordsLeft;

    block LoadRichEdit() { LoadLibrary(TEXT(MSFTEDIT_DLL_PATH)); }

    auto CreateGroupBox (
        HINSTANCE& process,
        HWND& parentWindow,
        const pair<int32>& position,
        const pair<int32>& area,
        const wchar* caption = L"Caption"
    ) {
        HWND groupBox = CreateWindowEx(
            NULL, BUTTON_CLASS,
            caption,
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            position.x, position.y,
            area.x, area.y,
            parentWindow,
            nullptr,
            process,
            nullptr
        );
        return groupBox;
    }

    auto CreateButton (
        HINSTANCE& process,
        HWND& parentWindow,
        const pair<int32>& position,
        const pair<int32>& area,
        const wchar* buttonText = L"Click Me!"
    ) {
        HWND windowButton = CreateWindowEx(
            NULL, BUTTON_CLASS,
            buttonText,
            WS_CHILD | WS_VISIBLE,
            position.x, position.y,
            area.x, area.y,
            parentWindow,
            nullptr,
            process,
            nullptr
        );

        return windowButton;
    }

    auto CreateRichEdit (
        HINSTANCE& process,
        HWND& parentWindow,
        const pair<int32>& position,
        const pair<int32>& area,
        const uint32&  windowStyles,
        const wchar* preText = L"Type here"
    ) {

        HWND windowEdit = CreateWindowEx(
            NULL, MSFTEDIT_CLASS, 
            preText,
            windowStyles,
            position.x, position.y, 
            area.x, area.y,
            parentWindow, 
            nullptr,
            process, 
            nullptr
        );

        return windowEdit;
    }

    ATOM MyRegisterClass(
        HINSTANCE& process, 
        const wchar* const windowClassName
    ) {
        WNDCLASSEXW wcex { 0 };
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = process;
        wcex.hIcon = LoadIcon(process, MAKEINTRESOURCE(IDI_CRYPTOGRAPHYRSA));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = windowClassName;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassExW(&wcex);
    }

    BOOL InitInstance(
        HINSTANCE& process,
        const int& nCmdShow, 
        const wchar* const windowClassName,
        const wchar* const windowTitle,
        const pair<int32>& windowPosition,
        const pair<int32>& windowArea
    ) {
        currentProcess = process;

        HWND windowHandle = CreateWindowW(
            windowClassName, 
            windowTitle, 
            WS_OVERLAPPEDWINDOW,
            windowPosition.x, windowPosition.y,
            windowArea.x, windowArea.y,
            nullptr, 
            nullptr, 
            process,
            nullptr
        );

        if (!windowHandle) return FALSE;

        { // Creation of inner windows.

            { // Tab Window

                const pair<int32> tabPosition { 0, 0 };
                const pair<int32> tabStyleOffset { 16, 26 }; // this should be related to nonClientAreaOffset and tabXOffset... fix it later...
                const pair<int32> tabArea { 
                    windowArea.x - tabStyleOffset.x + 2 /* to hide bottom line */, 
                    windowArea.y - tabStyleOffset.y - 13 + 2 /* to hide bottom line */ 
                };
                const int32 tabXOffset = 24;

                Windows::MainTab::Create (
                    Windows::MainTab::tabHandle,
                    windowHandle,
                    process,
                    tabPosition,
                    tabArea
                );

                { // Caption Boxes
                
                    // Different windows styles 7,8,10 and such have their own nonClientArea.
                    //  for shoutcut this is how it should be on windows 10.
                    const pair<int32> nonClientAreaOffset { 15, 28 };
                    const pair<int32>
                        key1Position { 40 + 10, 10 + tabXOffset },
                        keyArea { 300, 40 },
                        key2Position { key1Position.x + keyArea.x + 80, key1Position.y },
                        submitPosition { key2Position.x + keyArea.x + 110, key1Position.y },
                        submitArea { 100, 28 };

                    { // p
                        const uint32 multiLineStyle = ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_HSCROLL;
                        CreateWindow(L"STATIC", L"P:", WS_VISIBLE | WS_CHILD | SS_LEFT, 20, 10 + tabXOffset + 3, 100, 100, windowHandle, nullptr, process, nullptr);
                        pInput = CreateRichEdit(process, windowHandle, key1Position, keyArea, multiLineStyle, RSA::RSA256::p_str);
                    }

                    { // q
                        const uint32 multiLineStyle = ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_HSCROLL;
                        CreateWindow(L"STATIC", L"Q:", WS_VISIBLE | WS_CHILD | SS_LEFT, 20 + keyArea.x + 80, 10 + tabXOffset + 3, 100, 100, windowHandle, nullptr, process, nullptr);
                        qInput = CreateRichEdit(process, windowHandle, key2Position, keyArea, multiLineStyle, RSA::RSA256::q_str);
                    }

                    { // submit
                        buttonSubmit = CreateButton(process, windowHandle, submitPosition, submitArea, L"Submit");
                    }

                    const pair<int32>
                        positionWindowFile { 10, key1Position.y + keyArea.y + 10 },
                        areaWindowFile { 
                            windowArea.x - 20 - nonClientAreaOffset.x, 
                            60 + 60 + 24 
                        },
                        positionWindowText { 10, positionWindowFile.y + areaWindowFile.y },
                        areaWindowText {
                            windowArea.x - 20 - nonClientAreaOffset.x,
                            windowArea.y - 20 - nonClientAreaOffset.y - areaWindowFile.y - positionWindowFile.y
                    };

                    const wchar* captionRegionFile = L"File", * captionRegionText = L"Text";

                    CreateGroupBox(process, windowHandle, positionWindowFile, areaWindowFile, captionRegionFile);
                    CreateGroupBox(process, windowHandle, positionWindowText, areaWindowText, captionRegionText);

                    { // File Windows
                
                        const pair<int32>
                            areaButton { 100, 24 + 4 },

                            // 1 ROW
                            areaInputFile { 700, 24 + 10 + 18 },
                            positionEncodePrompt { 20, positionWindowFile.y + 20 },
                            positionInputFile { positionEncodePrompt.x + areaButton.x + 10, positionEncodePrompt.y },
                            positionEncode { areaInputFile.x + positionInputFile.x + 10, positionInputFile.y },

                            // 2 ROW
                            areaOutputFile { 700, 24 + 10 + 18 },
                            positionDecodePrompt { 20, positionInputFile.y + areaInputFile.y + 10 },
                            positionOutputFile { positionInputFile.x, positionDecodePrompt.y },
                            positionDecode { areaOutputFile.x + positionOutputFile.x + 10, positionOutputFile.y };
                
                        const uint32 singleLineStyle = WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP;
                
                        const wchar
                            * inputPreText = L"Input file path",
                            * outputPreText = L"Output file path",
                            * encodeText = L"Encode",
                            * decodeText = L"Decode",
                            * selectText = L"Select";

                        buttonEncodePathPrompt = CreateButton(process, windowHandle, positionEncodePrompt, areaButton, selectText);
                        buttonDecodePathPrompt = CreateButton(process, windowHandle, positionDecodePrompt, areaButton, selectText);
                
                        reInputPath = CreateRichEdit(process, windowHandle, positionInputFile, areaInputFile, singleLineStyle, inputPreText);
                        reOutputPath = CreateRichEdit(process, windowHandle, positionOutputFile, areaOutputFile, singleLineStyle, outputPreText);

                        // Show Horizontal Scrollbar
                        SendMessageW(reInputPath, EM_SHOWSCROLLBAR, SB_HORZ, TRUE);
                        SendMessageW(reOutputPath, EM_SHOWSCROLLBAR, SB_HORZ, TRUE);

                        buttonEncodePath = CreateButton(process, windowHandle, positionEncode, areaButton, encodeText);
                        buttonDecodePath = CreateButton(process, windowHandle, positionDecode, areaButton, decodeText);
                    }
                
                    { // Text Windows
                
                        const pair<int32>
                            positionInput { 20, positionWindowText.y + 20 },
                            areaInput { 400, areaWindowText.y - 20 - 10  },
                            positionOutput { positionInput.x + areaInput.x + 10, positionInput.y },
                            areaOutput { 400, areaWindowText.y - 20 - 10 },
                            positionEncode { positionOutput.x + areaOutput.x + 10, positionWindowText.y + 20 },
                            areaEncode { 100, 28 },
                            positionDecode { positionOutput.x + areaOutput.x + 10, positionWindowText.y + 20 + areaEncode.y + 10 },
                            areaDecode { 100, 28 };
                
                
                        const uint32 multiLineStyle = ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP;
                
                        const wchar
                            * inputPreText = L"Text",
                            * outputPreText = L"",
                            * encodeText = L"Encode",
                            * decodeText = L"Decode";
                
                        reInput = CreateRichEdit(process, windowHandle, positionInput, areaInput, multiLineStyle, inputPreText);
                        reOutput = CreateRichEdit(process, windowHandle, positionOutput, areaOutput, multiLineStyle, outputPreText);
                
                        // Show Vertical Scrollbar
                        SendMessageW(reInput, EM_SHOWSCROLLBAR, SB_VERT, TRUE);
                        SendMessageW(reOutput, EM_SHOWSCROLLBAR, SB_VERT, TRUE);
                
                        buttonEncode = CreateButton(process, windowHandle, positionEncode, areaEncode, encodeText);
                        buttonDecode = CreateButton(process, windowHandle, positionDecode, areaDecode, decodeText);
                    }
                }
            }

            //const pair<int32> position { 20, 20 }, area { 100, 100};
            //
            //const uint32 singleLineStyle = ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP,
            //    multiLineStyle = WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP;
        }

        ShowWindow(windowHandle, nCmdShow);
        UpdateWindow(windowHandle);

        return TRUE;
    }

    block OnButtonEncodePathClicked(
        const HWND& windowHandle
    ) {

        // READ INPUT_FIELD LENGTH
        const size inputFilePathLength = SendMessageW(reInputPath, WM_GETTEXTLENGTH, NULL, NULL);
        const size inputStringTerminationPosition = inputFilePathLength + 1;
        const size outputFilePathLength = SendMessageW(reOutputPath, WM_GETTEXTLENGTH, NULL, NULL);
        const size outputStringTerminationPosition = outputFilePathLength + 1;
        //const size keyValueLength = SendMessageW(reKey, WM_GETTEXTLENGTH, NULL, NULL);
        //const size keyStringTerminationPosition = keyValueLength + 1;

        wchar* inputPathBuffor = new wchar[inputStringTerminationPosition];
        wchar* outputPathBuffor = new wchar[outputStringTerminationPosition];
        //wchar* keyBuffor = new wchar[keyStringTerminationPosition];

        // READ INPUT_FIELD DATA
        SendMessageW(reInputPath, WM_GETTEXT, inputStringTerminationPosition, (LPARAM)inputPathBuffor);
        SendMessageW(reOutputPath, WM_GETTEXT, outputStringTerminationPosition, (LPARAM)outputPathBuffor);
        //SendMessageW(reKey, WM_GETTEXT, keyStringTerminationPosition, (LPARAM)keyBuffor);

        // Debug
        //const wchar* const nocryptFilePath = LR"(data/asci1.txt)";
        //const wchar* const encryptFilePath = LR"(data/asci2.txt)";
        //const wchar* const decryptFilePath = LR"(data/3.txt)";

        std::vector<wchar> data;
        //wchar* outputBuffor = nullptr;
        RSA::ret outputBuffor;
        int64 result = 0;

        { // PROCESS
            switch (Windows::MainTab::tabState) {

                default:
                case Windows::MainTab::RSA_256: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        outputBuffor = RSA::Encrypt(data.data(), data.size(), RSA::RSA256::blockSizeWchar, RSA::RSA256::blockSizeUint);
                        RSA::WcharsToFile(std::get<0>(outputBuffor), std::get<1>(outputBuffor), outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_1, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                    
                } break;

                case Windows::MainTab::RSA_512: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        outputBuffor = RSA::Encrypt(data.data(), data.size(), RSA::RSA512::blockSizeWchar, RSA::RSA512::blockSizeUint);
                        RSA::WcharsToFile(std::get<0>(outputBuffor), std::get<1>(outputBuffor), outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_2, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                } break;

                case Windows::MainTab::RSA_1024: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        outputBuffor = RSA::Encrypt(data.data(), data.size(), RSA::RSA1024::blockSizeWchar, RSA::RSA1024::blockSizeUint);
                        RSA::WcharsToFile(std::get<0>(outputBuffor), std::get<1>(outputBuffor), outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_3, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                } break;

                case Windows::MainTab::RSA_2048: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        outputBuffor = RSA::Encrypt(data.data(), data.size(), RSA::RSA2048::blockSizeWchar, RSA::RSA2048::blockSizeUint);
                        RSA::WcharsToFile(std::get<0>(outputBuffor), std::get<1>(outputBuffor), outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_4, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                }

            }
        }

        delete[] inputPathBuffor;
        delete[] outputPathBuffor;
        delete[] std::get<0>(outputBuffor);
    }

    block OnButtonDecodePathClicked(
        const HWND& windowHandle
    ) {

        // READ INPUT_FIELD LENGTH
        const size inputFilePathLength = SendMessageW(reInputPath, WM_GETTEXTLENGTH, NULL, NULL);
        const size inputStringTerminationPosition = inputFilePathLength + 1;
        const size outputFilePathLength = SendMessageW(reOutputPath, WM_GETTEXTLENGTH, NULL, NULL);
        const size outputStringTerminationPosition = outputFilePathLength + 1;
        //const size keyValueLength = SendMessageW(reKey, WM_GETTEXTLENGTH, NULL, NULL);
        //const size keyStringTerminationPosition = keyValueLength + 1;

        wchar* inputPathBuffor = new wchar[inputStringTerminationPosition];
        wchar* outputPathBuffor = new wchar[outputStringTerminationPosition];
        //wchar* keyBuffor = new wchar[keyStringTerminationPosition];

        // READ INPUT_FIELD DATA
        SendMessageW(reInputPath, WM_GETTEXT, inputStringTerminationPosition, (LPARAM)inputPathBuffor);
        SendMessageW(reOutputPath, WM_GETTEXT, outputStringTerminationPosition, (LPARAM)outputPathBuffor);
        //SendMessageW(reKey, WM_GETTEXT, keyStringTerminationPosition, (LPARAM)keyBuffor);

        std::vector<wchar> outputData;
        std::vector<wchar> data;

        { // PROCESS
            switch (Windows::MainTab::tabState) {

                default:
                case Windows::MainTab::RSA_256: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        RSA::Decrypt(outputData, data.data(), data.size(), RSA::RSA256::encodedBlockSizeUint);
                        RSA::WcharsToFile(outputData.data(), outputData.size() - 1, outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_1, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                } break;

                case Windows::MainTab::RSA_512: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        RSA::Decrypt(outputData, data.data(), data.size(), RSA::RSA512::encodedBlockSizeUint);
                        RSA::WcharsToFile(outputData.data(), outputData.size() - 1, outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_2, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                } break;

                case Windows::MainTab::RSA_1024: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        RSA::Decrypt(outputData, data.data(), data.size(), RSA::RSA1024::encodedBlockSizeUint);
                        RSA::WcharsToFile(outputData.data(), outputData.size() - 1, outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_3, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                } break;

                case Windows::MainTab::RSA_2048: {
                    if (!RSA::FileToWchars(data, inputPathBuffor)) {
                        RSA::Decrypt(outputData, data.data(), data.size(), RSA::RSA2048::encodedBlockSizeUint);
                        RSA::WcharsToFile(outputData.data(), outputData.size() - 1, outputPathBuffor);
                        MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_4, STRING_RESULT, MB_OK);
                    } else {
                        MessageBox(windowHandle, L"File is Empty!", L"Error", MB_OK);
                    }
                }

            }
        }

        delete[] inputPathBuffor;
        delete[] outputPathBuffor;
       // delete[] keyBuffor;
    }

    block OnButtonEncodeClick(
        const HWND& windowHandle
    ) {

        // READ LENGTH
        const size inputLength = SendMessageW(reInput, WM_GETTEXTLENGTH, NULL, NULL);
        const size inputStringTerminationPosition = inputLength + 1;
        //const size keyValueLength = SendMessageW(reKey, WM_GETTEXTLENGTH, NULL, NULL);
        //const size keyStringTerminationPosition = keyValueLength + 1;

        wchar* inputBuffor = new wchar[inputStringTerminationPosition];
        //wchar* keyBuffor = new wchar[keyStringTerminationPosition];

        // OUTPUT BUFFOR NECESSITIES
        const uint64 inputBytesLength = inputLength * 2;
        const uint64 blocksCount = inputBytesLength / 16;
        
        RSA::ret outputBuffor;
        //wchar* outputBuffor = nullptr;

        // READ DATA
        SendMessageW(reInput, WM_GETTEXT, inputStringTerminationPosition, (LPARAM)inputBuffor);
        //SendMessageW(reKey, WM_GETTEXT, keyStringTerminationPosition, (LPARAM)keyBuffor);

        { // PROCESS
            switch (Windows::MainTab::tabState) {
                default:
                case Windows::MainTab::RSA_256: {
                    outputBuffor = RSA::Encrypt(inputBuffor, inputLength, RSA::RSA256::blockSizeWchar, RSA::RSA256::blockSizeUint);
                    MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_1, STRING_RESULT, MB_OK);
                } break;

                case Windows::MainTab::RSA_512: {
                    outputBuffor = RSA::Encrypt(inputBuffor, inputLength, RSA::RSA512::blockSizeWchar, RSA::RSA512::blockSizeUint);
                    MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_2, STRING_RESULT, MB_OK);
                } break;

                case Windows::MainTab::RSA_1024: {
                    outputBuffor = RSA::Encrypt(inputBuffor, inputLength, RSA::RSA1024::blockSizeWchar, RSA::RSA1024::blockSizeUint);
                    MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_3, STRING_RESULT, MB_OK);
                } break;

                case Windows::MainTab::RSA_2048: {
                    outputBuffor = RSA::Encrypt(inputBuffor, inputLength, RSA::RSA2048::blockSizeWchar, RSA::RSA2048::blockSizeUint);
                    MessageBox(windowHandle, L"Succefully Encrypted " STRING_KEY_4, STRING_RESULT, MB_OK);
                }

            }

            //outputBuffor[outputCount] = L'\0';
            SendMessageW(reOutput, WM_SETTEXT, NULL, (LPARAM)std::get<0>(outputBuffor));
        }

        delete[] std::get<0>(outputBuffor);
        delete[] inputBuffor;
    }

    block OnButtonDecodeClick(
        const HWND& windowHandle
    ) {
        // READ LENGTH
        const size inputLength = SendMessageW(reOutput, WM_GETTEXTLENGTH, NULL, NULL);
        const size inputStringTerminationPosition = inputLength + 1;
        //const size keyValueLength = SendMessageW(reKey, WM_GETTEXTLENGTH, NULL, NULL);
        //const size keyStringTerminationPosition = keyValueLength + 1;

        wchar* inputBuffor = new wchar[inputStringTerminationPosition];
        //wchar* keyBuffor = new wchar[keyStringTerminationPosition];

        std::vector<wchar> outputData;

        // READ DATA
        SendMessageW(reOutput, WM_GETTEXT, inputStringTerminationPosition, (LPARAM)inputBuffor);
        //SendMessageW(reKey, WM_GETTEXT, keyStringTerminationPosition, (LPARAM)keyBuffor);

        { // PROCESS
            switch (Windows::MainTab::tabState) {

                default:
                case Windows::MainTab::RSA_256: { 
                    RSA::Decrypt(outputData, inputBuffor, inputLength, RSA::RSA256::encodedBlockSizeUint);
                    MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_1, STRING_RESULT, MB_OK);
                } break;

                case Windows::MainTab::RSA_512: {
                    RSA::Decrypt(outputData, inputBuffor, inputLength, RSA::RSA512::encodedBlockSizeUint);
                    MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_2, STRING_RESULT, MB_OK);
                } break;

                case Windows::MainTab::RSA_1024: {
                    RSA::Decrypt(outputData, inputBuffor, inputLength, RSA::RSA1024::encodedBlockSizeUint);
                    MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_3, STRING_RESULT, MB_OK);
                } break;

                case Windows::MainTab::RSA_2048: {
                    RSA::Decrypt(outputData, inputBuffor, inputLength, RSA::RSA2048::encodedBlockSizeUint);
                    MessageBox(windowHandle, L"Succefully Decrypted " STRING_KEY_4, STRING_RESULT, MB_OK);
                }

            }

            //outputBuffor[outputCount] = L'\0';
            SendMessageW(reInput, WM_SETTEXT, NULL, (LPARAM)outputData.data());
        }

        outputData.clear();
        delete[] inputBuffor;
        //delete[] keyBuffor;
    }

    block OnButtonSubmit(
        const HWND& windowHandle
    ) {
        // GET P & Q
        const size qInputLength = SendMessageW(qInput, WM_GETTEXTLENGTH, NULL, NULL);
        const size qInputLengthTerminationPosition = qInputLength + 1;
        const size pInputLength = SendMessageW(pInput, WM_GETTEXTLENGTH, NULL, NULL);
        const size pInputLengthTerminationPosition = pInputLength + 1;

        //wchar* qWchars = new wchar[qInputLengthTerminationPosition];
        //wchar* pWchars = new wchar[pInputLengthTerminationPosition];
        char* qChars = new char[qInputLengthTerminationPosition + 1];
        char* pChars = new char[qInputLengthTerminationPosition + 1];

        // READ INPUT_FIELD DATA
        SendMessageA(qInput, WM_GETTEXT, qInputLengthTerminationPosition, (LPARAM)qChars);
        SendMessageA(pInput, WM_GETTEXT, pInputLengthTerminationPosition, (LPARAM)pChars);

        qChars[qInputLengthTerminationPosition] = '\0';
        pChars[pInputLengthTerminationPosition] = '\0';

        RSA::g_p = pChars;
        RSA::g_q = qChars;

        RSA::Generate(RSA::g_p, RSA::g_q);
    }

    block OnButtonEncodePathPromptClicked (
       IN  const HWND& windowHandle
    ) {
        FileIO::WinAPI::OpenFilePrompt(windowHandle);
        SendMessageW(reInputPath, WM_SETTEXT, NULL, (LPARAM)FileIO::WinAPI::openedFile.lpstrFile);
    }

    block OnButtonDecodePathPromptClicked(
        IN const HWND& windowHandle
    ) {
        FileIO::WinAPI::SaveFilePrompt(windowHandle);
        SendMessageW(reOutputPath, WM_SETTEXT, NULL, (LPARAM)FileIO::WinAPI::openedFile.lpstrFile);
    }

    LRESULT CALLBACK WndProc(
        HWND windowHandle,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    ) {
        switch (message) {

            case WM_NOTIFY: {
                LPNMHDR notyfication((LPNMHDR)lParam);
                if (notyfication->code == TCN_SELCHANGE) {

                    /// Indeks aktualnej kontrolki, Get Current Selected
                    const int index(SendMessage(Windows::MainTab::tabHandle, TCM_GETCURSEL, 0, 0)); 

                    //CHARRANGE cr { 0 };
                    //cr.cpMin = -1;
                    //cr.cpMax = -1;

                    switch (index) {

                        // Could this be optimized ?
                        default:
                        case Windows::MainTab::ID_TAB_0: {
                            SendMessageW(qInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA256::p_str);
                            SendMessageW(pInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA256::q_str);
                            RSA::Generate(RSA::RSA256::p, RSA::RSA256::q);
                            UpdateWindow(qInput);
                            UpdateWindow(pInput);
                            Windows::MainTab::tabState = Windows::MainTab::ID_TAB_0;
                        } break;

                        case Windows::MainTab::ID_TAB_1: {
                            SendMessageW(qInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA512::p_str);
                            SendMessageW(pInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA512::q_str);
                            RSA::Generate(RSA::RSA512::p, RSA::RSA512::q);
                            UpdateWindow(qInput);
                            UpdateWindow(pInput);
                            Windows::MainTab::tabState = Windows::MainTab::ID_TAB_1;
                        } break;

                        case Windows::MainTab::ID_TAB_2: {
                            //SendMessageW(qInput, EM_EXSETSEL, 0, (LPARAM)&cr);
                            //SendMessageW(qInput, EM_REPLACESEL, 0, (LPARAM)RSA::RSA1024::p_str);
                            SendMessageW(qInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA1024::p_str);
                            SendMessageW(pInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA1024::q_str);
                            RSA::Generate(RSA::RSA1024::p, RSA::RSA1024::q);
                            //UpdateWindow(qInput);
                            //UpdateWindow(pInput);
                            Windows::MainTab::tabState = Windows::MainTab::ID_TAB_2;
                        } break;

                        case Windows::MainTab::ID_TAB_3: {
                            SendMessageW(qInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA2048::p_str);
                            SendMessageW(pInput, WM_SETTEXT, NULL, (LPARAM)RSA::RSA2048::q_str);
                            RSA::Generate(RSA::RSA2048::p, RSA::RSA2048::q);
                            UpdateWindow(qInput);
                            UpdateWindow(pInput);
                            Windows::MainTab::tabState = Windows::MainTab::ID_TAB_3;
                        }

                    }
                }
            }

            case WM_COMMAND: {

                int wmId = LOWORD(wParam);
                auto id = (HWND)lParam;

                if (id == buttonEncodePathPrompt) {
                    OnButtonEncodePathPromptClicked(windowHandle);
                } else if (id == buttonDecodePathPrompt) {
                    OnButtonDecodePathPromptClicked(windowHandle);
                } else if (id == buttonEncodePath) {
                    OnButtonEncodePathClicked(windowHandle);
                } else if (id == buttonDecodePath) {
                    OnButtonDecodePathClicked(windowHandle);
                } else if (id == buttonEncode) {
                    OnButtonEncodeClick(windowHandle);
                } else if (id == buttonDecode) {
                    OnButtonDecodeClick(windowHandle);
                } else if (id == buttonSubmit) {
                    OnButtonSubmit(windowHandle);
                }

                switch (wmId) {
                    case IDM_EXIT:
                        DestroyWindow(windowHandle);
                        break;
                    default:
                        return DefWindowProc(windowHandle, message, wParam, lParam);
                }

            } break;

            //case WM_GETTEXTLENGTH: {
            //    //MessageBox(windowHandle, L"Nacisn¹³eœ przycisk!", L"2!", MB_ICONINFORMATION);
            //} break;

            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(windowHandle, &ps);
                EndPaint(windowHandle, &ps);
            } break;

            case WM_DESTROY:
                PostQuitMessage(0);
                break;

            default:
                return DefWindowProc(windowHandle, message, wParam, lParam);
        }

        return 0;
    }
}