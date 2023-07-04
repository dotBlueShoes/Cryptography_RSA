package crypto;

import java.math.BigInteger;

public class Generation {
	private static boolean isPrimeNumber(BigInteger i){
		for( BigInteger j = BigInteger.TWO; j.compareTo(i.divide(BigInteger.TWO)) < 0; j.add(BigInteger.ONE)) {
			if(i.remainder(j).equals(BigInteger.ZERO))
				return false;
		}
		return true;
	}

	public static BigInteger generateE(BigInteger a) {
		for (BigInteger i = a.subtract(BigInteger.ONE); i.compareTo(BigInteger.ONE) > 0; i.subtract(BigInteger.ONE))
			if(isPrimeNumber(i) && (a.remainder(i)).equals(BigInteger.ZERO))
				return i;
		return BigInteger.ONE;
	}

	public static BigInteger generateD(BigInteger a, BigInteger b) {
		for(BigInteger i = BigInteger.ONE; true; i.add(BigInteger.ONE))
			if((((b.multiply(i)).add(BigInteger.ONE)).remainder(a)).equals(BigInteger.ZERO))
				return ((b.multiply(i)).add(BigInteger.ONE)).divide(a);
	}

}
