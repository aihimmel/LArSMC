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

std::vector<double> ExtractAttLens(std::string graph_name)
{
    TFile *file = TFile::Open(graph_name.c_str());
    TCanvas *canvas = (TCanvas*)file->Get("canvas");
    TGraph *g1 = (TGraph*)canvas->GetPrimitive("g1");
    TGraph *g2 = (TGraph*)canvas->GetPrimitive("g2");
    TGraph *g3 = (TGraph*)canvas->GetPrimitive("g3");
    TGraph *g4 = (TGraph*)canvas->GetPrimitive("g4");
    TGraph *g5 = (TGraph*)canvas->GetPrimitive("g5");
    TGraph *g6 = (TGraph*)canvas->GetPrimitive("g6");

    Double_t *attlens_0to3mm = g1->GetY();
    Double_t *attlens_15to18mm = g2->GetY();
    Double_t *attlens_30to33mm = g3->GetY();
    Double_t *attlens_42to45mm = g4->GetY();
    Double_t *attlens_45to48mm = g5->GetY();
    Double_t *attlens_48to51mm = g6->GetY();

    std::vector<double> attlens_vec = {attlens_0to3mm[0], attlens_15to18mm[7], attlens_30to33mm[7], attlens_42to45mm[7], attlens_45to48mm[7], attlens_48to51mm[7]};

    return attlens_vec;
}

void GraphIt(std::vector<double> attlens_115nm, std::vector<double> attlens_125nm, std::vector<double> attlens_129nm, std::vector<double> attlens_135nm, std::vector<double> attlens_140nm, std::vector<double> attlens_150nm, std::vector<double> attlens_155nm)
{
    std::string r_ranges[33] = {"[0,3]", "(3,6]", "(6,9]", "(9,12]", "(12,15]", "(15,18]", "(18,21]", "(21,24]", "(24,27]", "(27,30]", "(30,33]", "(33,36]", "(36,39]", "(39,42]", "(42,45]", "(45,48]", "(51,54]", "(54,57]", "(57,60]", "(60,63]", "(63,66]", "(66,69]", "(69,72]", "(72,75]", "(75,78]", "(78,81]", "(81,84]", "(84,87]", "(87,90]", "(90,93]", "(93,96]", "(96,99]"};
    double scatlens[7] = {56.84, 79.3458, 90.0, 107.949, 124.852, 164.531, 187.59};

    std::vector<double> attlens_0to3mm = {attlens_115nm[0], attlens_125nm[0], attlens_129nm[0], attlens_135nm[0], attlens_140nm[0], attlens_150nm[0], attlens_155nm[0]};
    double attlens_0to3mm_arr[attlens_0to3mm.size()];
        for (int i = 0; i < attlens_0to3mm.size(); i++) { attlens_0to3mm_arr[i] = attlens_0to3mm[i]; }

    std::vector<double> attlens_15to18mm = {attlens_115nm[1], attlens_125nm[1], attlens_129nm[1], attlens_135nm[1], attlens_140nm[1], attlens_150nm[1], attlens_155nm[1]};
    double attlens_15to18mm_arr[attlens_15to18mm.size()];
        for (int i = 0; i < attlens_15to18mm.size(); i++) { attlens_15to18mm_arr[i] = attlens_15to18mm[i]; }

    std::vector<double> attlens_30to33mm = {attlens_115nm[2], attlens_125nm[2], attlens_129nm[2], attlens_135nm[2], attlens_140nm[2], attlens_150nm[2], attlens_155nm[2]};
    double attlens_30to33mm_arr[attlens_30to33mm.size()];
        for (int i = 0; i < attlens_30to33mm.size(); i++) { attlens_30to33mm_arr[i] = attlens_30to33mm[i]; }

    std::vector<double> attlens_42to45mm = {attlens_115nm[3], attlens_125nm[3], attlens_129nm[3], attlens_135nm[3], attlens_140nm[3], attlens_150nm[3], attlens_155nm[3]};
    double attlens_42to45mm_arr[attlens_42to45mm.size()];
        for (int i = 0; i < attlens_42to45mm.size(); i++) { attlens_42to45mm_arr[i] = attlens_42to45mm[i]; }

    std::vector<double> attlens_45to48mm = {attlens_115nm[4], attlens_125nm[4], attlens_129nm[4], attlens_135nm[4], attlens_140nm[4], attlens_150nm[4], attlens_155nm[4]};
    double attlens_45to48mm_arr[attlens_45to48mm.size()];
        for (int i = 0; i < attlens_45to48mm.size(); i++) { attlens_45to48mm_arr[i] = attlens_45to48mm[i]; }

    std::vector<double> attlens_48to51mm = {attlens_115nm[5], attlens_125nm[5], attlens_129nm[5], attlens_135nm[5], attlens_140nm[5], attlens_150nm[5], attlens_155nm[5]};
    double attlens_48to51mm_arr[attlens_48to51mm.size()];
        for (int i = 0; i < attlens_48to51mm.size(); i++) { attlens_48to51mm_arr[i] = attlens_48to51mm[i]; }

    TCanvas *cmain = new TCanvas("canvas", "", 800, 600);
    TLegend *legend = new TLegend(0.581454, 0.140625, 0.880952, 0.288194, "h", "brNDC");
    legend->SetHeader("R Ranges (mm)", "C");
    legend->SetNColumns(3);

    TGraph *g1 = new TGraph(7, attlens_0to3mm_arr, scatlens);
    g1->SetNameTitle("g1", ";Extracted Attenuation Length (cm) ;Specified Scattering Length (cm)");
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kRed);
    g1->SetLineColor(kRed);
    g1->SetLineWidth(2);
    g1->GetXaxis()->SetLimits(40.0, 400.0);
    g1->GetYaxis()->SetRangeUser(40.0, 200.0);
    g1->Draw("APL");
    legend->AddEntry(g1, r_ranges[0].c_str(), "p");

    TGraph *g2 = new TGraph(7, attlens_15to18mm_arr, scatlens);
    g2->SetName("g2");
    g2->SetMarkerStyle(20);
    g2->SetMarkerColor(kOrange+10);
    g2->SetLineColor(kOrange+10);
    g2->SetLineWidth(2);
    g2->Draw("SAME PL");
    legend->AddEntry(g2, r_ranges[5].c_str(), "p");
    
    TGraph *g3 = new TGraph(7, attlens_30to33mm_arr, scatlens);
    g3->SetName("g3");
    g3->SetMarkerStyle(20);
    g3->SetMarkerColor(kYellow);
    g3->SetLineColor(kYellow);
    g3->SetLineWidth(2);
    g3->Draw("SAME PL");
    legend->AddEntry(g3, r_ranges[10].c_str(), "p");
    
    TGraph *g4 = new TGraph(7, attlens_42to45mm_arr, scatlens);
    g4->SetName("g4");
    g4->SetMarkerStyle(20);
    g4->SetMarkerColor(kGreen);
    g4->SetLineColor(kGreen);
    g4->SetLineWidth(2);
    g4->Draw("SAME PL");
    legend->AddEntry(g4, r_ranges[14].c_str(), "p");
    
    TGraph *g5 = new TGraph(7, attlens_45to48mm_arr, scatlens);
    g5->SetName("g5");
    g5->SetMarkerStyle(20);
    g5->SetMarkerColor(kBlue);
    g5->SetLineColor(kBlue);
    g5->SetLineWidth(2);
    g5->Draw("SAME PL");
    legend->AddEntry(g5, r_ranges[15].c_str(), "p");
    
    TGraph *g6 = new TGraph(7, attlens_48to51mm_arr, scatlens);
    g6->SetName("g6");
    g6->SetMarkerStyle(20);
    g6->SetMarkerColor(kMagenta);
    g6->SetLineColor(kMagenta);
    g6->SetLineWidth(2);
    g6->Draw("SAME PL");
    legend->AddEntry(g6, r_ranges[16].c_str(), "p");
    
    TLine *l1 = new TLine(40, 40, 200, 200);
    l1->SetLineColor(kBlack);
    l1->SetLineWidth(2);
    l1->Draw("SAME");
    legend->AddEntry(l1, "Specified Value", "l");

    legend->Draw();
    cmain->Update();
    cmain->Print("/nashome/a/abreaux/Downloads/ScatLens_Vs_AttLens.root");
}

