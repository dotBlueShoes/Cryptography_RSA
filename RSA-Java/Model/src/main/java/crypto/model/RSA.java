package crypto.model;

import java.math.BigInteger;
import java.util.ArrayList;

public class RSA {

	public enum Type {
		RSA256(0),
		RSA512(1),
		RSA1024(2),
		RSA2048(3);

		private int value;
		Type(int value) {
			this.value = value;
		}
		public int getValue() {
			return value;
		}
	}

	public static class RSA256 {
		public static final BigInteger testP = new BigInteger("340282366920938463463374607432841953291");
		public static final BigInteger testQ = new BigInteger("340282366920938463463374607431768212629");

		public static final int encryptedBlocksSize = 32; // 32 * 8 = 256
		public static final int blockSize = 32 - 1;

	}

	public static class RSA512 {
		public static final BigInteger testP = new BigInteger("115792089237316195423570985008687907853269984665640564039457584007913130688523");
		public static final BigInteger testQ = new BigInteger("115792089237316195423570985008687907853269984665640564039457584007914203382263");
		public static final int encryptedBlocksSize = 64;
		public static final int blockSize = 64 - 1;
	}

	public static class RSA1024 {
		public static final BigInteger testP = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171");
		public static final BigInteger testQ = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903");
		public static final int encryptedBlocksSize = 128;
		public static final int blockSize = 128 - 1;
	}

	public static class RSA2048 {
		public static final BigInteger testP = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481");
		public static final BigInteger testQ = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721");
		public static final int encryptedBlocksSize = 256;
		public static final int blockSize = 256;
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

	public static BigInteger bytesToBigInteger(final byte[] bytes) {
		byte[] formatted = new byte[bytes.length + 1];
		final int lastElement = formatted.length - 1;

		for (int i = 0, j = lastElement; j > 0; i++, j--)
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

	public static BigInteger p, q, n, phi, e, d;

	public static void initialize(final BigInteger newP, final BigInteger newQ) {
		final BigInteger minE = new BigInteger("65537");
		p = newP;
		q = newQ;
		n = p.multiply(q);
		phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));
		e = Generation.generateE(phi, minE);
		d = Generation.generateD(phi, e);
	}

	public static byte[] encrypt(byte[] nocrypted, int blockSize, int encryptedBlockSize) {

		// 1.
		//  Construct a single block from data
		//  Encrypt it and send

		ArrayList<BigInteger> nocryptedBlocks = new ArrayList<>();
		ArrayList<BigInteger> encryptedBlocks = new ArrayList<>();
		byte[] blockTemp = new byte[blockSize + 1];

		int blocksCount = nocrypted.length / blockSize;
		int leftCount = nocrypted.length % blockSize;

		{ // Blocks without last one.
			for (int i = 0; i < blocksCount; ++i) {
				for (int j = 0; j < blockSize; ++j) {
					blockTemp[j] = nocrypted[j + (i * blockSize)];
				}
				nocryptedBlocks.add(bytesToBigInteger(blockTemp));
			}
		}

		{ // Last Block e.g. LeftCount
			byte[] blockLeft = new byte[leftCount];

			for (int i = 0; i < leftCount; ++i) {
				blockLeft[i] = nocrypted[i + (nocrypted.length - leftCount)];
			}

			//block = bytesToBigInteger(blockLeft);
			nocryptedBlocks.add(bytesToBigInteger(blockLeft));
		}


		{ // Encryption
			//encoded = block.modPow(e, n);
			for (var block : nocryptedBlocks) {
				encryptedBlocks.add(block.modPow(e, n));
			}
		}

		// BUG? Sometimes it's 33 bytes instead 32 last one is 0 in tests therefore I discard it with (32, 64, 128, 256) iteration loop.
		byte[] result = new byte[encryptedBlocks.size() * encryptedBlockSize], temp;
		for (int i = 0; i < encryptedBlocks.size(); ++i) {
			temp = RSA.bigIntegerToBytes(encryptedBlocks.get(i)); // Calc-Get

			// THAT'S THE PROBLEM !
			//  results with additional 0es in bytes
			if (temp.length < 32) {
				byte[] filler = new byte[encryptedBlockSize];
				for (int x = 0; x < temp.length; ++x) {
					filler[x] = temp[x];
				}
				for (int x = temp.length; x < encryptedBlockSize; ++x) {
					filler[x] = 0;
				}
				temp = filler;
				//break;
			}

			// !@#!@%@!#^#$&#$^asdfasgasdgaż ź ćżzżććczxcżźćżććxzc€ó€ó€ó€asąśąśasdadasd!@#!@#!@#!@#!@#
			// !@#!@%@!#^#$&#$^asdfasgasdgaż��ćżzżććczxcżźćżććxzc€ó€ó€ó€asąśąśasdadasd!@#!@#!@#!@#!@#

			//1 // THAT'S THE PROBLEM !
			//1 // Adding zeroes at begin results with different numbers
			//1 if (temp.length < 32) {
			//1 	byte[] filler = new byte[encryptedBlockSize];
			//1 	final int difference = encryptedBlockSize - temp.length;
			//1 	for (int x = 0; x < difference; ++x) {
			//1 		filler[x] = 0;
			//1 	}
			//1 	for (int x = 0; x < temp.length; ++x) {
			//1 		filler[difference + x] = temp[x];
			//1 	}
			//1 	temp = filler;
			//1 }

			for (int j = 0; j < encryptedBlockSize; ++j) { // Copy
				result[j + (i * encryptedBlockSize)] = temp[j]; // here ?
			}
		}

		//System.out.print(encryptedBlocks.get(0));
		//byte[] result = RSA.bigIntegerToBytes(encryptedBlocks.get(0));

		//{ // TEST1
		//	byte[] sample = new byte[result.length - 1];
		//	for (int i = 0; i < sample.length; ++i) {
		//		sample[i] = result[i];
		//	}
		//	BigInteger rsample = bytesToBigInteger(sample);
		//	System.out.print(rsample);
		//}

		// !@#!%$!%$!@$!@$!@ - 33 its negation 0 is being placed last if last one has 1000'0000 set on it.
		// asdasd - 32
		
		// therefore I need to remove that byte inside bigIntegerToBytes right ?
		
		return result;
	}

