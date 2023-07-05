package crypto.model;

import java.math.BigInteger;

public class Generation {

	//private static boolean isPrimeNumber(BigInteger i){
	//	for( BigInteger j = BigInteger.TWO; j.compareTo(i.divide(BigInteger.TWO)) < 0; j.add(BigInteger.ONE)) {
	//		if(i.remainder(j).equals(BigInteger.ZERO))
	//			return false;
	//	}
	//	return true;
	//}

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

		// Jeśli nie mamy liczby całkowitej to musimy zwiększać tą liczbę.
		while (!((k.multiply(phi)).add(BigInteger.ONE)).mod(e).equals(BigInteger.ZERO)) k = k.add(BigInteger.ONE);
		return ((k.multiply(phi)).add(BigInteger.ONE)).divide(e);
	}

}
