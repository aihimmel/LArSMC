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
#include "TLine.h"

void GraphAttLensVsHLArMin(double attenuation_length_0to3mm, std::vector<double> attenuation_lengths_3to6mm, std::vector<double> attenuation_lengths_6to9mm, std::vector<double> attenuation_lengths_9to12mm, std::vector<double> attenuation_lengths_12to15mm, std::vector<double> attenuation_lengths_15to18mm)
{
    double HLAr_min_0to3mm[1] = {2.22};
    double HLAr_mins[12] = {5.23, 10.0, 17.0, 25.0, 28.0, 38.0, 40.0, 50.0, 63.0, 75.0, 85.0, 100.0};
    std::string r_ranges[33] = {"[0,3]", "(3,6]", "(6,9]", "(9,12]", "(12,15]", "(15,18]", "(18,21]", "(21,24]", "(24,27]", "(27,30]", "(30,33]", "(33,36]", "(36,39]", "(39,42]", "(42,45]", "(45,48]", "(48,51]", "(51,54]", "(54,57]", "(57,60]", "(60,63]", "(63,66]", "(66,69]", "(69,72]", "(72,75]", "(75,78]", "(78,81]", "(81,84]", "(84,87]", "(87,90]", "(90,93]", "(93,96]", "(96,99]"};
    
    double attenuation_length_0to3mm_arr[1] = {attenuation_length_0to3mm};
    double attenuation_lengths_3to6mm_arr[attenuation_lengths_3to6mm.size()];
        for (int i = 0; i < attenuation_lengths_3to6mm.size(); i++) { attenuation_lengths_3to6mm_arr[i] = attenuation_lengths_3to6mm[i]; }
    double attenuation_lengths_6to9mm_arr[attenuation_lengths_6to9mm.size()];
        for (int i = 0; i < attenuation_lengths_6to9mm.size(); i++) { attenuation_lengths_6to9mm_arr[i] = attenuation_lengths_6to9mm[i]; }
    double attenuation_lengths_9to12mm_arr[attenuation_lengths_9to12mm.size()];
        for (int i = 0; i < attenuation_lengths_9to12mm.size(); i++) { attenuation_lengths_9to12mm_arr[i] = attenuation_lengths_9to12mm[i]; }
    double attenuation_lengths_12to15mm_arr[attenuation_lengths_12to15mm.size()];
        for (int i = 0; i < attenuation_lengths_12to15mm.size(); i++) { attenuation_lengths_12to15mm_arr[i] = attenuation_lengths_12to15mm[i]; }
    double attenuation_lengths_15to18mm_arr[attenuation_lengths_15to18mm.size()];
        for (int i = 0; i < attenuation_lengths_15to18mm.size(); i++) { attenuation_lengths_15to18mm_arr[i] = attenuation_lengths_15to18mm[i]; }

    TCanvas *cmain = new TCanvas("canvas", "", 800, 600);
    TLegend *legend = new TLegend(0.585213, 0.730903, 0.885965, 0.881944, "h", "brNDC");
    legend->SetHeader("R Ranges (mm)", "C");
    legend->SetNColumns(3);

    TGraph *g1 = new TGraph(1, HLAr_min_0to3mm, attenuation_length_0to3mm_arr);
    g1->SetNameTitle("g1", ";HLAr Min (cm);Attenuation Length (cm)");
    g1->SetMarkerStyle(7);
    g1->SetMarkerColor(kRed);
    g1->GetXaxis()->SetLimits(0.0, 105.0);
    g1->GetYaxis()->SetRangeUser(85.0, 140.0);
    g1->Draw("AP");
    legend->AddEntry(g1, r_ranges[0].c_str(), "p");

    TGraph *g2 = new TGraph(attenuation_lengths_3to6mm.size(), HLAr_mins, attenuation_lengths_3to6mm_arr);
    g2->SetName("g2");
    g2->SetMarkerStyle(7);
    g2->SetMarkerColor(kOrange+10);
    g2->SetLineWidth(0);
    g2->Draw("SAME P");
    legend->AddEntry(g2, r_ranges[1].c_str(), "p");

    TGraph *g3 = new TGraph(attenuation_lengths_6to9mm.size(), HLAr_mins, attenuation_lengths_6to9mm_arr);
    g3->SetName("g3");
    g3->SetMarkerStyle(7);
    g3->SetMarkerColor(kYellow);
    g3->SetLineWidth(0);
    g3->Draw("SAME P");
    legend->AddEntry(g3, r_ranges[2].c_str(), "p");

    TGraph *g4 = new TGraph(attenuation_lengths_9to12mm.size(), HLAr_mins, attenuation_lengths_9to12mm_arr);
    g4->SetName("g4");
    g4->SetMarkerStyle(7);
    g4->SetMarkerColor(kGreen);
    g4->SetLineWidth(0);
    g4->Draw("SAME P");
    legend->AddEntry(g4, r_ranges[3].c_str(), "p");

    TGraph *g5 = new TGraph(attenuation_lengths_12to15mm.size(), HLAr_mins, attenuation_lengths_12to15mm_arr);
    g5->SetName("g5");
    g5->SetMarkerStyle(7);
    g5->SetMarkerColor(kBlue);
    g5->SetLineWidth(0);
    g5->Draw("SAME P");
    legend->AddEntry(g5, r_ranges[4].c_str(), "p");

    TGraph *g6 = new TGraph(attenuation_lengths_15to18mm.size(), HLAr_mins, attenuation_lengths_15to18mm_arr);
    g6->SetName("g6");
    g6->SetMarkerStyle(7);
    g6->SetMarkerColor(kMagenta);
    g6->SetLineWidth(0);
    g6->Draw("SAME P");
    legend->AddEntry(g6, r_ranges[5].c_str(), "p");

    TLine *l1 = new TLine(0, 90, 105, 90);
    l1->SetLineColor(kBlack);
    l1->SetLineWidth(2);
    l1->Draw("SAME");
    legend->AddEntry(l1, "Specified Value", "l");

    legend->Draw();
    cmain->Update();
    cmain->Print("/nashome/a/abreaux/Downloads/larsmc_128nm/AttenuationLength_Vs_HLArMin_128nm.root");
}

