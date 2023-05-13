#include<iostream>
#include <cmath>
#include<vector>
using namespace std;

double f(const double x, const double y)
{
    return x * x + 6 * y * y + x * y + x;
}
double dfx(const double x, const double y)
{
    return 2 * x + y + 1;
}
double dfy(const double x, const double y)
{
    return 12 * y + x;
}
double d2fx(double x, double y) {
    return 2;
}
double d2fy(double x, double y) {
    return 12;
}
double d2fxy(double x, double y) {
    return 1;
}


double g(double x, double y, double alpha, double d0, double d1)
{
    return f(x + alpha * d0, y + alpha * d1);
}
double Dihotomia(double a0, double b0, double epsilon, double x, double y, double d0, double d1)
{

    int k;
    double lk, mk;
    double delta = 0.5 * epsilon;
    double x_;
    double ak = a0, bk = b0;
    k = 1;
    do {
        lk = (ak + bk - delta) / 2;
        mk = (ak + bk + delta) / 2;
        k++;
        if (g(x, y, lk, d0, d1) <= g(x, y, mk, d0, d1)) {
            bk = mk;
        }
        else {
            ak = lk;
        }
    } while ((bk - ak) >= epsilon);

    x_ = (ak + bk) / 2;

    return x_;
}

void inversion(double** A, int N)
{
    double temp;

    double** E = new double* [N];

    for (int i = 0; i < N; i++)
        E[i] = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;

            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = A[k][k];

        for (int j = 0; j < N; j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

    for (int i = 0; i < N; i++)
        delete[] E[i];

    delete[] E;
}

double spusk(double x, double y, double N, double eps1, double eps2, int k)
{
    vector <double> min{ x,y };
    vector<double>x0 = { x,y };
    vector<double>x_pred = { x,y };
    vector<double>grad = { dfx(x,y),dfy(x,y) };
    vector<double>d = { dfx(x,y),dfy(x,y) };
    vector<double>d1 = { dfx(x,y),dfy(x,y) };
    double norma1, norma2, alpha;

    for (k = 0; ; k++)
    {
        double** H = new double* [2];
        for (int i = 0; i < 2; i++)
            H[i] = new double[2];



        H[0][0] = d2fx(x0[0], x0[1]); H[0][1] = d2fxy(x0[0], x0[1]);
        H[1][0] = d2fxy(x0[0], x0[1]); H[1][1] = d2fy(x0[0], x0[1]);
        inversion(H, 2);
        norma1 = sqrt(pow(grad[0], 2) + pow(grad[1], 2));

        if (norma1 < eps1)
        {
            min[0] = x0[0];
            min[1] = x0[1];
            break;
        }
        min[0] = x0[0];
        min[1] = x0[1];

        double opr = H[1][1] * H[0][0] - H[0][1] * H[1][0];

        if (opr > 0) {
            for (int i = 0; i < 2; i++)
            {
                float temp = 0;
                for (int j = 0; j < 2; j++)
                {
                    temp += H[i][j] * d[j];
                }
                d1[i] = -temp;
            }
        }
        else {
            d1[0] = -dfx(x0[0], x0[1]);
            d1[1] = -dfy(x0[0], x0[1]);
        }


        alpha = Dihotomia(-10000, 10000, eps1, x0[0], x0[1], d1[0], d1[1]);



        x0[0] = x0[0] + alpha*d1[0];
        x0[1] = x0[1] + alpha*d1[1];
        grad = { dfx(x0[0],x0[1]),dfy(x0[0],x0[1]) };


        norma2 = sqrt(pow(x0[0] - min[0], 2) + pow(x0[1] - min[1], 2));
        if (k >= 1 && norma2 < eps2)
        {
            min[0] = x0[0];
            min[1] = x0[1];
            break;
        }
        if (k == N)
        {
            min[0] = x0[0];
            min[1] = x0[1];
            break;
        }
        d[0] = d1[0];
        d[1] = d1[1];

    }
    cout << "Точка минимума" << x0[0] << " " << x0[1] << endl;
    cout << "Количество итераций " << k << endl;
    //cout << "Значение градиента на последнем шаге " << grad[0] << " " << grad[1] << endl;
    //cout << "Значение нормы градиента на последнем шаге " << sqrt(pow(grad[0], 2) + pow(grad[1], 2)) << endl;
    return f(min[0], min[1]);
}

int main()
{
    setlocale(LC_ALL, "RUS");
    double x, y, N, k = 0;
    cout << "Введите начальные координаты" << endl;
    cin >> x >> y;

    double eps1, eps2;
    cout << "Введите eps1 и eps2" << endl;
    cin >> eps1 >> eps2;
    cout << "Введите N" << endl;
    cin >> N;
    cout << spusk(x, y, N, eps1, eps2, k) << endl;

}
