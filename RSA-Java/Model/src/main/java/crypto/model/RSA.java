package crypto.model;

import java.math.BigInteger;
import java.util.ArrayList;

public class RSA {

	public enum Type {
		RSA256(0),
		RSA512(1),
		RSA1024(2),
		RSA2048(3);

		private final int value;
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
		public static final int blockSize = 32 - 2;

	}

	public static class RSA512 {
		public static final BigInteger testP = new BigInteger("115792089237316195423570985008687907853269984665640564039457584007913130688523");
		public static final BigInteger testQ = new BigInteger("115792089237316195423570985008687907853269984665640564039457584007914203382263");
		public static final int encryptedBlocksSize = 64;
		public static final int blockSize = 64 - 2;
	}

	public static class RSA1024 {
		public static final BigInteger testP = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171");
		public static final BigInteger testQ = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903");
		public static final int encryptedBlocksSize = 128;
		public static final int blockSize = 128 - 2;
	}

	public static class RSA2048 {
		public static final BigInteger testP = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481");
		public static final BigInteger testQ = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721");
		public static final int encryptedBlocksSize = 256;
		public static final int blockSize = 256 - 2;
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

		ArrayList<BigInteger> nocryptedBlocks = new ArrayList<>();
		ArrayList<BigInteger> encryptedBlocks = new ArrayList<>();
		byte[] blockTemp = new byte[blockSize];
		byte[] blockEncode;

		int blocksCount = nocrypted.length / blockSize;
		int leftCount = nocrypted.length % blockSize;

		{ // Blocks without last one.
			for (int i = 0; i < blocksCount; ++i) {
				for (int j = 0; j < blockSize; ++j) {
					blockTemp[j] = nocrypted[j + (i * blockSize)];
				}
				blockEncode = Numeric.encode(blockTemp); // encode (add 1)
				nocryptedBlocks.add(Numeric.bytesToBigInteger(blockEncode));
			}
		}

		{ // Last Block e.g. LeftCount
			byte[] blockLeft = new byte[leftCount];

			for (int i = 0; i < leftCount; ++i) {
				blockLeft[i] = nocrypted[i + (nocrypted.length - leftCount)];
			}

			blockEncode = Numeric.encode(blockLeft); // encode (add 1)
			nocryptedBlocks.add(Numeric.bytesToBigInteger(blockEncode));
		}


		{ // Encryption
			for (var block : nocryptedBlocks) {
				encryptedBlocks.add(block.modPow(e, n));
			}
		}

		// (Not a BUG) Sometimes it's 33 bytes instead 32 last one is 0 in tests therefore I discard it with (32, 64, 128, 256) iteration loop.
		byte[] result = new byte[encryptedBlocks.size() * encryptedBlockSize], temp;
		for (int i = 0; i < encryptedBlocks.size(); ++i) {
			temp = Numeric.bigIntegerToBytes(encryptedBlocks.get(i)); // Calc-Get

			// THAT'S THE PROBLEM !
			//  results with additional 0es in bytes
			if (temp.length < encryptedBlockSize) {
				byte[] filler = new byte[encryptedBlockSize];
				for (int x = 0; x < temp.length; ++x) {
					filler[x] = temp[x];
				}
				for (int x = temp.length; x < encryptedBlockSize; ++x) {
					filler[x] = 0;
				}
				temp = filler;
			}

			for (int j = 0; j < encryptedBlockSize; ++j) { // Copy
				result[j + (i * encryptedBlockSize)] = temp[j]; // here ?
			}
		}
		
		return result;
	}

	public static byte[] decrypt(final byte[] encrypted, final int blockSize, final int encryptedBlocksSize) {

		ArrayList<BigInteger> encryptedBlocks = new ArrayList<>();
		ArrayList<BigInteger> decryptedBlocks = new ArrayList<>();
		byte[] blockTemp = new byte[encryptedBlocksSize];

		int blocksCount = encrypted.length / encryptedBlocksSize;

		for (int i = 0; i < blocksCount; ++i) {
			for (int j = 0; j < encryptedBlocksSize; ++j) {
				blockTemp[j] = encrypted[j + (i * encryptedBlocksSize)];
			}
			encryptedBlocks.add(Numeric.bytesToBigInteger(Numeric.detectNegative(blockTemp)));
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
				byte[] temp = Numeric.decode(Numeric.bigIntegerToBytes(decryptedBlocks.get(i))); // decode (remove 1)

				results.add(temp);
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

			return result;
		}

	}

}
