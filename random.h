//
//  Problema 1
//  Ludovico Lapo Luperi
//  ludovicolapo.luperi@studenti.unimi.it
//

/* Obiettivo del codice
 Generare variabili pseudocasuali, calcolarne medie e varianze e confrontarle con i calcoli esatti
 */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>  // algoritmi STL
#include <numeric>    // inner_product

#include "BasicFunction.h"

using namespace std;

#pragma once
class RandomGenerator {
public:
    RandomGenerator(unsigned int s){
        a = 1664525;
        c = 1013904223;
        m = pow(2,31);
        seed = s;
    };
    
    void Set_A(unsigned int A) {a=A;}
    void Set_C(unsigned int C) {c=C;}
    void Set_M(unsigned int M) {m=M;}
    
    double Rand(){return ((a*(seed)+c))%m;};
    
    // distribuzione uniforme
    double Unif(double xmin, double xmax){
        seed = Rand();
        return xmin + (xmax-xmin)*Rand()/m;
    }
    // distribuzione esponenziale
    double Exp(double lambda){return (-1/lambda)*log(1-Unif(0,1));}
    // distribuzione qaussiana (Box-Muller)
    double Gauss(double mean, double sigma){
        double s = Unif(0,1);
        double t = Unif(0,1);
        double x = sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
        return mean+x*sigma;
    }
    // distribuzione gaussiana (Accept-Reject)
    double AcceptReject(double a, double b, double max, const BasicFunction &f){
        
        double s = Unif(0,1);
        double t = Unif(0,1);
        double x = a + (b-a)*s;
        double y = max*t;
        
        while(y>f.Evaluate(x)) x = AcceptReject(a,b,max,f);
        return x;
    }
    
private:
    unsigned int a,c,m;
    unsigned int seed;
};
