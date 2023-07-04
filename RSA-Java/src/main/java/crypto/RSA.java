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
		e = Generation.generateE(phi);
		d = Generation.generateD(e, phi);
	}

	public static void encrypt() {

	}

	public static void decrypt() {

	}
     public static BigInteger encrypt (BigInteger m) {
         return m.modPow(e,n);
     }

    public static BigInteger dencrypt (BigInteger c) {
        return c.modPow(d,n);
    }

    public BigInteger getE() {
        return e;
    }

    public BigInteger getD() {
        return d;
    }

}
