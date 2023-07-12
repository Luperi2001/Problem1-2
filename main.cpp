//
//  Problema 1
//  Ludovico Lapo Luperi
//  ludovicolapo.luperi@studenti.unimi.it
//

/* Obiettivo del codice
 Generare variabili pseudocasuali, calcolarne medie e varianze e confrontarle con i calcoli esatti
 */

/*Results and issues
 Le r_i non sono correlate, quindi media nulla per ogni caso e varianza data dalla somma delle varianze
 All'aumentare del numero di variabili non correlate aumenta la varianza della variabile x e la curva tende a una distribuzione normale standard (aka gaussiana) (teorema limite centrale verificato)
 Mancano i dati/una trattazione migliore del fit del punto c; è facoltativo, ma lo voglio fare
 Il multigraph è per evdere come la curva tenda a una gaussiana all'aumentare del numero di variabili che costituiscono la x
 */
#include <iostream>
#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <vector>
#include <cassert>
#include <algorithm>  // algoritmi STL
#include <numeric>    // inner_product

#include "random.h"

//ROOT
#include "TApplication.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TNamed.h"
#include "TColor.h"
#include "TH1F.h"
#include "TStyle.h"

using namespace std;

const int Times = pow(10,4);
const double e_inf = 0;
const double e_sup = x_max;

void RootGraphs(RandomGenerator &RandomNumber);

int main(int argc, const char * argv[]){
    
    assert(argc == 2 && "Syntax:\t <nome_eseguibilie> <seed>");
    
    RandomGenerator RandomNumber(atoi(argv[1]));
    TApplication app ("app",0,0);
    DenteDiSega f;
    TH1F DenteDiSegaT("Trasformata", "Dente di sega - Trasformata", 100, -1.5, 1.5);
    for(int i = 0; i<Times;i++) DenteDiSegaT.Fill(f.Evaluate(RandomNumber.Unif(0,1)));
    
    TH1F DenteDiSegaAR("AcceptReject", "Dente di sega - AcceptReject", 100, -1.5, 1.5);
    double x = 0,y = 1,m = 2/x_max;
    for(int i = 0; i<Times;i++){
        while(f.Evaluate(x) < y){
            x = e_inf + (e_sup-e_inf)*RandomNumber.Unif(0,1);
            y = m * RandomNumber.Unif(0,1);
        }
        DenteDiSegaAR.Fill(x);
        x = 0;
        y = 1;
    }
    
    cout << "Efficiency of the AcceptReject method:\t" << 1/(m*(e_sup-e_inf));
    
    cout << "\n\n\n" << endl;

    TCanvas alpha;
    alpha.Divide(2,1);
    alpha.cd(1);
    DenteDiSegaT.GetXaxis() -> SetTitle("Value [AU]");
    DenteDiSegaT.GetYaxis() -> SetTitle("Number of events");
    DenteDiSegaT.Draw();
    
    alpha.cd(2);
    DenteDiSegaAR.GetXaxis() -> SetTitle("Value [AU]");
    DenteDiSegaAR.GetYaxis() -> SetTitle("Number of events");
    DenteDiSegaAR.Draw();
    
    app.Run();
    return 0;
}
