#include "pch.h"
#include "CppUnitTest.h"
#include "../Program/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab113UT
{
	TEST_CLASS(Lab113UT)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			[Forwarded from Максим Данилюк]
			Student* f = new Student[3];
			f[0] = { "Данилюк", 2, КН, 4, 5 };
			f[1] = { "Патюк", 3, ІТ, 4, 5, 3 };
			f[2] = { "Михайлов", 1, СА, 5, 5, 3 };

			int t;
			t = BinSearch(f, "Патюк", ІТ, 4);
			Assert::AreEqual(t, 1); 

		}
	};
}
