#include "Framework.hpp"
#include "Windows/Window.hpp"

#include "RSA/main.hpp"

// Globals
const wchar 
    classNameMainWindow[] = L"RSAMainWindow",
    titleMainWindow[] = L"RSA 242422 242539";

int32 APIENTRY wWinMain (
    IN          HINSTANCE process,
    IN OPTIONAL HINSTANCE parentProcess,
    IN          LPWSTR    lpCmdLine,
    IN          int32     nCmdShow
) {

    UNREFERENCED_PARAMETER(parentProcess);
    UNREFERENCED_PARAMETER(lpCmdLine);

    { // Dynamic Library Loading.
        Window::LoadRichEdit();
    }

    { // Window Creation.
        const pair<int32> windowPosition { CW_USEDEFAULT, 0 }, windowArea { 1000, 600 };

        // RSA FIRST !!!
        RSA::Generate(RSA::RSA256::p, RSA::RSA256::q);

        Window::MyRegisterClass(process, classNameMainWindow);
        if (!Window::InitInstance(process, nCmdShow, classNameMainWindow, titleMainWindow, windowPosition, windowArea)) return FALSE;

        //// find the biggest probable prime less than 10^42
        //// Num p = Num(10).pow(42) - 1;

        // INPUT SIMULATION 
        //std::vector<wchar_t> inputData; // 16bit datatype
        //std::wstring inputData = L"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012312"; // 124 signs
        //std::wstring inputData = L"Text"; // 32 znaki - 64bytes = 64 * 8 = 512
        //std::wstring inputData = L"1234567890";
        //std::wstring inputData = L"TextTextTe";
        //std::wstring inputData = L"!@!@^%@&$*(@#%@QRT%Q#^#$*%^(&*_()+()_+P{}P|/O}OPPUITYDHHNBC VMVB<CVNXVZVASV@#!$%@#^%@#^&@$YW#$%*#$%^(*@TZSDSDGDSAAAAG";

        //std::wstring inputData = L"!@#$";

        //{ // WSTRING <=> UINT64 with 0'es TEST
        //    std::vector<Num::word> words; // Empty container for processed words to use in NUM creation.
        //    std::vector<WBuffor> results; // Empty containter for processed wstrings ready to write.
        //    //const wchar encodedData[] = L"184467440737095516151844674407370955161518446744073709551615";
        //    const wchar encodedData[] = L"000000000737095516151844674407370955161518446744073709551615";
        //    const size encodedDataSize = 60;
        //    wchar* data = nullptr;
        //    size dataSize = 0;
        //
        //    WstringToUint64s(words, encodedData, encodedDataSize);
        //    Uint64sToWstring(results, words);
        //
        //    words.clear();
        //
        //    // Num number(words.begin()._Ptr, words.end()._Ptr);
        //
        //    { // GET LENGTH;
        //        const size length = wBufforLength * results.size();
        //        dataSize = length + 1;
        //        data = new wchar[dataSize];
        //    }
        //
        //    WstringsToWstring(data, dataSize, results);
        //    WstringToUint64s(words, data, dataSize - 1);
        //    delete[] data;
        //}

        //{ // 256
        //    RSA::Generate(RSA::RSA256::p, RSA::RSA256::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA256::blockSizeWchar, RSA::RSA256::blockSizeUint, RSA::RSA256::encodedBlockSizeUint);
        //}
        //
        //{ // 512
        //    RSA::Generate(RSA::RSA512::p, RSA::RSA512::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA512::blockSizeWchar, RSA::RSA512::blockSizeUint, RSA::RSA512::encodedBlockSizeUint);
        //}
        //
        //{ // 1024
        //    RSA::Generate(RSA::RSA1024::p, RSA::RSA1024::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA1024::blockSizeWchar, RSA::RSA1024::blockSizeUint, RSA::RSA1024::encodedBlockSizeUint);
        //}
        //
        //{ // 2048
        //    RSA::Generate(RSA::RSA2048::p, RSA::RSA2048::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA2048::blockSizeWchar, RSA::RSA2048::blockSizeUint, RSA::RSA2048::encodedBlockSizeUint);
        //}

        //{ // 256
        //    RSA::Generate(RSA::RSA256::p, RSA::RSA256::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA256::blockSizeWchar, RSA::RSA256::blockSizeUint, RSA::RSA256::encodedBlockSizeUint);
        //}
        //
        //{ // 512
        //    RSA::Generate(RSA::RSA512::p, RSA::RSA512::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA512::blockSizeWchar, RSA::RSA512::blockSizeUint, RSA::RSA512::encodedBlockSizeUint);
        //}
        //
        //{ // 1024
        //    RSA::Generate(RSA::RSA1024::p, RSA::RSA1024::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA1024::blockSizeWchar, RSA::RSA1024::blockSizeUint, RSA::RSA1024::encodedBlockSizeUint);
        //}
        //
        //{ // 2048
        //    RSA::Generate(RSA::RSA2048::p, RSA::RSA2048::q);
        //    RSA::Test4(inputData.data(), inputData.length(), RSA::RSA2048::blockSizeWchar, RSA::RSA2048::blockSizeUint, RSA::RSA2048::encodedBlockSizeUint);
        //}
        
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}