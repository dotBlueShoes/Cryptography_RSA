#include "BigInt.hpp"

#include <cassert>

#include <windows.h>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>

int BigInt::base_char=8;
int BigInt::base=0xFFFFFFFF;
int BigInt::basebit=5;//2^5
int BigInt::basebitchar=0x1F;
int BigInt::basebitnum=32;

BigInt BigInt::Zero(0);
BigInt BigInt::One(1);
BigInt BigInt::Two(2);

BigInt operator + (const BigInt& a,const BigInt& b)
{
	BigInt ca(a);
	return ca.add(b);
}

BigInt operator - (const BigInt& a,const BigInt& b)
{
	BigInt ca(a);
	return ca.sub(b);
}

BigInt operator * (const BigInt& a,const BigInt& b)
{
	if(a==(BigInt::Zero) || b==(BigInt::Zero))
		return BigInt::Zero;

	const BigInt &big=a._data.size()>b._data.size()?a:b;
	const BigInt &smalll=(&big)==(&a)?b:a;

	BigInt result(0);
	
	BigInt::bit bt(smalll);
	for(int i=bt.size()-1;i>=0;--i)
	{
		if(bt.at(i))
		{
			BigInt temp(big,false);
			temp.leftShift(i);
			//std::cout<<"tmp:"<<temp<<std::endl;
			result.add(temp);
			//std::cout<<"res:"<<result<<std::endl;
		}
	}
	result._isnegative=!(a._isnegative==b._isnegative);
	return result;
}

BigInt operator / (const BigInt& a,const BigInt& b)
{
	assert(b!=(BigInt::Zero));
	if(a.equals(b))//绝对值相等
		return (a._isnegative==b._isnegative)?BigInt(1):BigInt(-1);
	else if(a.smallThan(b))//绝对值小于
		return BigInt::Zero;
	else
	{
		BigInt result,ca;
		BigInt::div(a,b,result,ca);
		return result;
	}
}

BigInt operator % (const BigInt& a,const BigInt& b)
{
	assert(b!=(BigInt::Zero));
	if(a.equals(b))
		return BigInt::Zero;
	else if(a.smallThan(b))
		return a;
	else
	{
		BigInt result,ca;
		BigInt::div(a,b,result,ca);
		return ca;
	}
}

void BigInt::div(const BigInt& a,const BigInt& b,BigInt& result,BigInt& ca)
{
	//1.复制a,b
	BigInt cb(b,false);
	ca._isnegative=false;
	ca._data=a._data;

	BigInt::bit bit_b(cb);
	//位数对齐
	while(true)//绝对值小于
	{
		BigInt::bit bit_a(ca);
		int len=bit_a.size()-bit_b.size();
		BigInt temp;
		//找到移位的
		while(len>=0)
		{
			temp=cb<<len;
			if(temp.smallOrEquals(ca))
				break;
			--len;
		}
		if(len<0)
			break;
		BigInt::base_t n=0;
		while(temp.smallOrEquals(ca))
		{
			ca.sub(temp);
			++n;
		}
		BigInt kk(n);
		if(len)
			kk.leftShift(len);
		result.add(kk);
	}
	result.trim();
}

bool operator < (const BigInt& a,const BigInt& b)
{
	if(a._isnegative==b._isnegative)
	{
		if(a._isnegative==false)
			return a.smallThan(b);
		else
			return !(a.smallOrEquals(b));
	}
	else
	{
		if(a._isnegative==false)
			return true;
		else
			return false;
	}
}

bool operator <= (const BigInt& a,const BigInt& b)
{
	if(a._isnegative==b._isnegative)
	{//同号
		if(a._isnegative==false)
			return a.smallOrEquals(b);
		else
			return !(a.smallThan(b));
	}
	else//异号
	{
		if(a._isnegative==false)
			return true;
		else
			return false;
	}
}

bool operator == (const BigInt& a,const BigInt& b)
{
	return a._data==b._data && a._isnegative == b._isnegative;
}

ostream& operator << (ostream& out, const BigInt& a) {

	static char hex[] {
		'0','1','2','3',
		'4','5','6','7',
		'8','9','A','B',
		'C','D','E','F'
	};

	if (a._isnegative)
		out<<"-";

	BigInt::base_t T=0x0F;
	std::string str;

	for (BigInt::data_t::const_iterator it = a._data.begin(); it != a._data.end(); ++it) {
		BigInt::base_t ch = (*it);
		for (int j = 0; j < BigInt::base_char; ++j) {
			str.push_back(hex[ch& (T)]);
			ch = ch >> 4;
		}
	}

	reverse(str.begin(), str.end());
	out << str;
	return out;
}

