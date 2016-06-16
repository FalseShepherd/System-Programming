bool foo(int a)
{
	return !(a & 1);
}

bool foo(int a, intb)
{
	return !(a & 1) && !(b & 1);
}

bool foo(int a, int b, int c)
{
	return !(a & 1) && !(b & 1) && !(c & 1);
}

bool allEven(int a, int b = 0, int c = 0)
{
	return !(a & 1) && !(b & 1) && !(c & 1);
}