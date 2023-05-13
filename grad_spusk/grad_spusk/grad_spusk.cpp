
#include<iostream>
#include <cmath>
#include<vector>
using namespace std;

double f(const double x, const double y)
{
    return x* x + 6 * y * y + x * y + x;
}
double dfx(const double x, const double y)
{
    return 2 * x + y + 1;
}
double dfy(const double x, const double y)
{
    return 12 * y + x;
}


double g(double x, double y, double alpha)
{
    return f(x - alpha * dfx(x, y), y - alpha * dfy(x, y));
}
double Dihotomia(double a0, double b0, double epsilon, double x, double y)
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
        if (g(x, y, lk) <= g(x, y, mk)) {
            bk = mk;
        }
        else {
            ak = lk;
        }
    } while ((bk - ak) >= epsilon);

    x_ = (ak + bk) / 2;

    return x_;
}

double spusk(double x, double y, double N, double eps1, double eps2, int k)
{
    vector <double> min{ x,y };
    vector<double>x0 = { x,y };
    vector<double>grad = { dfx(x,y),dfy(x,y) };
    double norma1, norma2, alpha;

    for (k = 0; ; k++)
    {
        alpha = Dihotomia(-10000, 10000, eps1, x0[0], x0[1]);
        norma1 = sqrt(pow(grad[0], 2) + pow(grad[1], 2));

        if (norma1 < eps1)
        {
            min[0] = x0[0];
            min[1] = x0[1];
            break;
        }
        min[0] = x0[0];
        min[1] = x0[1];
        x0[0] = x0[0] - grad[0] * alpha;
        x0[1] = x0[1] - grad[1] * alpha;
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
    cout << "vvedite eps1 i eps2" << endl;
    cin >> eps1 >> eps2;
    cout << "vvedite N" << endl;
    cin >> N;
    cout << "t min" << endl;
    cout << spusk(x, y, N, eps1, eps2, k) << endl;


}
