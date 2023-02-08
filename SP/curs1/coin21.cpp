/*  SDD   */
#include "mlisp.h"
bool NOT_Q/*2*/ (double x_Q);
double first__denomination/*3*/ (double kind__of__coins);
double count__change/*12*/ (double amount);
bool pier_Q/*32*/ (double x_Q, double y_Q);
double cc/*35*/ (double amount, double kinds__of__coins);
double denomination__list/*44*/ (double kinds__of__coins);
double GR__AMOUNT/*49*/ ();
extern double VARIANT/*52*/ ;
extern double LAST__DIGIT__OF__GROUP__NUMBER/*53*/ ;
extern double KINDS__OF__COINS/*54*/ ;
//________________ 
bool NOT_Q/*2*/ (double x_Q){
 return
 (0. == (x_Q
	 ? 1.
	 :  (0.)));
}

double first__denomination/*3*/ (double kind__of__coins){
 return
 ((kind__of__coins == 1.)
	 ? 1.
	 :  (((kind__of__coins == 2.)
	 ? 3.
	 :  (((kind__of__coins == 3.)
	 ? 15.
	 :  (((kind__of__coins == 4.)
	 ? 20.
	 :  (((kind__of__coins == 5.)
	 ? 25.
	 :  (((kind__of__coins == 6.)
	 ? 50.
	 :  (0.))))))))))));
}

double count__change/*12*/ (double amount){
 display("______\n amount: ");
 display(amount);
 newline();
 display("KIND-OF-COINS: ");
 display(KINDS__OF__COINS);
 newline();
 {
	 double largest__coin(first__denomination(KINDS__OF__COINS));
	 display("largest-coin: ");
	 display(largest__coin);
	 newline();
	 return
	 (((0. < amount) && (0. < KINDS__OF__COINS) && (0. < largest__coin))
	 ? display("List of coinsdenominations: "),
	 denomination__list(KINDS__OF__COINS),
	 display("count-change= "),
	 cc(amount
	 , KINDS__OF__COINS)
	 
	 :  (display("Improper parameter value!\ncount-change= "),
	 -1.));
 }
}

bool pier_Q/*32*/ (double x_Q, double y_Q){
 return
 NOT_Q(NOT_Q((NOT_Q(x_Q) && NOT_Q(y_Q))));
}

double cc/*35*/ (double amount, double kinds__of__coins){
 return
 ((amount == 0.)
	 ? 1.
	 :  ((pier_Q((amount < 0.)
	 , (kinds__of__coins == 0.))
	 ? (cc(amount
	 , (kinds__of__coins - 1.))
	  + cc((amount - first__denomination(kinds__of__coins))
	 , kinds__of__coins)
	 )
	 :  (0.))));
}

double denomination__list/*44*/ (double kinds__of__coins){
 return
 ((kinds__of__coins == 0.)
	 ? newline(),
	 0.
	 :  (display(first__denomination(kinds__of__coins)),
	 display(" "),
	 denomination__list((kinds__of__coins - 1.))));
}

double GR__AMOUNT/*49*/ (){
 return
 remainder((+ (100. * LAST__DIGIT__OF__GROUP__NUMBER))
	 , 231.)
	 ;
}

double VARIANT/*52*/ = 25.;

double LAST__DIGIT__OF__GROUP__NUMBER/*53*/ = 6.;

double KINDS__OF__COINS/*54*/ = 6.;
int main(){
 display("Calculations!");
 newline();
 display("Variant ");
 display(VARIANT);
 newline();
 newline();
 display(count__change(100.));
 newline();
 display(count__change(GR__AMOUNT()));
 newline();
 KINDS__OF__COINS = 13.;
 display(count__change(100.));
 newline();
 display("(c) Strygin D.D. 2021\n");
 std::cin.get();
 return 0;
}

