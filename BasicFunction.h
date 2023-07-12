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
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

const double x_max = 1;

#pragma once
class BasicFunction{
    public:
        BasicFunction(){};
        virtual double Evaluate(double x) const = 0;
        virtual ~BasicFunction(){};
        double Sign(double value) const{if(Evaluate(value) >= 0) return 1; return -1;};
};

#pragma once
class Sin: public BasicFunction{
public:
    Sin(): BasicFunction(){};
    virtual ~Sin(){};
    Sin(double value){x = value;};
    double Evaluate(double x) const override{ return sin(x);};
    
private:
    double x;
};

#pragma once
class DenteDiSega: public BasicFunction{
    public:
        DenteDiSega(): BasicFunction(){};
        virtual ~DenteDiSega(){};
        DenteDiSega(double value){x = value;};
        double Evaluate(double x) const override {return x_max*sqrt(x);};
    private:
        double x;
};

#pragma once
class Gauss: public BasicFunction{
public:
    Gauss(): BasicFunction(){};
    Gauss(double m, double s){ mean = m; sigma = s;}
    virtual ~Gauss(){};
    double Evaluate(double x) const override{return sqrt(1/(2*M_PI*pow(sigma,2)))*exp(-pow(((x-mean)/sigma),2)/2);};
    double GetMax() const {return sqrt(1/(2*M_PI*pow(sigma,2)));};
    
private:
    double mean, sigma;
};
