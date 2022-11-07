# include <Siv3D.hpp>

void Main()
{
	const URL url = U"https://httpbin.org/bearer";
	const HashTable<String, String> headers = { { U"Authorization", U"Bearer TOKEN123456abcdef" } };
	const FilePath saveFilePath = U"auth_result.json";

	if (const auto response = SimpleHTTP::Get(url, headers, saveFilePath))
	{
		Console << U"------";
		Console << response.getStatusLine().rtrimmed();
		Console << U"status code: " << FromEnum(response.getStatusCode());
		Console << U"------";
		Console << response.getHeader().rtrimmed();
		Console << U"------";

		if (response.isOK())
		{
			Print << TextReader{ saveFilePath }.readAll();
		}
	}
	else
	{
		Print << U"Failed.";
	}

	while (System::Update())
	{

	}
}
