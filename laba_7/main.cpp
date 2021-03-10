#include "HTMLTable.h"
#include "config.h"

#define HTML_FILE_PATH IN_RESOURCE_DIR(laba7.html)

const int MATRIX_SIZE = 4;

int main()
{
	HTMLTable input_matrix(MATRIX_SIZE);
	HTMLTable output_matrix(MATRIX_SIZE);

	input_matrix.new_height(MATRIX_SIZE);
	output_matrix.new_height(MATRIX_SIZE);

	input_matrix.Title = "Input";
	output_matrix.Title = "Output";

	input_matrix.Style = "class ='first' ";
	output_matrix.Style = "class = 'second' ";


	input_matrix.set_line(0, { 0.98,	-1.66,	-2.58,	-3.89 });
	input_matrix.set_line(1, { 0.45,	0.99,	-3.26,	-3.86 });
	input_matrix.set_line(2, { 1.40,	1.14,	3.01,	1.06 });
	input_matrix.set_line(3, { 2.62,	2.07,	-0.96,	-1.20 });

	/*input_matrix.set_line(0, { 8.79,	-2.28,	0.24,	0.695 });
	input_matrix.set_line(1, { -0.65,	6.181,	-0.84,	1.85 });
	input_matrix.set_line(2, { -1.395,	0.965,	5.135,	0.775 });
	input_matrix.set_line(3, { -1.285,	-2.43,	-1.125,	4.219 });*/

	for (int i = 0; i < output_matrix.width(); i++)
		output_matrix[i][i] = 1;

	std::ofstream fout;
	fout.open(HTML_FILE_PATH);

	fout << u8"<link rel = 'stylesheet' href ='matrix.css'>";

	fout << u8"<div class ='merge'>";
	insert(input_matrix, fout);
	insert(output_matrix, fout);
	fout << u8"</div>";

	fout << u8"<hr><h1 align = 'center'>Direct traversal</h1>";

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if (input_matrix[i][i] == 0)
		{
			fout.close();
			return 0;
		}

		for (int j = 0; j < MATRIX_SIZE; j++)
			output_matrix[i][j] /= input_matrix[i][i];

		for (int j = MATRIX_SIZE - 1; j >= i; j--)
			input_matrix[i][j] /= input_matrix[i][i];

		for (int j = i + 1; j < MATRIX_SIZE; j++)
		{
			for (int k = 0; k <= j; k++)
				output_matrix[j][k] -= output_matrix[i][k] * input_matrix[j][i];

			for (int k = MATRIX_SIZE - 1; k >= i; k--)
				input_matrix[j][k] -= input_matrix[i][k] * input_matrix[j][i];
		}

		fout << u8"<h4 align ='center'>Step " << i + 1 << "</h4>";

		fout << u8"<div class ='merge'>";
		insert(input_matrix, fout);
		insert(output_matrix, fout);
		fout << u8"</div>";
	}

	fout << u8"<hr><h1 align = 'center'>Reverse bypass</h1>";

	for (int i = MATRIX_SIZE -1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < MATRIX_SIZE; k++)
				output_matrix[j][k] -= output_matrix[i][k] * input_matrix[j][i];
			input_matrix[j][i] = 0;
		}

		fout << u8"<h4 align ='center'>Step " << MATRIX_SIZE -i << "</h4>";

		fout << u8"<div class ='merge'>";
		insert(input_matrix, fout);
		insert(output_matrix, fout);
		fout << u8"</div>";
	}

	fout << u8"<hr><h1 align = 'center'>Result</h1>";

	output_matrix.Style = "class ='HTMLTable' ";
	insert(output_matrix, fout);

	fout.close();
	system(HTML_FILE_PATH);
}