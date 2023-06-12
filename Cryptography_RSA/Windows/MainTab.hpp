#include "../Framework.hpp"
#include "Windows.hpp"

#include <CommCtrl.h>

namespace Windows {
	namespace MainTab {

		Windows::Handle tabHandle;

		#define STRING_KEY_1 L"256"
		#define STRING_KEY_2 L"512"
		#define STRING_KEY_3 L"1024"
		#define STRING_KEY_4 L"2048"
		
		uint8 tabState = 0;

		/// Must start from 0
		constexpr auto ID_TAB_0 = 0, ID_TAB_1 = 1, ID_TAB_2 = 2, ID_TAB_3 = 3;
		constexpr auto RSA_256 = ID_TAB_0, RSA_512 = ID_TAB_1, RSA_1024 = ID_TAB_2, RSA_2048 = ID_TAB_3;

		const array<const wchar, 8> 
			text1 { L"Key 256" },
			text2 { L"Key 512" };

		const array<const wchar, 9>
			text3 { L"Key 1024" },
			text4 { L"Key 2048" };

		//LRESULT CALLBACK Procedure(
		//	IN Windows::Handle window,
		//	IN UINT message,
		//	IN WPARAM wArgument,
		//	IN LPARAM lArgument
		//) {
		//	switch (message) {
		//
		//		//case WM_CREATE: {
		//		//	DEBUG logger::Info("(CALL) Window-Left:Event-Create");
		//		//	return proceeded::True;
		//		//}
		//
		//		case WM_NOTIFY: {
		//			LPNMHDR notyfication((LPNMHDR)lArgument);
		//			MessageBox(nullptr, L"Z", L"TITLE", MB_OK);
		//			if (notyfication->code == TCN_SELCHANGE) {
		//				//if (notyfication->hwndFrom == tabHandle) { /// Sprawdza, czy uchwyt pochodzi od tabHandle
		//				const int index(SendMessage(tabHandle, TCM_GETCURSEL, 0, 0)); /// Indeks aktualnej kontrolki, Get Current Selected
		//				switch (index) {
		//
		//					default:
		//					case ID_TAB_0: {
		//						MessageBox(nullptr, L"A", L"TITLE", MB_OK);
		//						tabState = 0;
		//					} break;
		//
		//					case ID_TAB_1: {
		//						MessageBox(nullptr, L"B", L"TITLE", MB_OK);
		//						tabState = 1;
		//					} break;
		//
		//					case ID_TAB_2: {
		//						MessageBox(nullptr, L"C", L"TITLE", MB_OK);
		//						tabState = 2;
		//					}
		//
		//				}
		//			}
		//		}
		//
		//		//		} else if (notyfication->hwndFrom == innerTab) {
		//		//			const int index(SendMessage(innerTab, TCM_GETCURSEL, 0, 0)); /// Indeks aktualnej kontrolki, Get Current Selected
		//		//			switch (index) {
		//		//				case ID_TAB_I_0:
		//		//					DEBUG logger::Info("(TABEVENT) ID_TAB_I_0");
		//		//					//ShowWindow( hEdit, SW_SHOW );
		//		//					//ShowWindow( hRadioButton, SW_HIDE );
		//		//					break;
		//		//				case ID_TAB_I_1:
		//		//					DEBUG logger::Info("(TABEVENT) ID_TAB_I_1");
		//		//					//ShowWindow( hEdit, SW_HIDE );
		//		//					//ShowWindow( hRadioButton, SW_SHOW );
		//		//					break;
		//		//					//itd.
		//		//				case ID_TAB_I_2:
		//		//					DEBUG logger::Info("(TABEVENT) ID_TAB_I_2");
		//		//					//ShowWindow( hEdit, SW_SHOW );
		//		//					//ShowWindow( hRadioButton, SW_HIDE );
		//		//					break;
		//		//				case ID_TAB_I_3:
		//		//					DEBUG logger::Info("(TABEVENT) ID_TAB_I_3");
		//		//					//ShowWindow( hEdit, SW_HIDE );
		//		//					//ShowWindow( hRadioButton, SW_SHOW );
		//		//					break;
		//		//					//itd.
		//		//			}
		//		//		}
		//		//	}
		//		//	return 0;
		//		//}
		//
		//		default:
		//			return DefWindowProcW(window, (uint32)message, wArgument, lArgument);
		//	}
		//}

		block Create (
			OUT Windows::Handle& tab,
			IN const Windows::Handle& window,
			IN const Windows::Process& process,
			IN const pair<int32>& position,
			IN const pair<int32>& area
		) {
			tab = CreateWindowExW(0, WC_TABCONTROLW, 0, WS_CHILD | WS_VISIBLE /*|TCS_FIXEDWIDTH*/,
				position.x, position.y, area.x, area.y, window, 0, process, NULL);

			// ERROR HANDLING
			//DEBUG if (hTab == NULL) logger::Error("Window not created!");

			/// For fixedwidth to set the fixedwidth
				//SendMessage(hTab, TCM_SETITEMSIZE, 0, MAKELPARAM(150, 20));

			TCITEMW tabItem1, tabItem2, tabItem3, tabItem4;

			tabItem1.mask = TCIF_TEXT;
			tabItem2.mask = TCIF_TEXT;
			tabItem3.mask = TCIF_TEXT;
			tabItem4.mask = TCIF_TEXT;
			tabItem1.pszText = (LPWSTR)text1.data();
			tabItem2.pszText = (LPWSTR)text2.data();
			tabItem3.pszText = (LPWSTR)text3.data();
			tabItem4.pszText = (LPWSTR)text4.data();
			tabItem1.cchTextMax = text1.size();
			tabItem2.cchTextMax = text2.size();
			tabItem3.cchTextMax = text3.size();
			tabItem3.cchTextMax = text4.size();

			SendMessage(tab, TCM_INSERTITEMW, (WPARAM)ID_TAB_0, (LPARAM)(const TC_ITEMW*)(&tabItem1));
			SendMessage(tab, TCM_INSERTITEMW, (WPARAM)ID_TAB_1, (LPARAM)(const TC_ITEMW*)(&tabItem2));
			SendMessage(tab, TCM_INSERTITEMW, (WPARAM)ID_TAB_2, (LPARAM)(const TC_ITEMW*)(&tabItem3));
			SendMessage(tab, TCM_INSERTITEMW, (WPARAM)ID_TAB_3, (LPARAM)(const TC_ITEMW*)(&tabItem4));
		}

	}
}