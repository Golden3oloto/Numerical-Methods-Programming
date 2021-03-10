#include "HTMLTable.h"
#include "config.h"

#define HTML_FILE_PATH IN_RESOURCE_DIR(laba6.html)

const int MATRIX_SIZE = 4;

int main()
{
	HTMLTable matrix(MATRIX_SIZE);
	matrix.new_height(MATRIX_SIZE);
	matrix.Title = "Original matrix";

	matrix.set_line(0, { -2.28,	-2.23,	3.06,	-3.20});
	matrix.set_line(1, {  3.6,	-0.40,	2.35,	-2.08});
	matrix.set_line(2, { -0.60,	-3.01,	0.28,	-1.50});
	matrix.set_line(3, { -0.37,	1.25,	-3.08,	1.81});

	std::ofstream fout;
	fout.open(HTML_FILE_PATH);

	fout << u8"<link rel = 'stylesheet' href ='matrix.css'>";
	insert(matrix, fout);

	fout << u8"<hr><h2 align = 'center'>Direct traversal</h2>";

	for (int i = 0; i < matrix.width(); i++)
	{
		if (matrix[i][i] == 0)
		{
			fout.close();
			return 0;
		}

		for (int j = i +1; j < matrix.height(); j++)
		{
			for (int k = i +1; k < matrix.width(); k++)
				matrix[j][k] -= matrix[j][i] / matrix[i][i] * matrix[i][k];

			matrix[j][i] = 0;
		}

		matrix.Title = "Step " + std::to_string(i + 1);
		insert(matrix, fout);
	}


	fout << u8"<hr><h2 align = 'center'>Determinant</h2>";

	double det = 1;
	for (int i = 0; i < MATRIX_SIZE; i++)
		det *= matrix[i][i];

	fout << u8"<p align ='center'>det(A) = " << det << u8"</p>";

	fout.close();
	system(HTML_FILE_PATH);
}