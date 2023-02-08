/*  SDD   */
#include "mlisp.h"
double day__of__week/*2*/ ();
double zeller/*9*/ (double d, double m
	 , double y, double c);
double neg__to__pos/*19*/ (double d);
double birthday/*24*/ (double dw);
extern double dd/*39*/ ;
extern double mm/*40*/ ;
extern double yyyy/*41*/ ;
//________________ 
double day__of__week/*2*/ (){
 return
 zeller(dd
	 , ((mm < 3.)
	 ? (mm + 10.)
	 :  ((mm - 2.)))
	 , remainder(((mm < 3.)
	 ? (yyyy - 1.)
	 :  (yyyy))
	 , 100.)
	 
	 , quotient(((mm < 3.)
	 ? (yyyy - 1.)
	 :  (yyyy))
	 , 100.)
	 )
	 ;
}

double zeller/*9*/ (double d, double m
	 , double y, double c){
 return
 neg__to__pos(remainder((d + y + quotient(((26. * m) - 2.)
	 , 10.)
	  + quotient(y
	 , 4.)
	  + quotient(c
	 , 4.)
	  + (2. * (- c)))
	 , 7.)
	 );
}

double neg__to__pos/*19*/ (double d){
 return
 ((d < 0.)
	 ? (d + 7.)
	 :  (d));
}

double birthday/*24*/ (double dw){
 display("Your were born on ");
 display(((dw == 1.)
	? "Monday "
	: (dw == 2.)
	? "Tuesday "
	: (dw == 3.)
	? "Wednesday "
	: (dw == 4.)
	? "Thursday "
	: (dw == 5.)
	? "Friday "
	: (dw == 6.)
	? "Saturday "
	: ("Sunday ")));
 display(dd);
 display(".");
 display(mm);
 display(".");
 return
 yyyy;
}

double dd/*39*/ = 28.;

double mm/*40*/ = 04.;

double yyyy/*41*/ = 2002.;
int main(){
 display("Calculations!");
 newline();
 display(birthday(day__of__week()));
 newline();
 std::cin.get();
 return 0;
}

