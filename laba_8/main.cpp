#include "HTMLTable.h"
#include "config.h"

#define HTML_FILE_PATH IN_RESOURCE_DIR(laba8.html)

const int ROOTS_NUM = 4;
const int NUM_OF_IT = 15;

const double e = 0.0001;

int main()
{
	HTMLTable A_matrix(ROOTS_NUM +1);
	A_matrix.Title = "input";

	A_matrix.new_height(ROOTS_NUM);

	A_matrix.set_line(0, { 14.72, 1.45, 3.88, -4.17, -35.70 });
	A_matrix.set_line(1, { -3.16,-12.79, 3.49, 4.28, 11.04 });
	A_matrix.set_line(2, { -4.62, 2.93, -15.95, 3.26, 10.37 });
	A_matrix.set_line(3, { 1.03, 3.85, -1.18, -11.95, -8.85 });

	double B_matrix[ROOTS_NUM][ROOTS_NUM +1];
	double X_matrix_old[ROOTS_NUM];
	double X_matrix_new[ROOTS_NUM];

	for (int i = 0; i < ROOTS_NUM; i++)
		X_matrix_old[i]= 0;


	for (int i = 0, j; i < ROOTS_NUM; i++)
	{
		for (j = 0; j < ROOTS_NUM; j++)
		{
			if (A_matrix[i][j] == 0)
				return 0;
			B_matrix[i][j] = -A_matrix[i][j] / A_matrix[i][i];
		}
		B_matrix[i][j] = A_matrix[i][j] / A_matrix[i][i];
		B_matrix[i][i] = 0;
	}

	double teta =0;

	for (int i = 0; i < ROOTS_NUM; i++)
	{
		double sum = 0;
		for (int j = 0; j < ROOTS_NUM; j++)
			sum += std::abs(B_matrix[i][j]);
		if (sum > teta)
			teta = sum;
	}


	double max;
	do
	{
		for (int j = 0, k; j < ROOTS_NUM; j++)
		{
			double sum = 0;
			for (k = 0; k < ROOTS_NUM; k++)
 				sum += B_matrix[j][k] * X_matrix_old[k];
			sum += B_matrix[j][k];
			X_matrix_new[j] = sum;
		}

		max = std::abs(X_matrix_new[0] - X_matrix_old[0]);

		for (int j = 1; j < ROOTS_NUM; j++)
		{
			if (std::abs(X_matrix_new[j] - X_matrix_old[j]) > max)
				max = std::abs(X_matrix_new[j] - X_matrix_old[j]);
		}

		std::swap(X_matrix_old, X_matrix_new);

	} while (max*teta/(1-teta) > e);

	std::ofstream fout;
	fout.open(HTML_FILE_PATH);

	fout << u8"<link rel = 'stylesheet' href ='matrix.css'>";
	insert(A_matrix, fout);

	fout << u8"<hr><h2 align = 'center'>Results</h2>";

	for (int i = 0; i < ROOTS_NUM; i++)
	{
		fout << u8"<p>x " << i + 1 << u8" = " << X_matrix_old[i] << u8"</p>";
	}

	fout.close();
	system(HTML_FILE_PATH);
}