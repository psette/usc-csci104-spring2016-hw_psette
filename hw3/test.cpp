#include "llistint.h"
#include "gtest/gtest.h"

class llistintTest : public testing::Test {
protected:
	llistintTest() {}
	virtual ~llistintTest() {}
	virtual void SetUp() {
		list = LListInt();
		list_two = LListInt();
		list_three = LListInt();
		list.insert(0,0);
		list.insert(1,1);
		list.insert(2,2);
		list.insert(3,3);
		list_two.insert(0,0);
		list_two.insert(1,1);
		list_three.insert(0,2);
		list_three.insert(1,3);
	}
	virtual void TearDown() {}
	LListInt list, list_two, list_three;
};

TEST_F(llistintTest, CopyConstructor) {
	LListInt new_list = LListInt(list);
	for( int i = 0; i < list.size(); i++)	
		EXPECT_EQ(list.get(i), new_list.get(i));
}

TEST_F(llistintTest, Equals) {
	LListInt new_list = LListInt();
	new_list = list;
	for( int i = 0; i < list.size(); i++)	
		EXPECT_EQ(list.get(i),new_list.get(i));
}

TEST_F(llistintTest, Add) {
	list_two = list_two + list_three;
	for( int i = 0; i < list.size(); i++)	EXPECT_EQ(list.get(i),list_two.get(i));
	LListInt new_list = LListInt();
	new_list = list_two + list_three;
	for( int i = 0; i < list.size(); i++)	EXPECT_EQ(list.get(i),new_list.get(i));
}

TEST_F(llistintTest, Brackets) {
	for( int i = 0; i < list.size(); i++)	
		EXPECT_EQ(list.get(i), list[i]);
}
