#include "pch.h"
#include "CppUnitTest.h"
#include "../labr3/FloydWarshallAlgorithm.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AlgorithmFloydTest)
		{
			string text = "Saint-Petesburg;Moscow;10;20\nMoscow;Khabarovsk;40;35";
			string cityDep = "Saint-Petesburg";
			string cityArr = "Moscow";
			int testArray[3][3] = {
					{ 0, 10,50},
					{ 20, 0, 40,},
					{55, 35, 0},
			};
			int** array = algorithmFloyd(text, cityDep, cityArr);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::IsTrue(testArray[i][j] == array[i][j]);
				}
			}
		}
		TEST_METHOD(MatrixTest)
		{
			string text = "Saint-Petesburg;Moscow;10;20\nMoscow;Khabarovsk;40;35";
			List list;
			list.stringToList(text);
			int** array = list.Matrix(text);
			int mas[3][3] = {
					{ 0, 10,notAvailablePrice},
					{ 20, 0, 40,},
					{notAvailablePrice, 35, 0},

			};
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::IsTrue(mas[i][j] == array[i][j]);
				}
			}
		}
		TEST_METHOD(maxIndexTest)
		{
			string text = "Saint-Petesburg;Moscow;10;20\nMoscow;Khabarovsk;40;35";
			List list;
			list.stringToList(text);
			Assert::IsTrue(list.maxIndex() == 2);
		}
	};
}
