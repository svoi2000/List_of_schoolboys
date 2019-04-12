#pragma once
#include "Children.h"


class Schoolboy : public Children
{
private:
	/* список свойств и методов для использования внутри класса */
	

public:
	/* список свойств и методов доступных другим функциям и объектам программы */
	int ball;
	Schoolboy();
	Schoolboy(const Schoolboy&);
	Schoolboy (std::string, std::string, int, int);
	~Schoolboy();
	void set(std::string, std::string, int, int);
	//void get();
	Schoolboy operator+ (Schoolboy);
};