package crypto.model;

import java.math.BigInteger;

public class Generation {

	public static BigInteger generateE(
		final BigInteger phi,
		final BigInteger min
	) {
		BigInteger e = min;
		while (!e.gcd(phi).equals(BigInteger.ONE)) e = e.add(BigInteger.TWO);
		//if (e >= phi) return ;
		return e;
	}

	public static BigInteger generateD(BigInteger phi, BigInteger e) {
		BigInteger k = BigInteger.ONE;

		while (!((k.multiply(phi)).add(BigInteger.ONE)).mod(e).equals(BigInteger.ZERO)) k = k.add(BigInteger.ONE);
		return ((k.multiply(phi)).add(BigInteger.ONE)).divide(e);
	}

}
