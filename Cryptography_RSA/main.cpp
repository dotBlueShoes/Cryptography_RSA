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

        Window::MyRegisterClass(process, classNameMainWindow);
        if (!Window::InitInstance(process, nCmdShow, classNameMainWindow, titleMainWindow, windowPosition, windowArea)) return FALSE;

        // INPUT SIMULATION 
        //std::vector<wchar_t> inputData; // 16bit datatype
        std::wstring inputData = L"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012312"; // 124 signs
        //std::wstring inputData = L"Text"; // 32 znaki - 64bytes = 64 * 8 = 512
        //std::wstring inputData = L"1234567890";

        { // WSTRING <=> UINT64 with 0'es TEST
            std::vector<Num::word> words; // Empty container for processed words to use in NUM creation.
            std::vector<RSA::WBuffor> results; // Empty containter for processed wstrings ready to write.
            //const wchar encodedData[] = L"184467440737095516151844674407370955161518446744073709551615";
            const wchar encodedData[] = L"000000000737095516151844674407370955161518446744073709551615";
            const size encodedDataSize = 60;
            wchar* data = nullptr;
            size dataSize = 0;

            RSA::WstringToUint64s(words, encodedData, encodedDataSize);
            RSA::Uint64sToWstring(results, words);

            words.clear();

            { // GET LENGTH;
                const size length = RSA::wBufforLength * results.size();
                dataSize = length + 1;
                data = new wchar[dataSize];
            }

            RSA::WstringsToWstring(data, dataSize, results);
            RSA::WstringToUint64s(words, data, dataSize - 1);
            delete[] data;
        }

        { // 256
            RSA::Generate(RSA::RSA256::p, RSA::RSA256::q);
            RSA::Test4(inputData.data(), inputData.length(), RSA::RSA256::blockSizeWchar, RSA::RSA256::blockSizeUint);
        }

        { // 512
            RSA::Generate(RSA::RSA512::p, RSA::RSA512::q);
            RSA::Test4(inputData.data(), inputData.length(), RSA::RSA512::blockSizeWchar, RSA::RSA512::blockSizeUint);
        }

        { // 1024
            RSA::Generate(RSA::RSA1024::p, RSA::RSA1024::q);
            RSA::Test4(inputData.data(), inputData.length(), RSA::RSA1024::blockSizeWchar, RSA::RSA1024::blockSizeUint);
        }

        { // 2048
            RSA::Generate(RSA::RSA2048::p, RSA::RSA2048::q);
            RSA::Test4(inputData.data(), inputData.length(), RSA::RSA2048::blockSizeWchar, RSA::RSA2048::blockSizeUint);
        }
       
        //RSA::BigIntTest();

        /* { // TESTS

            //{ // Single Block

            const AES::Key128 testKey {
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x09, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f
            };
                const AES::Block nocoded {
                    0x00, 0x11, 0x22, 0x33,
                    0x44, 0x55, 0x66, 0x77,
                    0x88, 0x99, 0xaa, 0xbb,
                    0xcc, 0xdd, 0xee, 0xff
                };
                
                Tests::WcharByteTest();
                Tests::Test128(testKey, nocoded);
                //Tests::Test192(AES::TEST::Key192::sample1, nocoded);
                //Tests::Test256(AES::TEST::Key256::sample1, nocoded);
            //}

            // No encoding decoding.
            //Tests::ReadWriteTest();

            { // FILE
                //const wchar* const nocodedFilePath = LR"(data/kryptoTest.pdf)";
                //const wchar* const encodedFilePath = LR"(data/aaa.pdf)";
                //const wchar* const decodedFilePath = LR"(data/bbb.pdf)";
                const wchar* const nocodedFilePath = LR"(data/1.txt)";
                const wchar* const encodedFilePath = LR"(data/2.txt)";
                const wchar* const decodedFilePath = LR"(data/3.txt)";
                uint8 extraBytes;
                //AES::ReadEncodeWrite<AES::Key128>(extraBytes, nocodedFilePath, encodedFilePath, AES::TEST::Key128::sample1);
                //AES::ReadDecodeWrite<AES::Key128>(encodedFilePath, decodedFilePath, AES::TEST::Key128::sample1, extraBytes);
                //AES::ReadEncodeWrite<AES::Key192>(extraBytes, nocodedFilePath, encodedFilePath, AES::TEST::Key192::sample1);
                //AES::ReadDecodeWrite<AES::Key192>(encodedFilePath, decodedFilePath, AES::TEST::Key192::sample1, extraBytes);
                AES::ReadEncodeWrite<AES::Key256>(extraBytes, nocodedFilePath, encodedFilePath, AES::TEST::Key256::sample1);
                AES::ReadDecodeWrite<AES::Key256>(encodedFilePath, decodedFilePath, AES::TEST::Key256::sample1, extraBytes);
            }
            
        }*/
        
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}