#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab2/lab2.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest_lab2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string_t s = string_malloc(256);
			Assert::IsFalse(lab2(s, STRING_STATIC("5")));
			Assert::AreEqual("5", s.first);
			string_free(s);
		}

	};
}