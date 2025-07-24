//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 18 11:40:15 2025 by ROOT version 6.20/08
// from TTree TrackTree/TrackTree
// found on file: /exp/dune/data/users/abreaux/larsmc_h2d22cm_180nm_ref.root
//////////////////////////////////////////////////////////

#ifndef Track_h2d22cm_180nm_ref_h
#define Track_h2d22cm_180nm_ref_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Track_h2d22cm_180nm_ref {
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

   Track_h2d22cm_180nm_ref(TTree *tree=0);
   virtual ~Track_h2d22cm_180nm_ref();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Track_h2d22cm_180nm_ref_cxx
Track_h2d22cm_180nm_ref::Track_h2d22cm_180nm_ref(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/exp/dune/data/users/abreaux/larsmc_h2d22cm_180nm_ref.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/exp/dune/data/users/abreaux/larsmc_h2d22cm_180nm_ref.root");
      }
      f->GetObject("TrackTree",tree);

   }
   Init(tree);
}

Track_h2d22cm_180nm_ref::~Track_h2d22cm_180nm_ref()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Track_h2d22cm_180nm_ref::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Track_h2d22cm_180nm_ref::LoadTree(Long64_t entry)
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

void Track_h2d22cm_180nm_ref::Init(TTree *tree)
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

Bool_t Track_h2d22cm_180nm_ref::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Track_h2d22cm_180nm_ref::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Track_h2d22cm_180nm_ref::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Track_h2d22cm_180nm_ref_cxx
