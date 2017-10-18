#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>

typedef Double_t NType;
typedef TH1D     NHIST;

// typedef per function pointer
typedef NType (*NPfun)(NType*, NType*); 

NType f(NType * x, NType * xx);

NType fc(NType(*pf)(NType*, NType*)); 

NType inversion(NType(*pf)(NType, NType *));

NType f(NType * x , NType * xx){
  if (x[0] < -2.6 || x[0] > 2.6) return 0.05;
  else return 1;
}


NType fc(NType * x , NType * xx){
  if (x[0] < -2.6) return 0.05 * x[0] + 0.5;
  if (x[0] >  2.6) return 0.05 * x[0] + 5.44;
  else             return        x[0] + 2.97;
}

NHIST * inversion(NType(*pf)(NType*, NType *),
		  const char* name,
		  const char* title,
		  Int_t bin,
		  NType min,
		  NType max,
		  Int_t sample = 10000) {
  NType * temp = new NType[1];

  NHIST * hmp = new NHIST(name, title, bin, min, max);
  NType iter = 0;
  for (int i = 0; i < sample; i++){
    iter = bin * ( i * (max - min) - min )/ sample;
    temp[0] = i;
    hmp->Fill(iter, pf(temp, NULL));
  }
  delete []temp;
  return hmp;
}


void m(){
  TF1 * sx = new TF1("sx", "TMath::Sin(x)*TMath::Sin(x)/(x*x)", -10., 10.);
  //sx->SetLineColor(kBlue);
  //sx->Draw();
  TF1 *funzione = new TF1("funzione", &fc, -10., 10.);
  funzione->Draw("same");
  NHIST * fhc = new NHIST();
  fhc = inversion(fc, "fhc", "fhc", 100, -10., 10.);
  fhc->Draw("histsame");
}
