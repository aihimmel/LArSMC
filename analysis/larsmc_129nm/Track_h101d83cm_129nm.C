#define Track_h101d83cm_129nm_cxx
#include "Track_h101d83cm_129nm.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TGraph.h"
#include "TH1D.h"

#include <iostream>
#include <vector>

void Track_h101d83cm_129nm::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Track_h101d83cm_129nm.C
//      root> Track_h101d83cm_129nm t
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

   // Final r^2 Objects
   std::string PCR_output_path = "/nashome/a/abreaux/Downloads/larsmc_129nm/PhotonCount_vs_r2_101d83_129nm.root";
   const double r_squared_max = 43472.25;

   TCanvas *canvas = new TCanvas("canvas", "Photon Detections vs. r^2", 800, 600);
   TH1D *h1 = new TH1D("h1", "Photon Count vs. r^2", 10000, 0.0, 10000.0);

   // Final Position Objects
   // std::string FP_output_path = "/nashome/a/abreaux/Downloads/larsmc_129nm/BottomDetections_101d83_129nm.root";

   // std::vector<double> final_x_cage;
   // std::vector<double> final_y_cage;
   // std::vector<double> final_x_opdet0;
   // std::vector<double> final_y_opdet0;
   // std::vector<double> final_x_opdet1;
   // std::vector<double> final_y_opdet1;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (FinalVolume == 1. || FinalVolume == 2. || FinalVolume == 13.)
      {
         h1->Fill(Final_R_Sq_);

         // if (FinalVolume == 1.)
         //    {
         //       final_x_opdet0.push_back(FinalX);
         //       final_y_opdet0.push_back(FinalY);
         //    }
         // else if (FinalVolume == 2.)
         //    {
         //       final_x_opdet1.push_back(FinalX);
         //       final_y_opdet1.push_back(FinalY);
         //    }
         // else
         //    {
         //       final_x_cage.push_back(FinalX);
         //       final_y_cage.push_back(FinalY);
         //    }
      }
   }

   h1->Draw();
   canvas->Update();
   canvas->SaveAs(PCR_output_path.c_str());
   delete canvas;

   // int a = final_x_cage.size();
   // int b = final_x_opdet0.size();
   // int c = final_x_opdet1.size();

   // std::cout << a << " " << b << " " << c << std::endl;

   // double arr_final_x_cage[a];
   // double arr_final_y_cage[a];
   // double arr_final_x_opdet0[b];
   // double arr_final_y_opdet0[b];
   // double arr_final_x_opdet1[c];
   // double arr_final_y_opdet1[c];

   // for (int i = 0; i < a; i++)
   // {
   //    arr_final_x_cage[i] = final_x_cage[i];
   //    arr_final_y_cage[i] = final_y_cage[i];

   //    std::cout << final_x_cage[i] << " ";
   // }

   // for (int i = 0; i < b; i++)
   // {
   //    arr_final_x_opdet0[i] = final_x_opdet0[i];
   //    arr_final_y_opdet0[i] = final_y_opdet0[i];

   //    std::cout << final_x_opdet0[i] << " ";
   // }

   // for (int i = 0; i < c; i++)
   // {
   //    arr_final_x_opdet1[i] = final_x_opdet1[i];
   //    arr_final_y_opdet1[i] = final_y_opdet1[i];

   //    std::cout << final_x_opdet1[i] << " ";
   // }

   // std::cout << arr_final_x_cage[10] << std::endl;
   // std::cout << arr_final_x_opdet0[10] << std::endl;
   // std::cout << arr_final_x_opdet1[10] << std::endl;

   // TCanvas *btmcanvas = new TCanvas("btmcanvas", "Tallbo Bottom Distribution", 800, 800);
   // TGraph *finalcage = new TGraph(final_x_cage.data(), final_y_cage.data());
   // finalcage->SetNameTitle("finalcage", "Tallbo Bottom Distribution");
   // finalcage->SetMarkerColor(kBlue);
   // finalcage->SetMarkerStyle(6);
   // finalcage->Draw("AP");
   // TGraph *finalopdet0 = new TGraph(final_x_opdet0.data(), final_y_opdet0.data());
   // finalopdet0->SetName("finalopdet0");
   // finalopdet0->SetMarkerColor(kRed);
   // finalopdet0->SetMarkerStyle(6);
   // finalopdet0->Draw("SAME");
   // TGraph *finalopdet1 = new TGraph(final_x_opdet1.data(), final_y_opdet1.data());
   // finalopdet0->SetName("finalopdet1");
   // finalopdet1->SetMarkerColor(kGreen);
   // finalopdet1->SetMarkerStyle(6);
   // finalopdet1->Draw("SAME");

   // btmcanvas->Update();
   // btmcanvas->SaveAs(FP_output_path.c_str());
   // delete btmcanvas;
}

// For the Tallbo Bottom Distribution graphs, the bug is coming from issues in memory availability. The arrays you're trying to initialize are far too large. If these plots are necessary in the future,
// ask Alex for some advice on how to work around this.