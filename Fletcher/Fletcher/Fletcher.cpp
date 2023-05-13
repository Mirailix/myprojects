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


double g(double x, double y, double alpha, double d0, double d1)
{
    return f(x + alpha * d0, y +alpha * d1);
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
        if (g(x, y, lk,d0,d1) <= g(x, y, mk,d0,d1)) {
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
    vector<double>x_pred = { x,y };
    vector<double>grad = { dfx(x,y),dfy(x,y) };
    vector<double>d = { -dfx(x,y),-dfy(x,y) };
    double norma1, norma2, alpha;

    for (k = 0; ; k++)
    {
        
        norma1 = sqrt(pow(grad[0], 2) + pow(grad[1], 2));

        if (norma1 < eps1)
        {
            min[0] = x0[0];
            min[1] = x0[1];
            break;
        }
        min[0] = x0[0];
        min[1] = x0[1];


        if (k >= 1) {
            double b = (pow(dfx(x0[0], x0[1]), 2) + pow(dfy(x0[0], x0[1]), 2)) / (pow(dfx(x_pred[0], x_pred[1]), 2) + pow(dfy(x_pred[0], x_pred[1]), 2));
                d[0] = -dfx(x0[0], x0[1]) + b * d[0];
                d[1]= -dfy(x0[0], x0[1]) + b * d[1];
                //cout << pow(dfx(x0[0], x0[1]), 2) + pow(dfy(x0[0], x0[1]), 2)<<" //// "<< (pow(dfx(x_pred[0], x_pred[1]), 2) + pow(dfy(x_pred[0], x_pred[1]), 2))<<" "<< b << " b " << endl;
        }

        alpha = Dihotomia(-10000, 10000, eps1, x0[0], x0[1],d[0],d[1]);

        x_pred[0] = x0[0];
        x_pred[1] = x0[1]; 
        //cout << d[0] << " " << d[1] <<" d "<< endl;
        
        //cout << alpha << " alpha" << endl;
        x0[0] = x0[0] - grad[0] * alpha;
        x0[1] = x0[1] - grad[1] * alpha;
        grad = { dfx(x0[0],x0[1]),dfy(x0[0],x0[1]) };
        //cout << x0[0] << " " << x0[1] << endl;
        //cout << grad[0] << " " << grad[1] << " grad" << endl;

       
        norma2 = sqrt(pow(x0[0] - min[0], 2) + pow(x0[1] - min[1], 2));
       // cout << norma2 << " norma" << endl;
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
