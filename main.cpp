#include <iostream>
#include <string>

// input - input text, big - separate uper and lower case 
std::string toCode(std::string input, bool big)
{
	std::string result = "";

	if (input.empty())
		return result;

	char current = ((big) ? input[0] : std::tolower(input[0]));
	int count = 0;

	for (auto i = 0; i < input.size(); i++) {

		if (isalpha(input[i]))
		{
			if (!big) {
				input[i] = std::tolower(input[i]);
			}

			if (input[i] != current)
			{
				result = result + current + std::to_string(count);
				current = input[i];
				count = 1;
			}
			else
			{
				count++;
			}
		}
	}

	if (count > 0)
		result = result + current + std::to_string(count);

	return result;
}

//input - string code, big - separate uper and lower case 
std::string toString(std::string input, bool big)
{
	std::string result = "";

	if (input.empty())
		return result;

	char current = NULL;
	int count = 0, mul = 1;

	for (int i = 0; i < input.size(); i++)
	{
		if (isalpha(input[i]))
		{
			if (!big) {
				input[i] = std::tolower(input[i]);
			}

			for (int i = 0; i < count; i++)
			{
				result = result + current;
			}

			count = 0;
			mul = 1;
			current = input[i];
		}

		if (isdigit(input[i]))
		{
			count = count * mul;
			count = count + (input[i] - 48);
			mul = mul * 10;
		}
	}

	for (int i = 0; i < count; i++)
	{
		result = result + current;
	}

	return result;
}

int main()
{
	std::cout << "# Text to code test #" << std::endl;

	//test standard string to code 
	std::cout << "Expected g4h6z3, got: " << toCode("gggghhhhhhzzz", 0) << std::endl;

	//test no separate upper case
	std::cout << "Expected g4h6z3, got: " << toCode("GGggHHHhhhzZz", 0) << std::endl;

	//test separate upper case
	std::cout << "Expected G2g2H3h3z1Z1z1, got: " << toCode("GGggHHHhhhzZz", 1) << std::endl;

	//empty string
	std::cout << "Expected empty, got: " << toCode("", 0) << std::endl;

	//bad string //todo
	std::cout << "Expected empty, got: " << toCode("+=", 0) << std::endl;

	//short string
	std::cout << "Expected c1, got: " << toCode("c", 0) << std::endl;

	std::cout << "# Code to text test #" << std::endl;

	//test standard string to code 
	std::cout << "Expected gggghhhhhhzzz, got: " << toString("g4h6z3", 0) << std::endl;

	//test no separate upper case
	std::cout << "Expected gggghhhhhhzzz, got: " << toString("G2g2H3h3z1Z1z1", 0) << std::endl;

	//test separate upper case
	std::cout << "Expected GGggHHHhhhzZz, got: " << toString("G2g2H3h3z1Z1z1", 1) << std::endl;

	//empty string
	std::cout << "Expected empty, got: " << toString("", 0) << std::endl;

	//bad string //todo
	std::cout << "Expected empty, got: " << toString("+=", 0) << std::endl;

	//short string
	std::cout << "Expected c, got: " << toString("c1", 0) << std::endl;

	std::cout << "# Code <-> Text test #" << std::endl;

	//two side test 
	std::string input = "gggghhhhhhzzz";
	std::string code = toCode(input, 0);
	std::string text = toString(code, 0);

	std::cout << "Test: " << (input == text) << std::endl;

	return 0;
}