#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>

typedef Double_t NType;
typedef TH1D     NHIST;

// typedef per function pointer
//typedef NType (*NPfun)(NType*, NType*); 

NType f(NType * x, NType * xx);

NType fc(NType(*pf)(NType*, NType*)); 

NType fi(NType * x, NType * xx);

NHIST * inversion(NType(*pf)(NType*, NType *),
		  const char* name,
		  const char* title,
		  Int_t bin,
		  NType min,
		  NType max,
		  Int_t sample = 10000000, NType scale = 1.);




void ma(){
  NHIST * hh = inversion(fi, "hh", "histo",
			 100, -10., 10., 10000000, 5.94);
  hh->Draw();
}




NType f(NType * x , NType * xx){
  // pdf
  if (x[0] < -2.6 || x[0] > 2.6) return 0.05;
  else return 1;
}

NType fc(NType * x , NType * xx){
  // cumulative function
  if (x[0] < -2.6) return 0.05 * x[0] + 0.5;
  if (x[0] >  2.6) return 0.05 * x[0] + 5.44;
  else             return        x[0] + 2.97;
}

NType fi(NType * x, NType * xx){
  // inverse cumulative function
  if (x[0] > 0    && x[0] < 0.37) return 20 * x[0] - 10;
  if (x[0] > 5.57 && x[0] < 5.94) return 20 * x[0] - 108.8;
  else                            return      x[0] - 2.97;
}

NHIST * inversion(NType(*pf)(NType*, NType *),
		  const char* name,
		  const char* title,
		  Int_t bin,
		  NType min,
		  NType max,
		  Int_t sample = 10000000, NType scale = 1.) {
  NHIST * histo = new NHIST("histo", "histo", bin, min, max);
  NType * temp = new NType[1];
  for (int i = 0; i < sample; i++){
    temp[0] = scale*gRandom->Rndm();
    histo->Fill(pf(temp, NULL));
  }
  delete [] temp;
  return histo;
}


