#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TF1.h"

void DoFit(std::string file_path)
{
    TFile *file = TFile::Open(file_path.c_str());
    TCanvas *canvas = (TCanvas*)file->Get("canvas");

    TGraph *g1 = (TGraph*)canvas->GetPrimitive("g1");
    TGraph *g2 = (TGraph*)canvas->GetPrimitive("g2");
    TGraph *g3 = (TGraph*)canvas->GetPrimitive("g3");
    TGraph *g4 = (TGraph*)canvas->GetPrimitive("g4");
    TGraph *g5 = (TGraph*)canvas->GetPrimitive("g5");
    TGraph *g6 = (TGraph*)canvas->GetPrimitive("g6");

    TF1 *f1 = new TF1("f1", "[0]+[1]*x", 40, 400);
    g1->Fit(f1, "N", "", 50, 400);
    g1->SetMarkerStyle(20);
    f1->SetLineColor(kRed);
    f1->Draw("SAME");

    TF1 *f2 = new TF1("f2", "[0]+[1]*x", 40, 400);
    g2->Fit(f2, "N", "", 50, 400);
    g2->SetMarkerStyle(20);
    f2->SetLineColor(kOrange+10);
    f2->Draw("SAME");

    TF1 *f3 = new TF1("f3", "[0]+[1]*x", 40, 400);
    g3->Fit(f3, "N", "", 50, 400);
    g3->SetMarkerStyle(20);
    f3->SetLineColor(kYellow);
    f3->Draw("SAME");

    TF1 *f4 = new TF1("f4", "[0]+[1]*x", 40, 400);
    g4->Fit(f4, "N", "", 50, 400);
    g4->SetMarkerStyle(20);
    f4->SetLineColor(kGreen);
    f4->Draw("SAME");

    TF1 *f5 = new TF1("f5", "[0]+[1]*x", 40, 400);
    g5->Fit(f5, "N", "", 50, 400);
    g5->SetMarkerStyle(20);
    f5->SetLineColor(kBlue);
    f5->Draw("SAME");

    TF1 *f6 = new TF1("f6", "[0]+[1]*x", 40, 400);
    g6->Fit(f6, "N", "", 50, 400);
    g6->SetMarkerStyle(20);
    f6->SetLineColor(kMagenta);
    f6->Draw("SAME");

    canvas->Update();
    canvas->Print("/nashome/a/abreaux/Downloads/FitScatLens_Vs_AttLens.root");

    return;
}

void FitScatLensVsAttLens()
{
    std::string file_path = "/nashome/a/abreaux/Downloads/ScatLens_Vs_AttLens.root";
    DoFit(file_path);
}