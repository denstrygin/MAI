#include "mlisp.h"

double fun(double x);
double golden__section__search(double a, double b);
double golden__start(double a, double b);
double __SDD__try(double a, double b, double xa, double ya, double xb, double yb);
double close__enough_Q(double x, double y);
extern double a;
extern double b;
extern double tolerance;
extern double total__iterations;
extern double xmin;
extern double mphi;



double tolerance = 0.001;
double a = 7.;
double b = 9.;
double total__iterations = 0.;
double xmin = 0.;
double mphi = (3. - sqrt(5.))*(1. / 2.0);

double fun(double x){
    x = x - (25. / 26.);
    return ((-x) + sin(x) + expt((x - 7.), 4.) + 0.3);
}

double golden__section__search(double a, double b){
    double xmin(a < b ? golden__start(a, b) : golden__start(b, a));
    newline();
    return xmin;
}

double golden__start(double a, double b){
    total__iterations = 0.;
    double xa(a + mphi * (b - a))
        , xb(b + (- mphi * (b - a)));
    return __SDD__try(a, b, xa, fun(xa), xb, fun(xb));
}

double __SDD__try(double a, double b, double xa, double ya, double xb, double yb){
    return (close__enough_Q(a, b) ?
        (a + b) * 0.5 : (
            display("+")
            , total__iterations = total__iterations + 1.
            , (ya < yb ? 
                ( 
                    b = xb
                    , xb = xa
                    , yb = ya
                    , xa = a + mphi * (b - a)
                    , __SDD__try(a, b, xa, fun(xa), xb, yb)
                ) : 
                (
                a = xa
                , xa = xb
                , ya = yb
                , xb = b - mphi * (b - a)
                , __SDD__try(a, b, xa, ya, xb, fun(xb))
                )
            )
        )
    );
}

double close__enough_Q(double x, double y){
    return (abs(x - y) < tolerance);
}

int main(){
    xmin = golden__section__search(a, b);
    display("Interval=\t[");
    display(a);
    display(", ");
    display(b);
    display("]\n");
    display("Total number of iterations=");
    display(total__iterations);
    display("\n");
    display("xmin=\t\t");
    display(xmin);
    display("\n");
    display("f(xmin)=\t");
    display(fun(xmin));
    newline();
    std::cin.get();
    return 0;
}