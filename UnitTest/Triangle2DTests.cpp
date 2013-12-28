#include <glm/glm.hpp>

#include "CppUnitTest.h"
#include "Color.h"
#include "Primitives2D\Triangle2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(Triangle2D_Tests)
	{
	public:

		TEST_METHOD(Triangle_ConstructorTest){
			Triangle2D t1 = Triangle2D(100, 100, 150, 150, 100, 150, Color(), false);
			Triangle2D t2 = Triangle2D(glm::vec2(100, 100), glm::vec2(150, 150), glm::vec2(100, 150), Color(), false);
			Assert::IsTrue(t1 == t2);
		}
	};
}