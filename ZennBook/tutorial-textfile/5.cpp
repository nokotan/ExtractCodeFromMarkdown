# include <Siv3D.hpp>

void Main()
{
	{
		TextWriter writer{ U"tutorial.txt" };

		// 1 行書き込む
		writer.write(U"Hello, Siv3D!");

	} // ここで自動的にクローズ

	String text;
	{
		// TextWriter でオープンしたままだと、ここでオープンに失敗する
		TextReader reader{ U"tutorial.txt" };

		// 1 行読み込む
		reader.readLine(text);
	
	} // ここで自動的にクローズ

	Print << text;

	while (System::Update())
	{

	}
}