std::wstring BigInt::toWString(const bool& negate) {
	//static char hex[] {
	//	'0','1','2','3',
	//	'4','5','6','7',
	//	'8','9','A','B',
	//	'C','D','E','F'
	//};
	//
	//static char rev[] {
	//	'F','E','D','C',
	//	'B','A','9','8',
	//	'7','6','5','4',
	//	'3','2','1','0'
	//};

	static char hex[] {
		0,   1,  2,  3,
		4,   5,  6,  7,
		8,   9, 10, 11,
		12, 13, 14, 15
	};

	static char rev[] {
		15, 14, 13, 12,
		11, 10,  9,  8,
		 7,  6,  5,  4,
		 3,  2,  1,  0
	};

	BigInt::base_t T = 0x0F;
	std::string cstring;

	if (_isnegative || negate) {
		for (BigInt::data_t::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			BigInt::base_t ch = (*it);
			for (int j = 0; j < BigInt::base_char; ++j) {
				cstring.push_back(rev[(ch & (T))]);
				ch = ch >> 4;
			}
		}

		if (cstring[0] == 15) { // 'f'
			cstring[0] = 0;
			cstring[1] += 1;
		} else if (cstring[0] == 9) { // '9'
			cstring[0] = 10; // 'a'
		} else {
			cstring[0] += 1;
		}

	} else {
		for (BigInt::data_t::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			BigInt::base_t ch = (*it);
			for (int j = 0; j < BigInt::base_char; ++j) {
				cstring.push_back(hex[ch & (T)]);
				ch = ch >> 4;
			}
		}
	}

	reverse(cstring.begin(), cstring.end());

	// BASE16 -> BASE256
	const uint32_t count = 2;
	const uint32_t f2 = cstring.size() / count;
	const uint32_t r2 = cstring.size() % count;

	std::string result = "";
	uint8_t character = 0;
	for (uint32_t i = 0; i < 4; ++i) { 
		character += cstring[(i * count)]; // 0, 2, 4, 6
		character <<= 4;
		character += cstring[(i * count) + 1]; // 1, 3, 5, 7
		//!// result += character;
		character = 0;
	}

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(result);
}

std::string BigInt::toHexString(const bool& negate) {
	static char hex[] {
		'0','1','2','3',
		'4','5','6','7',
		'8','9','A','B',
		'C','D','E','F'
	};
	
	static char rev[] {
		'F','E','D','C',
		'B','A','9','8',
		'7','6','5','4',
		'3','2','1','0'
	};

	BigInt::base_t T = 0x0F;
	std::string cstring;

	if (_isnegative || negate) {
		for (BigInt::data_t::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			BigInt::base_t ch = (*it);
			for (int j = 0; j < BigInt::base_char; ++j) {
				cstring.push_back(rev[(ch & (T))]);
				ch = ch >> 4;
			}
		}
	
		if (cstring[0] == 'F') { // 'F'
			cstring[0] = 0;
			cstring[1] += 1;
		} else if (cstring[0] == '9') { // '9'
			cstring[0] = 'A'; // 'A'
		} else {
			cstring[0] += 1;
		}
	
	} else {
		for (BigInt::data_t::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			BigInt::base_t ch = (*it);
			for (int j = 0; j < BigInt::base_char; ++j) {
				cstring.push_back(hex[ch & (T)]);
				ch = ch >> 4;
			}
		}
	}

	reverse(cstring.begin(), cstring.end());

	return cstring;
}

