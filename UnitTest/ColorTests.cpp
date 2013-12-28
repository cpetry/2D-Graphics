#include <glm/glm.hpp>

#include "CppUnitTest.h"
#include "Color.h"


// Ignore Specific default libraries: LIBCMT (parent project and testproject)
// Linker additional dependencies -> all obj-files which are needed (from error texts)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(Color_Test)
	{
	public:
		
		TEST_METHOD(Color_ConstructorTest)
		{
			Color c1;
			Color c2 = Color();
			Assert::IsTrue(c1 == c2);
		}

		TEST_METHOD(Color_ConstructorTest1)
		{
			Color c1 = Color(200, 255, 233);
			Color c2 = Color(200, 255, 233);
			Assert::IsTrue(c1 == c2);
		}

		TEST_METHOD(Color_ConstructorTest2)
		{
			Color c1 = Color(310, -25, 33);
			Color c2 = Color(255, 0, 33);
			Assert::IsTrue(c1 == c2);
		}

		TEST_METHOD(Color_ConstructorTest3)
		{
			Color c1 = Color(200.6, 0.2, 0.99);
			Color c2 = Color(200, 0, 0);
			Assert::IsTrue(c1 == c2);
		}

		TEST_METHOD(Color_ConstructorTest4)
		{
			Color c1 = Color(155, 3, 0);
			Color c2 = Color(200, 0, 0);
			Assert::IsFalse(c1 == c2);
		}

		TEST_METHOD(Color_ColorTest)
		{
			Color c1 = Color(155, 3, 0);
			Assert::IsTrue(c1.getR() == 155);
		}
	};
}