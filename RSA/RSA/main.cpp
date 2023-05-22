#include<iostream>
#include<ctime>
#include"BigInt.h"
#include"Rsa.h"


using std::cout;
using std::endl;
using std::cin;

void menu()
{
	cout<<"==========Welcome to use RSA encoder=========="<<endl;
	cout<<"               e.encrypt 加密              "<<endl;
	cout<<"               d.decrypt 解密              "<<endl;
	cout<<"               s.setkey 重置               "<<endl;
	cout<<"               p.print 显示               "<<endl;
	cout<<"               q.quit 退出                 "<<endl;
	cout<<"input your choice:"<<endl;
}

bool islegal(const string& str) {

	for (string::const_iterator iterator = str.begin(); iterator != str.end(); ++iterator)
		if (!isalnum(*iterator))
			return false;

	return true;
}

bool decode(Rsa& rsa) {
	string str;

	do {
		cout << ">输入16进制数据:";
		cin >> str;
	} while (cin && str.length() < 1);

	if (!cin || islegal(str) == false)
		return false;

	BigInt c(str);
	
	long t1 = clock();
	BigInt m = rsa.decodeByPr(c);
	long t2 = clock();

	cout << "用时:" << (t2 - t1) << "ms." << endl;
	cout << "密文:" << c << '\n' << "明文:" << m << endl;

	return true;
}

bool encry(Rsa& rsa,BigInt& c) {
	string str;

	do {
		cout << ">输入16进制数据:";
		cin >> str;
	} while (cin && str.length() < 1);

	if (!cin || islegal(str) == false)
		return false;

	BigInt m(str);

	c = rsa.encryptByPu(m);

	cout << "明文:" << m << '\n' << "密文:" << c << endl;

	return true;
}

void print(Rsa& rsa) {
	cout << rsa << endl;
}

void init(Rsa& rsa, int n) {
	cout << "初始化...."<< endl;
	long t1 = clock();
	rsa.init(n);
	long t2 = clock();
	cout << "初始化完成." << endl;
	cout << "用时:" << (t2-t1) / 1000 << "s." << endl;
}

int go()
{
	char ch;
	string str;
	Rsa rsa;
	BigInt c,m;
	cout<<"输入位数:";
	int n;
	cin >> n;

	init(rsa, n/2);

	while(true)
	{
		menu();
		cout<<">";
		cin>>str;
		if(!cin)
			return 0;
		
		if(str.length()<1)
			cout<<"重新输入"<<endl;
		else
		{
			ch=str.at(0);
			switch(ch)
			{
			case 'e':
			case 'E':
				encry(rsa,c);
				break;
			case 'd':
			case 'D':
				decode(rsa);
				break;
			case 's':
			case 'S':
				go();
				break;
			case 'p':
			case 'P':
				print(rsa);
				break;
			case 'q':
			case 'Q':
				return 0;
			}
		}
	}
}


int main()
{
	go();
}