std::string BigInt::toString(const bool& negate) {
	static char hex[] {
		0,   1,  2,  3,
		4,   5,  6,  7,
		8,   9, 10, 11,
		12, 13, 14, 15
	};
	
	static char rev[] {
		15, 14, 13, 12,
		11, 10,  9,  8,
		 7,  6,  5,  4,
		 3,  2,  1,  0
	};

	BigInt::base_t T = 0x0F;
	std::string cstring;

	if (_isnegative || negate) {
		for (BigInt::data_t::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			BigInt::base_t ch = (*it);
			for (int j = 0; j < BigInt::base_char; ++j) {
				cstring.push_back(rev[(ch & (T))]);
				ch = ch >> 4;
			}
		}
	
		if (cstring[0] == 15) { // 'f'
			cstring[0] = 0;
			cstring[1] += 1;
		} else if (cstring[0] == 9) { // '9'
			cstring[0] = 10; // 'a'
		} else {
			cstring[0] += 1;
		}
	
	} else {
		for (BigInt::data_t::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			BigInt::base_t ch = (*it);
			for (int j = 0; j < BigInt::base_char; ++j) {
				cstring.push_back(hex[ch & (T)]);
				ch = ch >> 4;
			}
		}
	}

	reverse(cstring.begin(), cstring.end());

	//// BASE16 -> BASE256
	//const uint32_t count = 2;
	//const uint32_t f2 = cstring.size() / count;
	//const uint32_t r2 = cstring.size() % count;
	//
	//std::string result = "";
	//uint8_t character = 0;
	//
	////debug
	//char debug[10] { 0 };
	//
	//for (uint32_t i = 0; i < f2; ++i) {
	//	character += cstring[(i * count)];		// 0, 2, 4, 6
	//	debug[0] = cstring[(i * count)];
	//	MessageBoxA(nullptr, debug, "DEBUG", MB_OK);
	//	character <<= 4;
	//	character += cstring[(i * count) + 1];	// 1, 3, 5, 7
	//	result += character;
	//	character = 0;
	//}

	const uint32_t count = 2;
	const uint32_t f2 = cstring.size() / count;
	const uint32_t r2 = cstring.size() % count;

	std::string result = "";
	uint8_t character = 0;

	for (uint32_t i = 0; i < f2; ++i) {
		character += cstring[(i * count)];		// 0, 2, 4, 6
		character <<= 4;
		character += cstring[(i * count) + 1];	// 1, 3, 5, 7
		result += character;
		character = 0;
	}
	//result += '\0';

	return result;
}

BigInt operator <<(const BigInt& a,unsigned int n)
{
	BigInt ca(a);
	return ca.leftShift(n);
}

BigInt& BigInt::leftShift(const unsigned int n)
{
	int k=n>>(BigInt::basebit);//5
	int off=n&(BigInt::basebitchar);//0xFF

	int inc=(off==0)?k:1+k;
	for(int i=0;i<inc;++i)
		_data.push_back(0);

	if(k)
	{
		inc=(off==0)?1:2;
		for(int i=_data.size()-inc;i>=k;--i)
			_data[i]=_data[i-k];
		for(int i=0;i<k;++i)
			_data[i]=0;
	}

	if(off)
	{
		BigInt::base_t T=BigInt::base;//0xffffffff
		T=T<<(BigInt::basebitnum-off);//32
		//左移
		BigInt::base_t ch=0;
		for(std::size_t i=0;i<_data.size();++i)
		{
			BigInt::base_t t=_data[i];
			_data[i]=(t<<off)|ch;
			ch=(t&T)>>(BigInt::basebitnum-off);//32,最高位
		}
	}
	trim();
	return *this;
}

BigInt& BigInt::rightShift(const unsigned int n)
{
	int k=n>>(BigInt::basebit);//5
	int off=n&(BigInt::basebitchar);//0xFF

	if(k)
	{
		for(int i=0;i>k;++i)
			_data[i]=_data[i+k];
		for(int i=0;i<k;++i)
			_data.pop_back();
		if(_data.size()==0)
			_data.push_back(0);
	}

	if(off)
	{
		BigInt::base_t T=BigInt::base;//0xFFFFFFFF
		T=T>>(BigInt::basebitnum-off);//32
		//左移
		BigInt::base_t ch=0;
		for(int i=_data.size()-1;i>=0;--i)
		{
			BigInt::base_t t=_data[i];
			_data[i]=(t>>off)|ch;
			ch=(t&T)<<(BigInt::basebitnum-off);//32,最高位
		}
	}
	trim();
	return *this;
}

BigInt& BigInt::sub(const BigInt& b)
{
	if(b._isnegative==_isnegative)
	{//同号
		
		BigInt::data_t &res=_data;
		if(!(smallThan(b)))//绝对值大于b
		{
			int cn=0;//借位
			//大数减小数
			for(std::size_t i=0;i<b._data.size();++i)
			{
				BigInt::base_t temp=res[i];
				res[i]=(res[i]-b._data[i]-cn);
				cn=temp<res[i]?1:temp<b._data[i]?1:0;
			}

			for(std::size_t i=b._data.size();i<_data.size() && cn!=0;++i)
			{
				BigInt::base_t temp=res[i];
				res[i]=res[i]-cn;
				cn=temp<cn;
			}
			trim();
		}
		else//绝对值小于b
		{
			_data=(b-(*this))._data;
			_isnegative=!_isnegative;
		}
	}
	else
	{//异号的情况
		bool isnegative=_isnegative;
		_isnegative=b._isnegative;
		add(b);
		_isnegative=isnegative;
	}
	return *this;
}

