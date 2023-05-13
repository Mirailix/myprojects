#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

double f1(double x)
{
	return x;
}

int main()
{
	setlocale(LC_ALL,"RUS");
	int A = 0, B = 0;
	int al = 0, bl = 1;
	double p=1, q=0,x=0;
	
	
	cout << "Введите шаг: " << endl;
	//cin >> h;
	double h = 0.02;
	int n = fabs(bl - al) / h;
	
	double** matrix;
	double* f=new double[n];
	
	matrix = new double* [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new double[n];
	}
	for (int i= 1; i < n-1; i++)
	{
		f[i] = (f1(x) * h * h);
		x = x + h;
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				matrix[i][j] = -(2 +(h*p)-(h*h*q));
			else if ((j - i) == 1)
				matrix[i][j] = (1+h*p);
			else if ((i - j) == 1)
				matrix[i][j] = 1;
			else {
				matrix[i][j] = 0;
			}
		}
		
	}

	for (int i = 0; i < n; i++) {
		if (i != 1)
			matrix[0][i] = 0;
		if (i != n - 1 && i != n - 2)
			matrix[n - 1][i] = 0;
	}
	//matrix[0][0] = -(2 + h * p - h * h * q);
	//matrix[0][1] = 1 + h * p;
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	f[0] = A;
	matrix[n-1][n-2] = -1;
	matrix[n-1][n-1] = 1;
	f[n-1] = h * B;

	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++) {
			//cout << matrix[i][j] << " ";
		}
		//cout << endl;
	}


	double *a = new double[n];
	double* b = new double[n];
	double* g = new double[n];
	double* y = new double[n];

	g[0] = matrix[0][0];
	a[0] = -matrix[0][1] / g[0];
	b[0] = f[0] / g[0];
	for (int i = 1; i <n-1; i++) {
		g[i] = matrix[i][i] + matrix[i][i - 1] * a[i - 1];
		a[i] = -matrix[i][i + 1] / g[i];
		b[i] = (f[i] - matrix[i][i - 1] * b[i - 1])/g[i];
		
		
	}
	g[n-1] = matrix[n-1][n-1] + matrix[n-1][n - 2] * a[n-2];
	b[n-1] = (f[n-1] - matrix[n-1][n-2] * b[n-2]) / g[n-1];


	y[n - 1] =b[n - 1];
	cout << y[n - 1] << endl;
	for (int i = n - 2; i >= 0; i--) {
		y[i] = a[i] * y[i + 1] + b[i];
	}
	cout << a[n - 2] << " " << y[n - 1] << " " << b[n - 2] << endl;

	fstream file;
	
	file.open("file.txt");

	for (int i = 0; i < n; i++) {
	 cout << y[i] <<" "<<i<< endl;
	}

	file.close();

	


}