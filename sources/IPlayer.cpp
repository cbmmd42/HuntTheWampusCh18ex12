#include "IPlayer.h"

std::string IPlayer::move(int roomChoice){
	std::string roomNumber = "13";
	return roomNumber;
}

bool IPlayer::shoot(int roomNo1, int roomNo2, int roomNo3){
	return false;
}

bool IPlayer::isAlive() {
	return true;
}

bool IPlayer::wampusLives(){
	return true;
}

std::string IPlayer::soundsHeard() {
	//std::string roomNumber = "13";
	return "I hear a breeze";
}