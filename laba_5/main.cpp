#include "HTMLTable.h"
#include "config.h"

#define HTML_FILE_PATH IN_RESOURCE_DIR(laba5.html)

const int ROOT_NUM = 10;

int main()
{
	HTMLTable matrix(ROOT_NUM + 1);
	matrix.new_height(ROOT_NUM);
	matrix.Title = "Original matrix";

	/*matrix.set_line(0, { -0.96,	3.53,	-3.34,	2.56,	8.85 });
	matrix.set_line(1, { -2.0,	-2.64,	3.95,	3.68,	1.13 });
	matrix.set_line(2, { 1.0,	2.75,	2.2,	-3.74,	7.39 });
	matrix.set_line(3, { 1.55,	-0.99,	-1.48,	-0.43,	3.6 });*/ 

	for (int i = 0; i < ROOT_NUM; i++)
	{
		matrix[i][i] = 10;
		matrix[i][ROOT_NUM] = 10;
	}

	std::ofstream fout;
	fout.open(HTML_FILE_PATH);

	fout << u8"<link rel = 'stylesheet' href ='matrix.css'>";
	insert(matrix, fout);


	fout << u8"<hr><h2 align = 'center'>Direct traversal</h2>";

	for (int i = 0; i < matrix.width() - 1; i++)
	{
		if (matrix[i][i] == 0)
		{
			int l;
			for (l = i; l < ROOT_NUM; l++)
			{
				if (matrix[l][i] != 0)
				{
					matrix.swap_lines(i, l);
					break;
				}
			}
			if (l == ROOT_NUM)
			{
				fout.close();
				return 0;
			}
		}

		for (int j = matrix.width() -1; j >= i; j--)
		{
			matrix[i][j] /= matrix[i][i];

			for (int k = i + 1; k < matrix.height(); k++)
				matrix[k][j] -= matrix[i][j] * matrix[k][i];
		}

		matrix.Title = "Step " + std::to_string(i + 1);
		insert(matrix, fout);
	}


	fout << u8"<hr><h2 align = 'center'>Results</h2>";



	double root[ROOT_NUM];
	for (int i = ROOT_NUM - 1; i >= 0; i--)
	{
		root[i] = matrix[i][matrix.width() - 1];
		for (int j = i + 1; j < ROOT_NUM; j++)
		{
			root[i] -= matrix[i][j] * root[j];
		}

		fout << u8"<p>x " << i + 1 << u8" = " << root[i] << u8"</p>";
	}

	fout.close();
	system(HTML_FILE_PATH);
}