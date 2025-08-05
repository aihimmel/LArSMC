#include "Track.h"

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"

TH2D* Track::Loop()
{
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   TH2D *h = new TH2D("h",  ";x (mm);y (mm);Photon Count", 100, 37.5, 137.5, 100, -50, 50);

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ((FinalVolume == 1. || FinalVolume == 2. || FinalVolume == 13.) && (FinalX < 137.5) && (FinalX > 37.5) && (FinalY < 50) && (FinalY > -50))
      {
        h->Fill(FinalX, FinalY);
      }
   }

   return h;
}

Track::Track(std::string filename) : fChain(0)
{
    TFile *file = TFile::Open(filename.c_str(), "READ");
    TTree *tree = nullptr;
    file->GetObject("TrackTree", tree);
    Init(tree);
}

Track::~Track()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Track::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Track::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Track::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("InitialX", &InitialX, &b_InitialX);
   fChain->SetBranchAddress("InitialY", &InitialY, &b_InitialY);
   fChain->SetBranchAddress("InitialZ", &InitialZ, &b_InitialZ);
   fChain->SetBranchAddress("InitialEnergy", &InitialEnergy, &b_InitialEnergy);
   fChain->SetBranchAddress("FinalX", &FinalX, &b_FinalX);
   fChain->SetBranchAddress("FinalY", &FinalY, &b_FinalY);
   fChain->SetBranchAddress("FinalZ", &FinalZ, &b_FinalZ);
   fChain->SetBranchAddress("FinalVolume", &FinalVolume, &b_FinalVolume);
   fChain->SetBranchAddress("Final_R_Sq.", &Final_R_Sq_, &b_Final_R_Sq_);
   Notify();
}

Bool_t Track::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Track::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Track::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}