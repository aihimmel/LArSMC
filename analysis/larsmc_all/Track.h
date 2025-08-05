#ifndef Track_h
#define Track_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH2D.h"

// Header file for the classes stored in the TTree if any.

class Track {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxFinal_R_Sq = 1;

   // Declaration of leaf types
   Double_t        InitialX;
   Double_t        InitialY;
   Double_t        InitialZ;
   Double_t        InitialEnergy;
   Double_t        FinalX;
   Double_t        FinalY;
   Double_t        FinalZ;
   Double_t        FinalVolume;
   Double_t        Final_R_Sq_;

   // List of branches
   TBranch        *b_InitialX;   //!
   TBranch        *b_InitialY;   //!
   TBranch        *b_InitialZ;   //!
   TBranch        *b_InitialEnergy;   //!
   TBranch        *b_FinalX;   //!
   TBranch        *b_FinalY;   //!
   TBranch        *b_FinalZ;   //!
   TBranch        *b_FinalVolume;   //!
   TBranch        *b_Final_R_Sq_;   //!

   Track(std::string filename);
   virtual ~Track();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual TH2D*    Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif