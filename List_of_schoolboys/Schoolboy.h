#pragma once
#include "Children.h"


class Schoolboy : public Children
{
private:
	/* ������ ������� � ������� ��� ������������� ������ ������ */
	

public:
	/* ������ ������� � ������� ��������� ������ �������� � �������� ��������� */
	int ball;
	Schoolboy();
	Schoolboy(const Schoolboy&);
	Schoolboy (std::string, std::string, int, int);
	~Schoolboy();
	void set(std::string, std::string, int, int);
	//void get();
	Schoolboy operator+ (Schoolboy);
};