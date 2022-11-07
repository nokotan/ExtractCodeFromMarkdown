# include <Siv3D.hpp>

void Main()
{
	bool a = true;
	int32 b = 123;
	double c = 0.5;
	BigInt d = 111222333444555666777888999000_big;
	BigFloat e = 0.1234567890123456789_bigF;
	Byte f{ 0xF7 };
	char32 g = U'あ';
	String h = U"Hello!";
	Array<int32> i = { 10, 20, 30, 40 };
	Array<String> j = { U"aaa", U"bbb" };
	HalfFloat k = 3.333333f;

	Print << a;
	Print << b;
	Print << c;
	Print << d;
	Print << e;
	Print << f;
	Print << g;
	Print << h;
	Print << i << U" : " << i.size();
	Print << j << U" : " << j.size();
	Print << k << U" : " << sizeof(k);

	while (System::Update())
	{

	}
}
