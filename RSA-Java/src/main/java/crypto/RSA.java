package crypto;

import java.math.BigInteger;

public class RSA {

	// Bytes to BigInt
	// BigInt to Bytes
	// encryption, decryption tests

	static BigInteger p, q, n, phi, e, d;

	public static void initialize(final BigInteger p, final BigInteger q) {
		n = p.multiply(q);
		phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));
		e = Generation.generateE(phi, n);
		d = Generation.generateD(e, phi);
	}

	public static void encrypt() {

	}

	public static void decrypt() {

	}

}
