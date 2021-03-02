#include "HTMLTable.h"
#include <iostream>

#define DEF_TITLE "table"
#define DEF_STYTE "class ='HTMLTable' "
#define DEF_HEADER_STYLE "class ='HTMLTableHeader' "

#pragma warning(push)
#pragma warning(disable:6385)//menya eto predyprejdenie zaebalo

HTMLTable::HTMLTable(int width)
{
	Width = width;
	Height = 0;
	Header = nullptr;

	Title = DEF_TITLE;
	Style = DEF_STYTE;
	Header_style = DEF_HEADER_STYLE;
}

HTMLTable::HTMLTable(const InitList(HEAD) & list) : HTMLTable::HTMLTable((int)list.size())
{
	int count =0;
	Header = new HEAD[Width];

	for (HEAD element : list)
	{
		Header[count] = element;
		count++;
	}
}

HTMLTable::~HTMLTable()
{
	if(Header != nullptr)
		delete[] Header;

	for (int i = 0; i < Height; i++)
		delete[] Data[i];
	Data.clear();
}



int HTMLTable::height() const { return Height; }

int HTMLTable::width() const { return Width; }

const HEAD* const HTMLTable::header() const { return Header; }

const DATA* const HTMLTable::operator[] (int line) const
{
	if (line >= Height || line < 0)
		return nullptr;
	return Data[line];
}



HEAD* const HTMLTable::header() 
{
	if (Header == nullptr)
		Header = new HEAD[Width];
	return Header; 
}

void HTMLTable::new_height(int new_height)
{
	if (new_height > Height)
	{
		Data.resize(new_height);
		for (int i = Height; i < new_height; i++)
		{
			Data[i] = new DATA[Width];
			for (int j = 0; j < Width; j++)
				Data[i][j] = DATA();
		}
	}
	else if (new_height < Height)
	{
		for (int i = new_height; i < Height; i++)
			delete[] Data[i];

		Data.resize(new_height);
	}

	Height = new_height;
}

void HTMLTable::set_line(int line, const InitList(DATA) & list)
{
	if (line < 0 || list.size() > Width)
		return;
	if (line >= Height)
		this->new_height(line +1);

	int count =0;
	for (DATA element : list)
	{
		Data[line][count] = element;
		count++;
	}
	
}

DATA* const HTMLTable::operator[](int line)
{
	if (line < 0)
		return nullptr;
	if (line >= Height)
		this->new_height(line +1);
	return Data[line];
}

void HTMLTable::erase_line(int line)
{
	if (line >= Height || line < 0)
		return;
	delete[] Data[line];
	Data.erase(Data.begin() + line);
	Height--;
}

void HTMLTable::swap_lines(int line1, int line2)
{
	if (line1 == line2)
		return;
	DATA* temp = Data[line1];
	Data[line1] = Data[line2];
	Data[line2] = temp;
}



bool insert(const HTMLTable& table, std::ofstream& fout)
{
	if (!fout.is_open())
		return false;
	 
	fout << u8"<table " << table.Style << u8" >";

	fout << u8"<caption>" << table.Title << u8"</caption>";

	if (table.Header != nullptr)
	{
		fout << u8"<tr " << table.Header_style << u8" >";
		for (int i = 0; i < table.Width; i++)
			fout << u8"<td>" << table.Header[i] << u8"</td>";
		fout << u8"</tr>";
	}

	for (int i = 0; i < table.Height; i++)
	{
		fout << u8"<tr>";
		for (int j = 0; j < table.Width; j++)
		{
			fout << u8"<td>" << table[i][j] << u8"</td>";
		}
		fout << u8"</tr>";
	}

	fout << u8"</table>";
	return true;
}

void print(const HTMLTable & table)
{
	for (int i = 0; i < table.width(); i++)
		std::cout << table.header()[i] << '\t';

	std::cout << std::endl;

	for (int i = 0; i < table.height(); i++)
	{
		for (int j = 0; j < table.width(); j++)
			std::cout << table[i][j] << '\t';

		std::cout << std::endl;
	}
}

#pragma warning(pop)