#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IGame.h"
#include "IPlayer.h"

using ::testing::Return;
using ::testing::Assign;

class MockPlayer : public IPlayer {
public:
	MOCK_METHOD1(move, std::string(int roomChoice));
	MOCK_METHOD3(shoot, bool(int roomNo1,int roomNo2,int roomNo3));
	MOCK_METHOD0(soundsHeard, std::string());
};

class MockUserInput : public IUserInput {
public:
	MOCK_METHOD0(getInput, std::string());
	MOCK_METHOD0(getInputMove, int());
	MOCK_METHOD3(getInputShoot, void(int& firstRoom, int& secondRoom, int& thirdRoom));
};

TEST(HuntTheWampusTests, GameInterfaceMove){
	MockPlayer mp;
	IGame g(mp);
	
	EXPECT_CALL(mp, move(3))
	.Times(1)
	.WillOnce(Return("13"));
	
	std::string actual = g.move(3);
	std::cout << '\n';
	
	EXPECT_EQ(actual, "You moved to room 13");
}

TEST(HuntTheWampusTests, GameInterfaceShoot){
	MockPlayer mp;
	IGame g(mp);
	
	EXPECT_CALL(mp, shoot(3, 14 ,16))
	.Times(1)
	.WillOnce(Return(false));
	
	std::string actual = g.shoot(3, 14 ,16);
	//std::cout << '\n';
	
	EXPECT_EQ(actual, "You missed the wampus");
}

TEST(HuntTheWampusTests, GameInterfaceIndication){
	MockPlayer mp;
	IGame g(mp);
	
	EXPECT_CALL(mp, soundsHeard())
	.Times(1)
	.WillOnce(Return("I hear a breeze"));
	
	std::string actual = g.indication();
	std::cout << '\n';
	
	EXPECT_EQ(actual, "I hear a breeze");
}

TEST(HuntTheWampusTests, GameInterfacePrompt){
	MockPlayer mp;
	IGame g(mp);
	
	g.prompt("This is a test of the prompt() function");
	std::cout << '\n';
}

TEST(HuntTheWampusTests, GameInterfaceUserInput){
	MockPlayer mp;
	MockUserInput i;
	IGame g(mp,i);
	
	EXPECT_CALL(i, getInput())
	.Times(1)
	.WillOnce(Return("move"));
	
	char actual = g.userInput();
	char expected = 'm';
	EXPECT_EQ(actual, expected);
}

TEST(HuntTheWampusTests, GameInterfaceUserInputTypo){
	MockPlayer mp;
	MockUserInput i;
	IGame g(mp,i);
	
	EXPECT_CALL(i, getInput())
	.Times(2)
	.WillOnce(Return("mve"))
	.WillOnce(Return("move"));
	
	char actual = g.userInput();
	char expected = 'm';
	EXPECT_EQ(actual, expected);
}

TEST(HuntTheWampusTests, GameInterfaceUserInputShoot){
	MockPlayer mp;
	MockUserInput i;
	IGame g(mp,i);
	
	EXPECT_CALL(i, getInput())
	.Times(1)
	.WillOnce(Return("shoot"));
	
	char actual = g.userInput();
	char expected = 's';
	EXPECT_EQ(actual, expected);
}

TEST(HuntTheWampusTests, GameInterfaceUserInputOverloadMove){
	MockPlayer mp;
	MockUserInput i;
	IGame g(mp,i);
	
	EXPECT_CALL(i, getInputMove())
	.Times(1)
	.WillOnce(Return(1));
	int actual;
	
	g.userInput(actual);
	int expected = 1;
	EXPECT_EQ(actual, expected);
}

TEST(HuntTheWampusTests, GameInterfaceUserInputOverloadShoot){
	MockPlayer mp;
	MockUserInput i;
	IGame g(mp,i);
	int actualFirst = 0;
	int actualSecond = 0;
	int actualThird = 0;
	
	EXPECT_CALL(i, getInputShoot(actualFirst,actualSecond,actualThird))
	.Times(1)
	.WillOnce(DoAll(Assign(&actualFirst, 15),Assign(&actualSecond, 2),Assign(&actualThird, 54)));
	
	int expectedFirst = 15;
	int expectedSecond = 2;
	int expectedThird = 54;
	
	g.userInput(actualFirst,actualSecond,actualThird);
	
	EXPECT_EQ(actualFirst, expectedFirst);
	EXPECT_EQ(actualSecond, expectedSecond);
	EXPECT_EQ(actualThird, expectedThird);
}

