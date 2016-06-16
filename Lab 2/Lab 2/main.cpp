#include <iostream>
#include <inttypes.h>
int main(int argc, const char * argv[])
{
	//1.
	int x;
	std::cout << "input your value: \n";
	std::cin >> x;
	printf("bool: %d\n", true);
	printf("char: %c\n", 'a');
	printf("short: %h\n", 123);
	printf("long: %l\n", 12345);
	printf("long long: %ll\n", 1234567);
	printf("float: %f\n", 1.23);
	printf("double: %f\n", 1.234);
	printf("long double: %L\n", 1.234567);
	printf("unsigned short: %h\n", 123);
	printf("unsigned int: %o\n", 1234567);
	printf("unsigned long: %l\n", 8198141094);
	printf("unsigned long long: %ll\n", 9378461834);
	printf("int8_d: %" PRId8 "\n", 200);
	printf("hex int8_d: %" PRIx8 "\n", 200);
	printf("int16_d: %" PRId16 "\n", 6000);
	printf("hex int16_d: %" PRIx16 "\n", 6000);
	printf("int32_d: %" PRId32 "\n", 2319440);
	printf("hex int32_d: %" PRIx32 "\n", 2319440);
	printf("int64_d: %" PRId64 "\n", 12345);
	printf("hex int64_d: %" PRIx64 "\n", 12345);

	//2.
	std::cout << "bool:" << sizeof (bool) << '\n'
		<< "bool:" << sizeof (bool) << '\n'
		<< "char:" << sizeof (char) << '\n'
		<< "short:" << sizeof (short) << '\n'
		<< "long:" << sizeof (long) << '\n'
		<< "long long:" << sizeof (long long) << '\n'
		<< "float:" << sizeof (float) << '\n'
		<< "double:" << sizeof (double) << '\n'
		<< "long double:" << sizeof (long double) << '\n'
		<< "unsigned short:" << sizeof (unsigned short) << '\n'
		<< "unsigned int:" << sizeof (unsigned int) << '\n'
		<< "unsinged long:" << sizeof (unsigned long) << '\n'
		<< "unsinged long long:" << sizeof (unsigned long long) << '\n'
		<< "int8_t:" << sizeof int8_t << '\n'
		<< "int16_t:" << sizeof int16_t << '\n'
		<< "int32_t:" << sizeof int32_t << '\n'
		<< "int64_t:" << sizeof int64_t << '\n';

	//4.
	printf("max of unsigned int8: %" PRId8 "\n", 255);
	printf("min of unsigned int8: %" PRId8 "\n", 0);
	printf("max of unsigned int32: %" PRId32 "\n", 4294967295);
	printf("min of unsigned int32: %" PRId32 "\n", 0);

	//5.
	printf("max of signed int8: %" PRId8 "\n", 127);
	printf("min of signed int8: %" PRId8 "\n", -127);
	printf("max of signed int32: %" PRId64 "\n", 2147483647);
	printf("min of signed int32: %" PRId64 "\n", -2147483647);

	//6. 
	int y = 3.14159265359;
	unsigned int z = 3.14159265359;
	printf("float to int: %d", x);
	printf("float to unsigned int: %d", y);

	//7.
	int w;
	float v;
	printf("uninitialized int: %d", w);
	printf("uninitialized float: %f", v);







}
