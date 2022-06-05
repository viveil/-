#include "pch.h"
#include "CppUnitTest.h"
#include "../lr2/HuffmanAlgo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHuffman
{
	TEST_CLASS(UnitTestHuffman)
	{
	public:
		
		TEST_METHOD(codingTest)
		{
			string testString = "ohayo";
			string check = "1010011001";
			RBtree<char, int> map;
			AlgoHuffman test = AlgoHuffman(testString);
			test.createEncodingTable(testString, map);
			test.HuffmanTree(map);
			test.coding();
			Assert::IsTrue(test.codingString == check);
		}
		TEST_METHOD(decodingTest)
		{

			string testString = "ohayo";
			string check = "1010011001";
			RBtree<char, int> map;
			AlgoHuffman test = AlgoHuffman(testString);
			test.createEncodingTable(testString, map);
			test.HuffmanTree(map);
			test.coding();
			test.decoding();
			Assert::IsTrue(test.codingString == check);
			Assert::IsTrue(test.decodingString == testString);
		}
	};
}
