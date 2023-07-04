import org.junit.Test;

import java.math.BigInteger;
import java.nio.ByteBuffer;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class BigIntegerTest {

	@Test
	public void signumTest() {
		// Determines the sign of the BigInteger.
		assertEquals(1, BigInteger.TEN.signum());
		assertEquals(-1, BigInteger.TEN.negate().signum());
		assertEquals(0, BigInteger.ZERO.signum());
	}

	@Test
	public void magTest() {
		// Mag property stores the given value in an array using the binary representation.
		//  Groups them in 32-bit portions – a set of four bytes.
		//  - big-endian notation - The zeroth element of this array is the most significant int of the magnitude.
		assertEquals(new BigInteger("1"), new BigInteger(new byte[]{0b1}));
		assertEquals(new BigInteger("2"), new BigInteger(new byte[]{0b10}));
		assertEquals(new BigInteger("4"), new BigInteger(new byte[]{0b100}));
	}

	@Test
	public void negativeTest() {
		byte[] bytes = { -128 }; // 1000 0000
		assertEquals(new BigInteger("128"), new BigInteger(1, bytes));
		assertEquals(new BigInteger("-128"), new BigInteger(-1, bytes));

		//assertEquals("10000000", new BigInteger(1, bytes));
		//assertEquals("-10000000", new BigInteger(-1, bytes));
	}

	@Test
	public void sample() {
		BigInteger bi1 = BigInteger.ZERO.setBit(63);
		String str = bi1.toString(2);

		assertEquals(64, bi1.bitLength());
		assertEquals(1, bi1.signum());
		assertEquals("9223372036854775808", bi1.toString());
		assertEquals(BigInteger.ONE, bi1.subtract(BigInteger.valueOf(Long.MAX_VALUE)));

		assertEquals(64, str.length());
		assertTrue(str.matches("^10{63}$")); // 1000 0000 ... 0000

		{
			byte[] bytes = ByteBuffer.allocate(Long.BYTES).putLong(Long.MIN_VALUE).array();
			BigInteger bi2 = new BigInteger(1, bytes);
			assertEquals(bi1, bi2);
		}

	}

	@Test
	public void BigIntegerAdd() {
		BigInteger testSubject1 = new BigInteger("100000000000000000000000000000000000000000000000");
		BigInteger testSubject2 = new BigInteger("911111111111111111111111111111111111111111111111");
		BigInteger result = new BigInteger("1011111111111111111111111111111111111111111111111");

		assertEquals(result, testSubject1.add(testSubject2));
	}

	@Test
	public void BigIntegerSubtract() {
		BigInteger testSubject1 = new BigInteger("100000000000000000000000000000000000000000000000");
		BigInteger testSubject2 = new BigInteger("911111111111111111111111111111111111111111111111");
		BigInteger result = new BigInteger("811111111111111111111111111111111111111111111111");

		assertEquals(result, testSubject2.subtract(testSubject1));
	}

	@Test
	public void BigIntegerPowerMod() {
		BigInteger testSubject1 = new BigInteger("100000000000000000000000000000000000000000000000");
		BigInteger power = new BigInteger("911111111111111111111111111111111111111111111111");
		BigInteger mod = new BigInteger("67345623512356236236236236326326");
		BigInteger result = new BigInteger("59684624648632765396744309710582");

		assertEquals(result, testSubject1.modPow(power, mod));
	}

	@Test
	public void BigIntegerRSA256() {
		BigInteger nocrypted = new BigInteger("1234567890");
		BigInteger e = new BigInteger("65537");
		BigInteger d = new BigInteger("45873717212531511939478417607993338985203698332816772336676580002019942742113");
		BigInteger n = new BigInteger("115792089237316195423570985009053283665497032829582625988272189963300174312039");

		BigInteger decrypted = nocrypted.modPow(e, n);
		BigInteger encrypted = decrypted.modPow(d, n);

		assertEquals(nocrypted, encrypted);
	}

	@Test
	public void BigIntegerRSA512() {
		BigInteger nocrypted = new BigInteger("1234567890");
		BigInteger e = new BigInteger("65537");
		BigInteger d = new BigInteger("8489613587268687181912863197133649644506328386363772342270696388759436751032861808964060572265447244996842177801457597349277095013769073113413927469687357");
		BigInteger n = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721888482358972321438460600643024795664454222011193600659973326960726666683397868555867549");

		BigInteger decrypted = nocrypted.modPow(e, n);
		BigInteger encrypted = decrypted.modPow(d, n);

		assertEquals(nocrypted, encrypted);
	}

	@Test
	public void BigIntegerRSA1024() {
		BigInteger nocrypted = new BigInteger("1234567890");
		BigInteger e = new BigInteger("65537");
		BigInteger d = new BigInteger("26176641570396998195615849727176500347767450920924716760918920067873764823105965960837954118860111330234054759229331626594714905531165262804968842497012474034054790820638299120595992598571920651701491040486136142817809429758760763166627688815013139671917041615651170694672711273767841382650445691318757317733");
		BigInteger n = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430653537332774941944555860887764470363899128906300087673702898450343051921981734064981595816628150725238205726506162944160231534326050039858483390574966423801578413");

		BigInteger decrypted = nocrypted.modPow(e, n);
		BigInteger encrypted = decrypted.modPow(d, n);

		assertEquals(nocrypted, encrypted);
	}

	@Test
	public void BigIntegerRSA2048() {
		BigInteger nocrypted = new BigInteger("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		BigInteger e = new BigInteger("65537");
		BigInteger d = new BigInteger("384626466509339543991296577767712323254747701029618040878613141179322077731921737288765385980253482791052382768803583551358976702280893517465992628002954984727590282534976836772588831428108223496664860429064081408302148870733225655831571685979762785236599060306030947817000364208892588343367629440384235446200694260364807539509242666927512991129654623352501583469337930995902215109751738450848562547306332799013868641828543857606454587367900002076070394714786820427023871310556639811793186209343332994561561121460286203274888514065022174372758662185993761861646098492005151361209047202021951927425944559233653737473");
		BigInteger n = new BigInteger("32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338532966225706400788815833624465067780972043028537544013633925177484532487013547324356952574707937829177062281358163969360482757577287828776800488699154214702930475498515281136964252118505002469656000708163010599295154568569686129958747103410739130137409843488834522872592814597312069081552222564534572806277086423194697476381224832510511095921736624660803198165862878002993801");

		BigInteger decrypted = nocrypted.modPow(e, n);
		BigInteger encrypted = decrypted.modPow(d, n);

		assertEquals(nocrypted, encrypted);
	}

}
