#include <cmath>
#include "HTMLTable.h"
#include "config.h"

#define HTML_FILE_PATH IN_RESOURCE_DIR(laba4.html)

//		sqrt(x+1) -1/x =0 
//		1/sqrt(x+1) = x

double f(double x)
{
	return 1.0 / sqrt(x + 1.0);
}

const double e = 0.0001;

int main()
{
	const double teta = 0.5;

	double x_i = 0.0;

	HTMLTable table = { "i", "xi", "|f(xi) -xi|", "|xi - x(i-1)|" };
	table.Title = "iteration method";


	double x_i_pre;
	int i = 0;
	do
	{
		i++;
		x_i_pre = x_i;
		x_i = f(x_i);

		table.set_line(i - 1, { (double)i, x_i, abs(f(x_i) - x_i), abs(x_i - x_i_pre) });

	} while (abs(x_i - x_i_pre) > teta / (1.0 - teta) * e);

	std::ofstream fout;
	fout.open(HTML_FILE_PATH);

	fout << u8"<link rel = 'stylesheet' href ='table.css'>";
	insert(table, fout);

	fout.close();
	system(HTML_FILE_PATH);
}