# include <Siv3D.hpp>

void Main()
{
	const URL url = U"https://httpbin.org/post";
	const HashTable<String, String> headers = { { U"Content-Type", U"application/json" } };
	const std::string data = JSON
	{
		{ U"body", U"Hello, Siv3D!" },
		{ U"date", DateTime::Now().format() },
	}.formatUTF8();
	const FilePath saveFilePath = U"post_result.json";

	if (auto response = SimpleHTTP::Post(url, headers, data.data(), data.size(), saveFilePath))
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