void GraphScatLensVsAttLens()
{
    std::string path_name = "/nashome/a/abreaux/Downloads";
    std::vector<std::string> graph_names = {"/larsmc_115nm/AttenuationLength_Vs_HLArMin_115nm.root", "/larsmc_125nm/AttenuationLength_Vs_HLArMin_125nm.root", "/larsmc_129nm/AttenuationLength_Vs_HLArMin_129nm.root", "/larsmc_135nm/AttenuationLength_Vs_HLArMin_135nm.root", "/larsmc_140nm/AttenuationLength_Vs_HLArMin_140nm.root", "/larsmc_150nm/AttenuationLength_Vs_HLArMin_150nm.root", "/larsmc_155nm/AttenuationLength_Vs_HLArMin_155nm.root"};

    std::vector<double> attlens_115nm = ExtractAttLens(path_name + graph_names[0]);
    std::vector<double> attlens_125nm = ExtractAttLens(path_name + graph_names[1]);
    std::vector<double> attlens_129nm = ExtractAttLens(path_name + graph_names[2]);
    std::vector<double> attlens_135nm = ExtractAttLens(path_name + graph_names[3]);
    std::vector<double> attlens_140nm = ExtractAttLens(path_name + graph_names[4]);
    std::vector<double> attlens_150nm = ExtractAttLens(path_name + graph_names[5]);
    std::vector<double> attlens_155nm = ExtractAttLens(path_name + graph_names[6]);

    GraphIt(attlens_115nm, attlens_125nm, attlens_129nm, attlens_135nm, attlens_140nm, attlens_150nm, attlens_155nm);
}