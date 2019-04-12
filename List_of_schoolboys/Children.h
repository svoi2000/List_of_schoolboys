#pragma once
#include <string>
#include <algorithm>


class Children
{
protected:
	/* список свойств и методов для использования внутри класса */
	int age;

public:
	std::string name, surname;
	/* список методов доступных другим функциям и объектам программы */
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