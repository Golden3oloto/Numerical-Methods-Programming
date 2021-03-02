#include <cmath>
#include "HTMLTable.h"
#include "config.h"

#define HTML_FILE_PATH IN_RESOURCE_DIR(laba3.html)

double f(double x)
{
	return exp(x) + 2.45 * x + 0.57;
}

double d_f(double x)
{
	return exp(x) + 2.45;
}

const double e = 0.000001;

int main()
{
	const double left_border = -1.0;
	const double right_border = 0.0;

	double x_0;
	double x_border;

	if (abs(d_f(left_border)) > abs(d_f(right_border)))
	{
		x_0 = right_border;
		x_border = left_border;
	}
	else
	{
		x_0 = left_border;
		x_border = right_border;
	}

	double m = d_f(x_0);

	HTMLTable table = { "i", "xi", "f(xi)", "|f(xi)/m|" };
	table.Title = "chord method";

	int i =0;
	double x_i = x_0;
	do
	{
		x_i = x_i - f(x_i) * (x_border - x_i) / (f(x_border) - f(x_i));
		i++;
		table.set_line(i -1, { (double)i, x_i, f(x_i),  abs(f(x_i) / m) });

	} while (abs( f(x_i) / m) > e);

	std::ofstream fout;
	fout.open(HTML_FILE_PATH);

	fout << u8"<link rel = 'stylesheet' href ='table.css'>";
	insert(table, fout);

	fout.close();
	system(HTML_FILE_PATH);
}