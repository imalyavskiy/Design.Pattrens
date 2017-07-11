#include <iostream>
#include <map>
#include <string>
#include <functional>

namespace Dynamic
{
	int main(int argc, char* argv[]);
}

namespace Static
{
	int main(int argc, char* argv[]);
}

const std::map<std::string, std::function<int(int, char*[])>> map = 
{ 
	{"dynamic", &Dynamic::main}, 
	{"static",  &Static::main} 
};

int main(int argc, char* argv[])
{
	if (argc < 2)
		std::cout << "Not enough arguments." << std::endl;
	
	for (size_t c = 1; c < argc; ++c)
	{
		auto it = map.find(argv[c]);
		if (it != map.end())
			(it->second)(argc, argv);
		else
			std::cout << "Algorithm \"" << argv[c] << "\" is not registered." << std::endl;
	}
}