BigInt& BigInt::add(const BigInt& b)
{
	if(_isnegative==b._isnegative)
	{//同号
		//引用
		BigInt::data_t &res=_data;
		int len=b._data.size()-_data.size();

		while((len--)>0)//高位补0
			res.push_back(0);

		int cn=0;//进位
		for(std::size_t i=0;i<b._data.size();++i)
		{
			BigInt::base_t temp=res[i];
			res[i]=res[i]+b._data[i]+cn;
			cn=temp>res[i]?1:temp>(temp+b._data[i])?1:0;//0xFFFFFFFF
		}

		for(std::size_t i=b._data.size();i<_data.size() && cn!=0;++i)
		{
			BigInt::base_t temp=res[i];
			res[i]=(res[i]+cn);
			cn=temp>res[i];
		}

		if(cn!=0)
			res.push_back(cn);
		
		trim();
	}
	else
	{//异号的情况
		bool isnegative;
		if(smallThan(b))//绝对值小于b
			isnegative=b._isnegative;
		else if(equals(b))//绝对值等于b
			isnegative=false;
		else//绝对值大于b
			isnegative=_isnegative;

		_isnegative=b._isnegative;
		sub(b);
		_isnegative=isnegative;		
	}
	return *this;
}

BigInt BigInt::moden(const BigInt& exp,const BigInt& p)const
{//模幂运算
	BigInt::bit t(exp);

	BigInt d(1);
	for(int i=t.size()-1;i>=0;--i)
	{
		d=(d*d)%p;
		if(t.at(i))
			d=(d*(*this))%p;
	}
	return d;
}

BigInt BigInt::extendEuclid(const BigInt& m)
{//扩展欧几里得算法求乘法逆元
	assert(m._isnegative==false);//m为正数
	BigInt a[3],b[3],t[3];
	a[0] = 1; a[1] = 0; a[2] = m;
	b[0] = 0; b[1] = 1; b[2] = *this;
	if (b[2] == BigInt::Zero || b[2]==BigInt::One)
		return b[2];

	while(true) 
	{
		if (b[2] == BigInt::One) 
		{
			if(b[1]._isnegative==true)//负数
				b[1]=(b[1]%m+m)%m;
			return b[1];
		}

		BigInt q = a[2]/b[2];
		for(int i=0; i<3;++i)
		{
			t[i] = a[i] - q * b[i];
			a[i] = b[i];
			b[i] = t[i];
		}
	}
}

std::size_t BigInt::bit::size()
{
	return _size;
}

bool BigInt::bit::at(std::size_t i)
{
	std::size_t index=i>>(BigInt::basebit);
	std::size_t off=i&(BigInt::basebitchar);
	BigInt::base_t t=_bitvec[index];
	return (t&(1<<off));
}

BigInt::bit::bit(const BigInt& ba)
{
	_bitvec=ba._data;
	BigInt::base_t a=_bitvec[_bitvec.size()-1];//最高位
	_size=_bitvec.size()<<(BigInt::basebit);
	BigInt::base_t t=1<<(BigInt::basebitnum-1);
	
	if(a==0)
		_size-=(BigInt::basebitnum);
	else
	{
		while(!(a&t))
		{
			--_size;
			t=t>>1;
		}
	}
}

bool BigInt::smallThan(const BigInt& b)const
{
	if(_data.size()==b._data.size())
	{
		for(BigInt::data_t::const_reverse_iterator it=_data.rbegin(),it_b=b._data.rbegin();
			it!=_data.rend();++it,++it_b)
			if((*it)!=(*it_b))
				return (*it)<(*it_b);
		return false;//相等
	}
	else
		return _data.size()<b._data.size();
}

bool BigInt::smallOrEquals(const BigInt& b)const
{
	if(_data.size()==b._data.size())
	{
		for(BigInt::data_t::const_reverse_iterator it=_data.rbegin(),it_b=b._data.rbegin();
			it!=_data.rend();++it,++it_b)
			if((*it)!=(*it_b))
				return (*it)<(*it_b);
		return true;//相等
	}
	else
		return _data.size()<b._data.size();
}

bool BigInt::equals(const BigInt& a)const
{
	return _data==a._data;
}