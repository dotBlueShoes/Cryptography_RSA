package crypto.model;

import java.math.BigInteger;

public class Numeric {

	// Problem View
	// BigInteger implementation supports negative numbers.
	//  Big Integer is negative when the 1st bit in 1st byte is set.
	//  e.g. 0b1000'0000'0000'0000'0000'0000'0000'0000 is negative
	// Problems
	//  1. Problem. (byte[] to BigInteger to byte[])
	//   Required is special encoding which would force negative numbers.
	//  2. Problem. (number changes its size in bytes in modulo operations)
	//   Normally a number would fit in unsigned format in the same amount of bytes
	//    however here to make the representation correct a 0-byte is being added at the very end.


	// I am adding 0 at the end when BigInteger is negative ....
	//  this leads to some bigIntegers having 0 as first byte and some not.
	//  some might have a zero there by default
	//  I need to differentiate between those 2.
	// It seems that I need something like:

	//  bytes -> bigInteger(encrypted) -> bytes -> bigInteger(decrypted) -> bytes
	//  bytes -> encoding -> bigInteger(encrypted) -> bytes -> bigInteger(decrypted) -> decoding -> bytes

	// algorithm:
	// bytes -> bytes(encoded) (number of added 0'es)
	// bytes(encoded) -> bigInteger
	// bigInteger -> bigInteger(encrypted)
	// bigInteger(encrypted) -> bigInteger(exceeding-0-cut)
	// bigInteger(exceeding-0-cut) -> bytes
	// bytes -> bigInteger(add-0-cut)
	// bigInteger(add-0-cut) -> bigInteger(decrypted)
	// bigInteger(decrypted) -> bytes(encoded)
	// bytes(encoded) -> bytes

	// 1. I cannot remove any bytes during bigInteger -> bytes transformation !

	// Added 1 at the end so 0 bytes are not removed
	public static byte[] encode(final byte[] data) {
		byte[] temp = new byte[data.length + 1];

		for (int i = 0; i < data.length; ++i) {
			temp[i] = data[i];
		}

		temp[data.length] = 1;


		return temp;
	}

	// Removed prev. added 1 so we're back to normal.
	public static byte[] decode(final byte[] data) {
		byte[] temp = new byte[data.length - 1];

		for (int i = 0; i < temp.length; ++i) {
			temp[i] = data[i];
		}

		return temp;
	}

	public static byte[] bigIntegerToBytes(final BigInteger value) {
		byte[] bytes = value.toByteArray();

		byte[] result = new byte[bytes.length];
		final int lastElement = result.length - 1;

		for (int i = 0, j = lastElement; i < result.length; i++, j--)
			result[j] = bytes[i];

		{ // DEBUG
			String temp = "\n\nAfter: ";
			temp += result[0];
			for (int i = 1; i < result.length; ++i) {
				temp += ", ";
				temp += result[i];
			}
			temp += "\n\n";
			System.out.print(temp);
		}

		return result;
	}

	public static byte[] detectNegative(final byte[] bytes) {
		final int lastElement = bytes.length - 1;
		byte[] formatted;

		if ((bytes[lastElement] & 0b10000000) > 0) {
			formatted = new byte[bytes.length + 1];
			formatted[bytes.length] = 0;

			for (int i = 0; i < bytes.length; ++i) {
				formatted[i] = bytes[i];
			}

		} else {
			formatted = bytes;
		}

		return formatted;

	}

	public static BigInteger bytesToBigInteger(final byte[] bytes, boolean detectNegative) {
		byte[] formatted = new byte[bytes.length];

		//if (detectNegative && (bytes[0] & 0b10000000) > 0) {
		//	formatted = new byte[bytes.length + 1];
		//	formatted[0] = 0;
		//
		//} else {
		//	formatted = new byte[bytes.length];
		//
		//}

		final int lastElement = formatted.length - 1;

		for (int i = 0, j = lastElement; i < bytes.length; i++, j--)
			formatted[j] = bytes[i];

		{ // DEBUG
			String temp = "\n\nBefore: ";
			temp += formatted[0];
			for (int i = 1; i < formatted.length; ++i) {
				temp += ", ";
				temp += formatted[i];
			}
			temp += "\n\n";
			System.out.print(temp);
		}

		return new BigInteger(formatted);
	}

}
