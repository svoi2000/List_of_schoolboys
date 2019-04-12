#pragma once
#include <string>
#include <algorithm>


class Children
{
protected:
	/* ������ ������� � ������� ��� ������������� ������ ������ */
	int age;

public:
	std::string name, surname;
	/* ������ ������� ��������� ������ �������� � �������� ��������� */
	Children();
	Children(const Children&);
	Children(std::string, std::string, int);
	~Children();
	void set(std::string, std::string, int);
	//void get();
	std::string get_name();
	Children& operator+ (const Children&);
	bool operator< (const Children&);
	Children& operator= (const Children&);
};