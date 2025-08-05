#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

void MakePCRGraphPDFs(std::string ginfile_name, std::string goutfile_pdf_name1, std::string goutfile_pdf_name2, std::string goutfile_pdf_name3)
{
    TFile *ginfile = TFile::Open(ginfile_name.c_str());
    TCanvas *c1 = (TCanvas*)ginfile->Get("canvas");
    TGraph *g1 = (TGraph*)c1->GetPrimitive("g1");

    c1->Print(goutfile_pdf_name1.c_str()); // Output the original graph

    g1->GetYaxis()->SetRangeUser(0.0, 1400000.0);
    g1->Draw();
    c1->Update();
    c1->Print(goutfile_pdf_name2.c_str());

    g1->GetYaxis()->SetRangeUser(0.0, 100000.0);
    g1->Draw();
    c1->Update();
    c1->Print(goutfile_pdf_name3.c_str()); // Output zoomed graph
}

void MakePCRFitPDFs(std::string finfile_name, std::string foutfile_pdf_name)
{
    TFile *finfile = TFile::Open(finfile_name.c_str());
    TCanvas *c1 = (TCanvas*)finfile->Get("canvas");
    TGraph *g1 = (TGraph*)c1->GetPrimitive("g1");

    c1->Print(foutfile_pdf_name.c_str());
}

void MakePCRHistoPDFs(std::string hinfile_name, std::string houtfile_pdf_name)
{
    TFile *hinfile = TFile::Open(hinfile_name.c_str());
    TCanvas *c1 = (TCanvas*)hinfile->Get("canvas");

    c1->Print(houtfile_pdf_name.c_str());
}

void MakePDFs_155nm()
{
    std::string ginfile_name = "/nashome/a/abreaux/Downloads/larsmc_155nm/gPhotonCount_vs_r2_155nm.root";
    std::string hinfile_name = "/nashome/a/abreaux/Downloads/larsmc_155nm/PhotonCount_vs_r2_155nm.root";
    std::string finfile_name = "/nashome/a/abreaux/Downloads/larsmc_155nm/AttenuationLength_Vs_HLArMin_155nm.root";
    std::string goutfile_pdf_name1 = "/nashome/a/abreaux/Downloads/larsmc_155nm/g1PCvsR2_155nm.pdf";
    std::string goutfile_pdf_name2 = "/nashome/a/abreaux/Downloads/larsmc_155nm/g2PCvsR2_155nm.pdf";
    std::string goutfile_pdf_name3 = "/nashome/a/abreaux/Downloads/larsmc_155nm/g3PCvsR2_155nm.pdf";
    std::string houtfile_pdf_name = "/nashome/a/abreaux/Downloads/larsmc_155nm/hPCvsR2_155nm.pdf";
    std::string foutfile_pdf_name = "/nashome/a/abreaux/Downloads/larsmc_155nm/fALvsMHLAr_155nm.pdf";

    MakePCRGraphPDFs(ginfile_name, goutfile_pdf_name1, goutfile_pdf_name2, goutfile_pdf_name3);
    MakePCRFitPDFs(finfile_name, foutfile_pdf_name);
    // MakePCRHistoPDFs(hinfile_name, houtfile_pdf_name);
}