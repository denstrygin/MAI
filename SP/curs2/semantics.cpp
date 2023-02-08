/* $n25 */
#include "semantics.h"
using namespace std;
void tSM::init(){
	return;}
int tSM::p01(){ //        S -> PROG
	return 0;}
int tSM::p02(){ //     PROG -> CALCS
	return 0;}
int tSM::p03(){ //     PROG -> DEFS
	return 0;}
int tSM::p04(){ //     PROG -> DEFS CALCS
	return 0;}
int tSM::p05(){ //        E -> $id
	return 0;}
int tSM::p06(){ //        E -> $int
	return 0;}
int tSM::p07(){ //        E -> $dec
	return 0;}
int tSM::p08(){ //        E -> AREX
	return 0;}
int tSM::p09(){ //        E -> COND
	return 0;}
int tSM::p10(){ //        E -> CPROC
	return 0;}
int tSM::p11(){ //     AREX -> HAREX E )
	return 0;}
int tSM::p12(){ //    HAREX -> ( AROP
	return 0;}
int tSM::p13(){ //    HAREX -> HAREX E
	return 0;}
int tSM::p14(){ //     AROP -> +
	return 0;}
int tSM::p15(){ //     AROP -> -
	return 0;}
int tSM::p16(){ //     AROP -> *
	return 0;}
int tSM::p17(){ //     AROP -> /
	return 0;}
int tSM::p18(){ //    CPROC -> HCPROC )
	return 0;}
int tSM::p19(){ //   HCPROC -> ( $id
	return 0;}
int tSM::p20(){ //   HCPROC -> HCPROC E
	return 0;}
int tSM::p21(){ //     COND -> ( cond BRANCHES )
	return 0;}
int tSM::p22(){ // BRANCHES -> CLAUS ELSE
	return 0;}
int tSM::p23(){ //    CLAUS -> ( BOOL CLAUSB )
	return 0;}
int tSM::p24(){ //   CLAUSB -> E
	return 0;}
int tSM::p25(){ //   CLAUSB -> INTER CLAUSB
	return 0;}
int tSM::p26(){ //     ELSE -> ( else ELSEB )
	return 0;}
int tSM::p27(){ //    ELSEB -> E
	return 0;}
int tSM::p28(){ //    ELSEB -> INTER ELSEB
	return 0;}
int tSM::p29(){ //      STR -> $str
	return 0;}
int tSM::p30(){ //      STR -> SCOND
	return 0;}
int tSM::p31(){ //    SCOND -> ( cond SBRANCHES )
	return 0;}
int tSM::p32(){ //SBRANCHES -> SELSE
	return 0;}
int tSM::p33(){ //SBRANCHES -> SCLAUS SBRANCHES
	return 0;}
int tSM::p34(){ //   SCLAUS -> ( BOOL STR )
	return 0;}
int tSM::p35(){ //    SELSE -> ( else STR )
	return 0;}
int tSM::p36(){ //     BOOL -> $bool
	return 0;}
int tSM::p37(){ //     BOOL -> $idq
	return 0;}
int tSM::p38(){ //     BOOL -> REL
	return 0;}
int tSM::p39(){ //     BOOL -> AND
	return 0;}
int tSM::p40(){ //     BOOL -> CPRED
	return 0;}
int tSM::p41(){ //    CPRED -> HCPRED )
	return 0;}
int tSM::p42(){ //   HCPRED -> ( $idq
	return 0;}
int tSM::p43(){ //   HCPRED -> HCPRED ARG
	return 0;}
int tSM::p44(){ //      ARG -> E
	return 0;}
int tSM::p45(){ //      ARG -> BOOL
	return 0;}
int tSM::p46(){ //      REL -> ( = E E )
	return 0;}
int tSM::p47(){ //      REL -> ( < E E )
	return 0;}
int tSM::p48(){ //      AND -> HAND BOOL )
	return 0;}
int tSM::p49(){ //     HAND -> ( and
	return 0;}
