
#include <iostream>
#include <fstream>
#include<math.h>
using namespace std;
double f1(double x, double y, double z) {
    return 2 * z - y;
    //return x*z-2*x*y + 0.8;
}
double f2(double x, double y, double z){
    return 4 * z - 3 * y + exp(3 * x) / (exp(2*x) + 1);
    //return z;
}

int main()
{

    const int n = 2;
    double f[n];
    double a = 0;
    double b = 3;
    double h = 0.1;
    double x0 = 0;
    double y0 = 3.87765;
    double z0 = 5.66305;
    fstream file1, file2;
    file1.open("file1.txt");
    file2.open("file1.txt");
    cout << x0 << " " << y0 <<" "<<z0<< endl;
    while (x0 + h < b) {

        double k1 = h*f1(x0, y0, z0);
        double l1= h*f2(x0, y0, z0);

        double x = x0 + h / 2;

        double k2 = h*f1(x, y0 + k1 / 2,z0+l1/2);
        double l2 = h*f2(x, y0 + k1 / 2, z0 + l1 / 2);

        double k3 = h*f1(x, y0 + k2 / 2, z0 + l2 / 2);
        double l3 = h*f2(x, y0 + k2 / 2, z0 + l2 / 2);

        x = x + h / 2;
        double k4 = h*f1(x, y0 + k3, z0+l3);
        double l4 = h*f2(x, y0 + k3, z0 + l3);
        x0 = x;

        y0 = y0 +  (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        z0 = z0 +  (l1 + 2 * l2 + 2 * l3 + l4) / 6;
        cout << x << " " << y0 << " "<<z0<< endl;
        file1 << y0 << endl;
        file2 << z0 << endl;

    }
    file1.close();
    file2.close();
}
