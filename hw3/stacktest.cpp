#include "stackint.h"
#include "gtest/gtest.h"

class stackTest : public testing::Test {
protected:
	stackTest() {}
	virtual ~stackTest() {}
	virtual void SetUp() {
		stack = StackInt();
		stack.push(3);
		stack.push(2);
		stack.push(1);
		stack.push(0);
	}
	virtual void TearDown() {}
	StackInt stack;
};

TEST_F(stackTest, isEmpty) {
	StackInt new_stack = StackInt();
	EXPECT_EQ(new_stack.empty(),true);
}

TEST_F(stackTest, Push_Pop_Top_Tests) {
	StackInt new_stack = StackInt();
	for( int i = 3; i >= 0; i--) new_stack.push(i);
	while(!stack.empty() && !new_stack.empty()){
		EXPECT_EQ(new_stack.top(),stack.top());
		new_stack.pop();
		stack.pop();
	}	
}