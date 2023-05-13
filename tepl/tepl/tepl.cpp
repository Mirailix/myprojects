#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

double f(double x, double y, double t) {
    return 32 * (x * (1 - x) + y*(1 - y));
}
int main()
{
    setlocale(LC_ALL, "Ru");
    const int N = 20;
    double lx = 1;
    int ly = 1;
    int psi = 0;
    int u0 = 1;
    int t0 = 0;
    double** U,**F;
    double h = lx / N;
    double tau = 0.0001;
    double* x, * y;
    x = new double[N + 1];
    y = new double[N + 1];
    fstream file1;
    file1.open("file1.txt");

    for (int i = 0; i <= N; i++) {
        x[i] = y[i] = i * h;
    }

    U = new double* [N+1];
    F = new double* [N+1];
    for (int i = 0; i <= N; i++) {
        U[i] = new double[N+1];
        F[i] = new double[N+1];

    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            U[i][j] = 1;
            U[0][j] = 0;
            U[i][0] = 0;
            U[N ][j] = 0;
            U[i][N] = 0;
            cout << U[i][j] << " ";
        }
        cout << endl;
    }
    double t = t0 + tau;
    while (t < 50) {

        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                F[i][j] = f(x[i], y[j], t / 2);
            }
        }

        for (int j = 1; j < N ; j++) {
            for (int i = 1; i < N; i++) {
                U[j][i] = U[j][i] + tau * ((U[j + 1][i] - 2 * U[j][i] + U[j -1][i]) / (h * h) + (U[j][i + 1] - 2 * U[j][i] + U[j][i - 1]) / (h * h) + F[j][i]);
                //file1 << U[j][i] << " ";
            }
           //file1 << "\n";
        }
        t = t + tau;
    }
   
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            file1 << U[i][j] << "; ";
        }
       file1 << "\n";
    }
    file1.close();
}
/*

double f(double x) {
    return x* (3-x );
}

int main()
{
    setlocale(LC_ALL, "Ru");
    const int N = 20;
    double lx = 1;
    int ly = 1;
    int psi = 0;
    int u0 = 1;
    int t0 = 0;
    double** U, ** F;
    double h = lx / N;
    double tau = 0.0001;
    double* x, * y;
    x = new double[N + 1];
    y = new double[N + 1];
    fstream file1;
    file1.open("file1.txt");

    for (int i = 0; i <= N; i++) {
        x[i] = y[i] = i * h;
    }

    U = new double* [N + 1];
    F = new double* [N + 1];
    for (int i = 0; i <= N; i++) {
        U[i] = new double[N + 1];
        F[i] = new double[N + 1];

    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            U[i][j] = f(i*h);
        }
        cout << U[i][0]<<endl;
    }
    double t = t0 + tau;
    while (t < 50) {

      
        for (int j = 1; j < N; j++) {
                U[j][0] = U[j][0] + tau * ((U[j + 1][0] - 2 * U[j][0] + U[j - 1][0]) / (h * h) );
               
          
        }
        t = t + tau;
    }

    for (int i = 0; i <= N; i++) {
            file1 << U[i][0] << "\n ";
    }
    file1.close();
}
*/