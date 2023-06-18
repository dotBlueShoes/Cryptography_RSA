#pragma once
#include "../Framework.hpp"

const size wBufforLength = 20;
using WBuffor = std::array<wchar, wBufforLength + 1>;

block WstringsToWstring(
	OUT wchar* result,
	OUT size& resultLength,
	IN const std::vector<WBuffor>& strings
) {
	for (size i = 0; i < strings.size(); ++i) {
		for (size j = 0; j < wBufforLength; ++j) {
			result[j + (i * wBufforLength)] = strings[i][j];
		}
	}

	result[resultLength - 1] = L'\0';
}

block Uint64sToWstring(
	OUT std::vector<WBuffor>& results,
	IN const std::vector<uint64>& words
) {
	int written = 0;

	for (size i = 0; i < words.size(); ++i) {
		WBuffor buffor { 0 }, zeroesBuffor { 0 }; // 1 extra for null-terminator.

		written = swprintf(buffor.data(), buffor.size(), L"%llu", words[i]);

		// FORCE 0es to appear at the begin - 00001234.
		const int zeroes = wBufforLength - written;
		if (zeroes) {
			for (size j = 0; j < zeroes; ++j) {
				zeroesBuffor[j] = L'0';
			}

			for (size j = 0; j < written; ++j) {
				zeroesBuffor[zeroes + j] = buffor[j];
			}
			buffor = zeroesBuffor;
		}

		results.push_back(buffor);
	}

	//results.size();
}

block WstringToUint64s(
	OUT std::vector<uint64>& words,
	IN const wchar* encodedData,
	IN const size& encodedDataSize
) {
	wchar* end;

	const uint64 packets = encodedDataSize / wBufforLength;
	const uint64 left = encodedDataSize % wBufforLength;

	for (size i = 0; i < packets; ++i) {

		WBuffor buffor { 0 };

		// Copy To buffor
		for (size j = 0; j < wBufforLength; ++j) {
			buffor[j] = encodedData[(i * wBufforLength) + j];
		}

		uint64 result = wcstoull(buffor.data(), &end, 10);
		words.push_back(result);

	}

	//words.size();

}