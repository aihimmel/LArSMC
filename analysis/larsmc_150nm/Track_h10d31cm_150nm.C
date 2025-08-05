#define Track_h10d31cm_150nm_cxx
#include "Track_h10d31cm_150nm.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Track_h10d31cm_150nm::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Track_h10d31cm_150nm.C
//      root> Track_h10d31cm_150nm t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   const double r_squared_max = 43472.25;

   TCanvas *canvas = new TCanvas("canvas", "Photon Detections vs. r^2", 800, 600);
   TH1D *h1 = new TH1D("h1", "Photon Count vs. r^2", 10000, 0.0, 10000.0);

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (FinalVolume == 1. || FinalVolume == 2. || FinalVolume == 13.)
      {
         h1->Fill(Final_R_Sq_);
      }
   }

   h1->Draw();
   std::string OutfilePath = "/nashome/a/abreaux/Downloads/larsmc_150nm/PhotonCount_vs_r2_10d31_150nm.root";
   canvas->Update();
   canvas->SaveAs(OutfilePath.c_str());
   delete canvas;
}
