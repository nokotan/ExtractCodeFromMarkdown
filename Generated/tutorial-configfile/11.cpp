# include <Siv3D.hpp>

JSON MakeJSON()
{
	JSON json;
	json[U"Game"][U"score"] = { 10, 20, 50, 100 };
	return json;
}

void Main()
{
	const JSON json = MakeJSON();

	// by index
	{
		const size_t size = json[U"Game"][U"score"].size();
		for (size_t i = 0; i < size; ++i)
		{
			Print << json[U"Game"][U"score"][i].get<int32>();
		}
	}

	Print << U"----";

	// range based
	{
		for (const auto& elem : json[U"Game"][U"score"].arrayView())
		{
			Print << elem.get<int32>();
		}
	}

	while (System::Update())
	{

	}
}
