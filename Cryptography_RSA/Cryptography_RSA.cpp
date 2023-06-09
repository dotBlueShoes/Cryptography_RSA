﻿#include "inc/Framework.hpp"
#include "inc/Window.hpp"
#include "inc/AES/main.hpp"
#include "inc/RSA/Test.hpp"

// Globals
const wchar classNameMainWindow[] = L"MainWindow",
titleMainWindow[] = L"RSA 242422 242539";

int32 APIENTRY wWinMain(
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

        {
            Tests::Key32();

            //const uint8 mask = 0b0000'1111;
            //std::string temp = "";
            //uint8 sample = 0b1111'0001;
            //char s1 = sample >> 4;
            //
            //if (s1 > 9) { // '9'
            //    s1 += ('A' - 10); // 'a'
            //} else {
            //    s1 += '0';
            //}
            //temp += s1;
            //
            //s1 = sample & mask;
            //
            //if (s1 > 9) { // '9'
            //    s1 += ('A' - 10); // 'a'
            //} else {
            //    s1 += '0';
            //}
            //temp += s1;
            //
            //temp += '\n';
            //
            //MessageBoxA(nullptr, temp.c_str(), "CORRECT", MB_OK);
        }

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

    return (int)msg.wParam;
}