int tSM::p50(){ //     HAND -> HAND BOOL
	return 0;}
int tSM::p51(){ //      SET -> HSET E )
	return 0;}
int tSM::p52(){ //     HSET -> ( set! $id
	return 0;}
int tSM::p53(){ //  DISPSET -> ( display E )
	return 0;}
int tSM::p54(){ //  DISPSET -> ( display BOOL )
	return 0;}
int tSM::p55(){ //  DISPSET -> ( display STR )
	return 0;}
int tSM::p56(){ //  DISPSET -> ( newline )
	return 0;}
int tSM::p57(){ //  DISPSET -> SET
	return 0;}
int tSM::p58(){ //    INTER -> DISPSET
	return 0;}
int tSM::p59(){ //    INTER -> E
	return 0;}
int tSM::p60(){ //    CALCS -> CALC
	return 0;}
int tSM::p61(){ //    CALCS -> CALCS CALC
	return 0;}
int tSM::p62(){ //     CALC -> E
	return 0;}
int tSM::p63(){ //     CALC -> BOOL
	return 0;}
int tSM::p64(){ //     CALC -> STR
	return 0;}
int tSM::p65(){ //     CALC -> DISPSET
	return 0;}
int tSM::p66(){ //     DEFS -> DEF
	return 0;}
int tSM::p67(){ //     DEFS -> DEFS DEF
	return 0;}
int tSM::p68(){ //      DEF -> PRED
	return 0;}
int tSM::p69(){ //      DEF -> VAR
	return 0;}
int tSM::p70(){ //      DEF -> PROC
	return 0;}
int tSM::p71(){ //     PRED -> HPRED BOOL )
	return 0;}
int tSM::p72(){ //    HPRED -> PDPAR )
	return 0;}
int tSM::p73(){ //    PDPAR -> ( define ( $idq
	return 0;}
int tSM::p74(){ //    PDPAR -> PDPAR $idq
	return 0;}
int tSM::p75(){ //    PDPAR -> PDPAR $id
	return 0;}
int tSM::p76(){ //      VAR -> VARDCL E )
	return 0;}
int tSM::p77(){ //   VARDCL -> ( define $id
	return 0;}
int tSM::p78(){ //     PROC -> HPROC BLOCK )
	return 0;}
int tSM::p79(){ //     PROC -> HPROC E )
	return 0;}
int tSM::p80(){ //    HPROC -> PCPAR )
	return 0;}
int tSM::p81(){ //    HPROC -> HPROC INTER
	return 0;}
int tSM::p82(){ //    PCPAR -> ( define ( $id
	return 0;}
int tSM::p83(){ //    PCPAR -> PCPAR $id
	return 0;}
int tSM::p84(){ //    BLOCK -> HBLOCK E )
	return 0;}
int tSM::p85(){ //   HBLOCK -> BLVAR )
	return 0;}
int tSM::p86(){ //   HBLOCK -> HBLOCK INTER
	return 0;}
int tSM::p87(){ //    BLVAR -> ( let ( LOCDEF
	return 0;}
int tSM::p88(){ //    BLVAR -> BLVAR LOCDEF
	return 0;}
int tSM::p89(){ //   LOCDEF -> ( $id E )
	return 0;}
//_____________________
int tSM::p90(){return 0;} int tSM::p91(){return 0;} 
int tSM::p92(){return 0;} int tSM::p93(){return 0;} 
int tSM::p94(){return 0;} int tSM::p95(){return 0;} 
int tSM::p96(){return 0;} int tSM::p97(){return 0;} 
int tSM::p98(){return 0;} int tSM::p99(){return 0;} 
int tSM::p100(){return 0;} int tSM::p101(){return 0;} 
int tSM::p102(){return 0;} int tSM::p103(){return 0;} 
int tSM::p104(){return 0;} int tSM::p105(){return 0;} 
int tSM::p106(){return 0;} int tSM::p107(){return 0;} 
int tSM::p108(){return 0;} int tSM::p109(){return 0;} 
int tSM::p110(){return 0;} 

