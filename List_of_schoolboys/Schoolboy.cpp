#include "stdafx.h"
#include "Children.h"
#include "Schoolboy.h"
#include <string>


Schoolboy::Schoolboy() : Children::Children()
{
	ball = 0;
}

Schoolboy::Schoolboy(const Schoolboy& ch) : Children::Children(ch)
{
	ball = ch.ball;
}

Schoolboy::Schoolboy(std::string ch_name, std::string ch_surname, int ch_age, int ch_ball) : Children::Children (ch_name, ch_surname, ch_age)
{
	ball = ch_ball;
}

Schoolboy::~Schoolboy()
{
	
}

void Schoolboy::set(std::string ch_name, std::string ch_surname, int ch_age, int ch_ball)
{
	Children::set(ch_name, ch_surname, ch_age);
	ball = ch_ball;
}

Schoolboy Schoolboy::operator+ (Schoolboy ch)
{
	return Schoolboy(this->name + ch.name, this->surname + ch.surname, this->age + ch.age, this->ball + ch.ball);
}