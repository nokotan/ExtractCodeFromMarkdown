# include <Siv3D.hpp>

void Main()
{
	Array<int32> values = { 1, 2, 3, 4, 5 };

	// 各要素に 0.1 をかけた結果の配列を作成
	Array<double> results = values.map([](int32 n){ return (n * 0.1); });

	Print << results;

	while (System::Update())
	{

	}
}
