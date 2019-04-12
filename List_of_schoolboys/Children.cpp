// файл реализации класса Children.cpp

#include "stdafx.h"
#include <string>

// подключаем интерфейс класса к файлу его реализации
#include "Children.h"

Children::Children()
{
	set("", "", 0);
}

Children::Children(const Children& ch)
{
	set(ch.name, ch.surname, ch.age);
}

Children::Children(std::string ch_name, std::string ch_surname, int ch_age)
{
	set(ch_name, ch_surname, ch_age);
}

Children::~Children()
{
	
}

void Children::set(std::string ch_name, std::string ch_surname, int ch_age)
{
	name = ch_name;
	surname = ch_surname;
	age = ch_age;
}

std::string Children::get_name() // функция (метод класса), возвращающая имя ребенка
{
	return (this->name);
}

Children& Children::operator+ (const Children& ch)
{
	Children* pch = new Children(this->name + ch.name, this->surname + ch.surname, this->age + ch.age);
	return *pch;
}

bool Children::operator< (const Children& ch)
{
	return (this->surname + this->name < ch.surname + ch.name);
}

Children& Children::operator= (const Children& ch)
{
	this->name = ch.name;
	this->surname = ch.surname;
	this->age = ch.age;
	return *this;  
}