#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>


typedef Double_t NType;
typedef TH1D     NHIST;

// typedef per function pointer
typedef NType (*NPfun)(NType*, NType*);

NType F(NType * x, NType * xx){
  return 1./4./x[0];
}

NType f(NType * x, NType * xx){
  return 1./2.*sqrt(x[0]);
}

NType i(NType * x, NType * xx){
  return 4.*x*x[0];
}


