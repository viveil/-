#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication8/RBTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForTree
{
	TEST_CLASS(UnitTestForTree)
	{
	public:
		
		TEST_METHOD(insertFindTest)
		{
			Map<int, int>* test = new Map<int, int>();
			test->insert(55, 33);
			test->insert(40, 13);
			test->insert(65, 53);
			test->insert(60, 41);
			test->insert(75, 61);
			test->insert(57, 11);
			Assert::AreEqual(test->find(55), 33);
			Assert::AreEqual(test->find(60), 41);
		}

		TEST_METHOD(findErrorTest) {
			try {
				Map<int, int>* test = new Map<int, int>();
				test->insert(9, -7);
				test->insert(2, 2);
				test->insert(7, 4);
				test->find(31);
			}
			catch (std::out_of_range exc) {
				Assert::AreEqual("No key", exc.what());
			}
		}
		TEST_METHOD(removeTest)
		{
			try {
				Map<int, int>* test = new Map<int, int>();
				test->insert(55, 33);
				test->insert(40, 13);
				test->insert(65, 53);
				test->insert(60, 41);
				test->insert(75, 61);
				test->insert(57, 11);
				test->remove(65);
				test->find(65);
			}
			catch (std::out_of_range exc) {
				Assert::AreEqual("No key", exc.what());
			}
		}

		TEST_METHOD(clearTest)
		{
			{
				try {
					Map<int, int>* test = new Map<int, int>();
					test->insert(9, -1);
					test->insert(5, 11);
					test->insert(7, -3);
					test->clear();
					test->printTree();
				}
				catch (std::out_of_range exc) {
					Assert::AreEqual("Tree is empty!", exc.what());
				}
			}

		}
		TEST_METHOD(get_keysTest)
		{
			Map<int, int>* test = new Map<int, int>();
			test->insert(8, -1);
			test->insert(5, -2);
			test->insert(7, -3);
			List<int>* list = test->get_keys();
			Assert::AreEqual(list->at(0), 5);
			Assert::AreEqual(list->at(1), 7);
			Assert::AreEqual(list->at(2), 8);
		}
		TEST_METHOD(get_valuesTest)
		{
			Map<int, int>* test = new Map<int, int>();
			test->insert(8, -1);
			test->insert(5, -2);
			test->insert(7, -3);
			List<int>* list = test->get_values();
			Assert::AreEqual(list->at(0), -2);
			Assert::AreEqual(list->at(1), -3);
			Assert::AreEqual(list->at(2), -1);
		}
	};
}