double Fit_0to3mm(std::string ginput_name)
{
    TFile *file = TFile::Open(ginput_name.c_str());
    TCanvas *canvas = (TCanvas*)file->Get("canvas");
    TGraph *g1 = (TGraph*)canvas->GetPrimitive("g1");

    TF1 *f1 = new TF1("f1", "expo", 2.22, 127.22);
    g1->Fit(f1, "", "", 2.22, 127.22);

    double attenuation_length = -1 * (1 / f1->GetParameter(1));
    return attenuation_length;
}

std::vector<double> Fit_Other(std::string ginput_name)
{
    TFile *file = TFile::Open(ginput_name.c_str());
    TCanvas *canvas = (TCanvas*)file->Get("canvas");
    TGraph *g1 = (TGraph*)canvas->GetPrimitive("g1");

    std::vector<double> attenuation_lengths;
    double HLAr_mins[12] = {5.23, 10.0, 17.0, 25.0, 28.0, 38.0, 40.0, 50.0, 63.0, 75.0, 85.0, 100.0};

    for (int i = 0; i < 12; i++)
    {
        TF1 *f1 = new TF1("f1", "expo", 2.22, 127.22);

        if (HLAr_mins[i] == 5.23)
        {
            g1->Fit(f1, "", "", HLAr_mins[i], 127.22);
        }
        else
        {
            g1->Fit(f1, "+", "", HLAr_mins[i], 127.22);
        }

        double attenuation_length = -1 * (1 / f1->GetParameter(1));
        attenuation_lengths.push_back(attenuation_length);
    }

    return attenuation_lengths;
}

void FitPhotonsVsHLAr_128nm()
{
    std::string r_range_names[33] = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm", "18to21mm", "21to24mm", "24to27mm", "27to30mm", "30to33mm", "33to36mm", "36to39mm", "39to42mm", "42to45mm", "45to48mm", "48to51mm", "51to54mm", "54to57mm", "57to60mm", "60to63mm", "63to66mm", "66to69mm", "69to72mm", "72to75mm", "75to78mm", "78to81mm", "81to84mm", "84to87mm", "87to90mm", "90to93mm", "93to96mm", "96to99mm"};
    double attenuation_length_0to3mm;
    std::vector<double> attenuation_lengths_3to6mm;
    std::vector<double> attenuation_lengths_6to9mm;
    std::vector<double> attenuation_lengths_9to12mm;
    std::vector<double> attenuation_lengths_12to15mm;
    std::vector<double> attenuation_lengths_15to18mm;

    for (int i = 0; i < 19; i++)
    {
        std::string ginput_name = "/nashome/a/abreaux/Downloads/larsmc_128nm/gPhotonCount_vs_r2_" + r_range_names[i] + "_128nm.root";
        if (r_range_names[i] == "0to3mm") 
        { 
            attenuation_length_0to3mm = Fit_0to3mm(ginput_name); 
        }
        else if (r_range_names[i] == "3to6mm") 
        {  
            attenuation_lengths_3to6mm = Fit_Other(ginput_name);
        }
        else if (r_range_names[i] == "6to9mm") 
        {  
            attenuation_lengths_6to9mm = Fit_Other(ginput_name);
        } 
        else if (r_range_names[i] == "9to12mm") 
        {  
            attenuation_lengths_9to12mm = Fit_Other(ginput_name);
        } 
        else if (r_range_names[i] == "12to15mm") 
        {  
            attenuation_lengths_12to15mm = Fit_Other(ginput_name);
        } 
        else if (r_range_names[i] == "15to18mm")
        {
            attenuation_lengths_15to18mm = Fit_Other(ginput_name);
        }
        else {;}
    }

    GraphAttLensVsHLArMin(attenuation_length_0to3mm, attenuation_lengths_3to6mm, attenuation_lengths_6to9mm, attenuation_lengths_9to12mm, attenuation_lengths_12to15mm, attenuation_lengths_15to18mm);
}