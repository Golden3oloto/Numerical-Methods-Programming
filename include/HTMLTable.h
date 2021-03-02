#ifndef HTMLTABLE_H
#define HTMLTABLE_H

#include <initializer_list>
#include <string>
#include <vector>
#include <fstream>

typedef std::string HEAD;
typedef double DATA;

#define InitList(type) std::initializer_list<type>

class HTMLTable
{
private:
	int Width;
	int Height;

	HEAD* Header;
	std::vector<DATA*> Data;

public:
	std::string Title;
	std::string Style;
	std::string Header_style;

	HTMLTable(int width);
	HTMLTable(const InitList(HEAD) & list);
	~HTMLTable();

	int width() const;
	int height() const;
	const HEAD* const HTMLTable::header() const;
	const DATA* const operator[] (int line) const;


	HEAD* const header();
	void new_height(int new_height);
	void set_line(int line, const InitList(DATA) & list);
	DATA* const operator[](int line);
	void erase_line(int line);
	void swap_lines(int line1, int line2);

	friend bool insert(const HTMLTable& table, std::ofstream& fout);
};

void print(const HTMLTable& table);

#endif