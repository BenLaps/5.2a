#include "pch.h"
#include "CppUnitTest.h"
#include "../5.2a/5.2a.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char f[6] = "f.dat";
			load_print(f);
		}
	};
}
