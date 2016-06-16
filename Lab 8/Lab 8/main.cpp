#include <iostream>
#include <string>
struct blah
{
	int b;
	int c;
};

template<typename gen>
void Generic (std::string s) {
	gen G;
	std::cin >> G;
	std::cout << s << " in decimal: " << std::dec << G << "\n";
	std::cout << s << " in hexidecimal: " << std::hex << G << "\n";
}
	int main(int argc, char* argv[]) {
		Generic <int>("int");
		Generic <float>("floats");
		Generic <char>("char");
		Generic <std::string>("string");
		//Generic <blah>("blah");



}