	public static byte[] decrypt(final byte[] encrypted, final int blockSize, final int encryptedBlocksSize) {

		// 1.
		//  Construct a single block from data
		//  Decrypt it and send

		//byte[] blockTemp = new byte[blockSize];
		//BigInteger block, decoded;
		//block = bytesToBigInteger(encrypted);

		ArrayList<BigInteger> encryptedBlocks = new ArrayList<>();
		ArrayList<BigInteger> decryptedBlocks = new ArrayList<>();
		byte[] blockTemp = new byte[encryptedBlocksSize];

		int blocksCount = encrypted.length / encryptedBlocksSize;

		for (int i = 0; i < blocksCount; ++i) {
			for (int j = 0; j < encryptedBlocksSize; ++j) {
				blockTemp[j] = encrypted[j + (i * encryptedBlocksSize)];
			}
			encryptedBlocks.add(bytesToBigInteger(blockTemp));
		}

		{ // Decryption
			for (var block : encryptedBlocks) {
				decryptedBlocks.add(block.modPow(d, n));
			}
		}

		{ // list<byte[]> to byte[]
			ArrayList<byte[]> results = new ArrayList<>();
			int resultLength = 0;

			for (int i = 0; i < decryptedBlocks.size(); ++i) {
				results.add(RSA.bigIntegerToBytes(decryptedBlocks.get(i)));
				resultLength += results.get(i).length; // that's quite stupid, isn't it ?
			}

			byte[] result = new byte[resultLength];
			int currentElementIndex = 0;

			for (int i = 0; i < results.size(); ++i) {

				for (int j = 0; j < results.get(i).length; ++j) {
					result[j + currentElementIndex] = results.get(i)[j];
				}
				currentElementIndex += results.get(i).length;
			}

			//byte[] result = new byte[decryptedBlocks.size() * encryptedBlockSize], temp;
			//byte[] temp = RSA.bigIntegerToBytes(decryptedBlocks.get(0));

			// !@#!@#!@%!%!#$!@#$!@#!@$!@$!@$!@$!@$!@$!@$ASFASFASGFASFASVFASFASfasfasfasfasfasfa
			// !@#!@#!@%!%!#$!@#$!@#!@$!@$!@$! !@#!@#!@ %!%!#$!@#$!@#!@$!@$!@$!!@#!@#!@%!%!#$!@#$!

			// !@#!@#!@%!%!#$!@#$!@#!@$@$ASFASFASGFASFASVFASFASfasfasfasfasfasfa
			// !@#!@#!@%!%!#$!@#$!@#!@$@$ASFAS!@#!@#!@%!%!#$!@#$!@#!@$@$ASFAS!@#

			return result;
		}

	}

	//public static BigInteger encrypt (BigInteger m) {
	// return m.modPow(e,n);
	// }

    //public static BigInteger decrypt (BigInteger c) {
    //    return c.modPow(d,n);
    //}

    //public BigInteger getE() {
    //    return e;
    //}

    //public BigInteger getD() {
    //    return d;
    //}

}
