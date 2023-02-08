/*  SDD   */
#include "mlisp.h"
extern double a/*2*/ ;
extern double b/*2*/ ;
double fun/*3*/ (double x);
double golden__section__search/*7*/ (double a, double b);
double golden__start/*15*/ (double a, double b);
extern double mphi/*24*/ ;
double __SDD__try/*25*/ (double a, double b
	 , double xa, double ya
	 , double xb, double yb);
bool close__enough_Q/*45*/ (double x, double y);
extern double tolerance/*47*/ ;
extern double total__iterations/*48*/ ;
extern double xmin/*49*/ ;
//________________ 
double a/*2*/ = 7.;

double b/*2*/ = 9.;

double fun/*3*/ (double x){
 x = (x - (25. / 26.));
 return
 ((sin(x) + expt((x - 7.)
	 , 4.)
	  + +0.3e-0) - x);
}

double golden__section__search/*7*/ (double a, double b){
 {
	 double xmin(((a < b)
	 ? golden__start(a
	 , b)
	 
	 :  (golden__start(b
	 , a)
	 )));
	 newline();
	 return
	 xmin;
 }
}

double golden__start/*15*/ (double a, double b){
 total__iterations = 0.;
 {
	 double xa((a + (mphi * (b - a)))),
	 xb((b + (- (mphi * (b - a)))));
	 return
	 __SDD__try(a
	 , b
	 , xa
	 , fun(xa)
	 , xb
	 , fun(xb))
	 ;
 }
}

double mphi/*24*/ = ((3. - sqrt(5.)) * (1. / +2.e-0));

double __SDD__try/*25*/ (double a, double b
	 , double xa, double ya
	 , double xb, double yb){
 return
 (close__enough_Q(a
	 , b)
	 ? ((a + b) * +0.5e-0)
	 :  (display("+"),
	 total__iterations = (total__iterations + 1.),
	 ((ya < yb)
	 ? b = xb,
	 xb = xa,
	 yb = ya,
	 xa = (a + (mphi * (b - a))),
	 __SDD__try(a
	 , b
	 , xa
	 , fun(xa)
	 , xb
	 , yb)
	 
	 :  (a = xa,
	 xa = xb,
	 ya = yb,
	 xb = (b - (mphi * (b - a))),
	 __SDD__try(a
	 , b
	 , xa
	 , ya
	 , xb
	 , fun(xb))
	 ))));
}

bool close__enough_Q/*45*/ (double x, double y){
 return
 (abs((x - y)) < tolerance);
}

double tolerance/*47*/ = +1.e-3;

double total__iterations/*48*/ = 0.;

double xmin/*49*/ = 0.;
int main(){
 display("Calculations!");
 newline();
 xmin = golden__section__search(a
	 , b)
	 ;
 display("Interval=\t[");
 display(a);
 display(" , ");
 display(b);
 display("]\n");
 display("Total number of iteranions=");
 display(total__iterations);
 newline();
 display("xmin=\t\t");
 display(xmin);
 newline();
 display("f(xmin)=\t");
 display(fun(xmin));
 newline();
 std::cin.get();
 return 0;
}

