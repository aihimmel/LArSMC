#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TF1.h"

std::vector<double> GetSlopeIntercept(std::string infile)
{
    TFile *file = TFile::Open(infile.c_str());
    TCanvas *canvas = (TCanvas*)file->Get("canvas");

    // Slopes and intercepts vector. It will call push back with the intercept, then slope of each fit line.
    std::vector<double> IS_vec;

    TF1 *f1 = (TF1*)canvas->GetPrimitive("f1");
    IS_vec.push_back(f1->GetParameter(0));
    IS_vec.push_back(f1->GetParameter(1));

    TF1 *f2 = (TF1*)canvas->GetPrimitive("f2");
    IS_vec.push_back(f2->GetParameter(0));
    IS_vec.push_back(f2->GetParameter(1));

    TF1 *f3 = (TF1*)canvas->GetPrimitive("f3");
    IS_vec.push_back(f3->GetParameter(0));
    IS_vec.push_back(f3->GetParameter(1));

    TF1 *f4 = (TF1*)canvas->GetPrimitive("f4");
    IS_vec.push_back(f4->GetParameter(0));
    IS_vec.push_back(f4->GetParameter(1));

    TF1 *f5 = (TF1*)canvas->GetPrimitive("f5");
    IS_vec.push_back(f5->GetParameter(0));
    IS_vec.push_back(f5->GetParameter(1));

    TF1 *f6 = (TF1*)canvas->GetPrimitive("f6");
    IS_vec.push_back(f6->GetParameter(0));
    IS_vec.push_back(f6->GetParameter(1));

    return IS_vec;
}

std::vector<double> GetAttLens(std::string infile)
{
    TFile *file = TFile::Open(infile.c_str());
    TCanvas *canvas = (TCanvas*)file->Get("canvas");

    TGraph *g1 = (TGraph*)canvas->GetPrimitive("g1");
    TGraph *g2 = (TGraph*)canvas->GetPrimitive("g2");
    TGraph *g3 = (TGraph*)canvas->GetPrimitive("g3");
    TGraph *g4 = (TGraph*)canvas->GetPrimitive("g4");
    TGraph *g5 = (TGraph*)canvas->GetPrimitive("g5");
    TGraph *g6 = (TGraph*)canvas->GetPrimitive("g6");

    Double_t *attlens_0to3mm = g1->GetY();
    Double_t *attlens_3to6mm = g2->GetY();
    Double_t *attlens_6to9mm = g3->GetY();
    Double_t *attlens_9to12mm = g4->GetY();
    Double_t *attlens_12to15mm = g5->GetY();
    Double_t *attlens_15to18mm = g6->GetY();

    std::vector<double> attlens;
    int n = g1->GetN();

    for (int i = 0; i < n; i++) { attlens.push_back(attlens_0to3mm[i]); }
    for (int i = 0; i < n; i++) { attlens.push_back(attlens_3to6mm[i]); }
    for (int i = 0; i < n; i++) { attlens.push_back(attlens_6to9mm[i]); }
    for (int i = 0; i < n; i++) { attlens.push_back(attlens_9to12mm[i]); }
    for (int i = 0; i < n; i++) { attlens.push_back(attlens_12to15mm[i]); }
    for (int i = 0; i < n; i++) { attlens.push_back(attlens_15to18mm[i]); }

    return attlens;
}

std::vector<double> DoCorrection(int n, std::vector<double> IS_vec, std::vector<double> attlens)
{
    std::vector<double> corrected_attlens_vec;

    // Not subtracting intercept from the measured attenuation length in r = 0-3mm range (first for loop) because 0 falls within its confidence range.
    for (int i = 0; i < n; i++)
    {
        double corrected_attlens = (attlens[i] - IS_vec[0])/ IS_vec[1];
        corrected_attlens_vec.push_back(corrected_attlens);
    }
    for (int i = 0; i < n; i++)
    {
        double corrected_attlens = (attlens[i + n] - IS_vec[2]) / IS_vec[3];
        corrected_attlens_vec.push_back(corrected_attlens);
    }
    for (int i = 0; i < n; i++)
    {
        double corrected_attlens = (attlens[i + (2 * n)] - IS_vec[4]) / IS_vec[5];
        corrected_attlens_vec.push_back(corrected_attlens);
    }
    for (int i = 0; i < n; i++)
    {
        double corrected_attlens = (attlens[i + (3 * n)] - IS_vec[6]) / IS_vec[7];
        corrected_attlens_vec.push_back(corrected_attlens);
    }
    for (int i = 0; i < n; i++)
    {
        double corrected_attlens = (attlens[i + (4 * n)] - IS_vec[8]) / IS_vec[9];
        corrected_attlens_vec.push_back(corrected_attlens);
    }
    for (int i = 0; i < n; i++)
    {
        double corrected_attlens = (attlens[i + (5 * n)] - IS_vec[10]) / IS_vec[11];
        corrected_attlens_vec.push_back(corrected_attlens);
    }

    return corrected_attlens_vec;
}

void GraphCorrection(const int n, std::vector<std::string> r_range_names, std::vector<double> corrected_attlens)
{
    std::string r_ranges[33] = {"[0,3]", "(3,6]", "(6,9]", "(9,12]", "(12,15]", "(15,18]", "(18,21]", "(21,24]", "(24,27]", "(27,30]", "(30,33]", "(33,36]", "(36,39]", "(39,42]", "(42,45]", "(45,48]", "(51,54]", "(54,57]", "(57,60]", "(60,63]", "(63,66]", "(66,69]", "(69,72]", "(72,75]", "(75,78]", "(78,81]", "(81,84]", "(84,87]", "(87,90]", "(90,93]", "(93,96]", "(96,99]"};
    double scatlens[7] = {56.84, 79.3458, 90.0, 107.949, 124.852, 164.531, 187.59}; // n
    int colors[6] = {632, 810, 400, 416, 600, 616}; // r_range_names.size()

    std::vector<double> corrected_attlens_0to3mm;
        for (int i = 0; i < n; i++) { corrected_attlens_0to3mm.push_back(corrected_attlens[i]); }
    double corrected_attlens_0to3mm_arr[corrected_attlens_0to3mm.size()];
        for (int i = 0; i < n; i++) { corrected_attlens_0to3mm_arr[i] = corrected_attlens_0to3mm[i]; }

    std::vector<double> corrected_attlens_3to6mm;
        for (int i = 0; i < n; i++) { corrected_attlens_3to6mm.push_back(corrected_attlens[i + n]); }
    double corrected_attlens_3to6mm_arr[corrected_attlens_3to6mm.size()];
        for (int i = 0; i < n; i++) { corrected_attlens_3to6mm_arr[i] = corrected_attlens_3to6mm[i]; }

    std::vector<double> corrected_attlens_6to9mm;
        for (int i = 0; i < n; i++) { corrected_attlens_6to9mm.push_back(corrected_attlens[i + (2 * n)]); }
    double corrected_attlens_6to9mm_arr[corrected_attlens_6to9mm.size()];
        for (int i = 0; i < n; i++) { corrected_attlens_6to9mm_arr[i] = corrected_attlens_6to9mm[i]; }

    std::vector<double> corrected_attlens_9to12mm;
        for (int i = 0; i < n; i++) { corrected_attlens_9to12mm.push_back(corrected_attlens[i + (3 * n)]); }
    double corrected_attlens_9to12mm_arr[corrected_attlens_9to12mm.size()];
        for (int i = 0; i < n; i++) { corrected_attlens_9to12mm_arr[i] = corrected_attlens_9to12mm[i]; }

    std::vector<double> corrected_attlens_12to15mm;
        for (int i = 0; i < n; i++) { corrected_attlens_12to15mm.push_back(corrected_attlens[i + (4 * n)]); }
    double corrected_attlens_12to15mm_arr[corrected_attlens_12to15mm.size()];
        for (int i = 0; i < n; i++) { corrected_attlens_12to15mm_arr[i] = corrected_attlens_12to15mm[i]; }

    std::vector<double> corrected_attlens_15to18mm;
        for (int i = 0; i < n; i++) { corrected_attlens_15to18mm.push_back(corrected_attlens[i + (5 * n)]); }
    double corrected_attlens_15to18mm_arr[corrected_attlens_15to18mm.size()];
        for (int i = 0; i < n; i++) { corrected_attlens_15to18mm_arr[i] = corrected_attlens_15to18mm[i]; }

    for (int i = 0; i < r_range_names.size(); i++)
    {
        TCanvas *canvas = new TCanvas("canvas", "", 800, 600);
        TLegend *legend = new TLegend(0.12782, 0.727431, 0.428571, 0.876736, "h", "brNDC");
        legend->SetHeader(r_range_names[i].c_str(), "C");

        TGraph *g1 = new TGraph(n);
        if (i == 0) {for (int j = 0; j < n; j++) { g1->SetPoint(j, scatlens[j], corrected_attlens_0to3mm_arr[j]); }}
        if (i == 1) {for (int j = 0; j < n; j++) { g1->SetPoint(j, scatlens[j], corrected_attlens_3to6mm_arr[j]); }}
        if (i == 2) {for (int j = 0; j < n; j++) { g1->SetPoint(j, scatlens[j], corrected_attlens_6to9mm_arr[j]); }}
        if (i == 3) {for (int j = 0; j < n; j++) { g1->SetPoint(j, scatlens[j], corrected_attlens_9to12mm_arr[j]); }}
        if (i == 4) {for (int j = 0; j < n; j++) { g1->SetPoint(j, scatlens[j], corrected_attlens_12to15mm_arr[j]); }}
        if (i == 5) {for (int j = 0; j < n; j++) { g1->SetPoint(j, scatlens[j], corrected_attlens_15to18mm_arr[j]); }}
        g1->SetNameTitle("g1", ";Scattering Length (cm);Attenuation Length (cm)");
        g1->SetMarkerStyle(20);
        g1->SetMarkerSize(0.7);
        g1->SetMarkerColor(colors[i]);
        g1->GetXaxis()->SetLimits(40.0, 200.0);
        g1->GetYaxis()->SetRangeUser(40.0, 200.0);
        g1->Draw("AP");
        legend->AddEntry(g1, "Measured Values", "p");

        TF1 *f1 = new TF1("f1", "[0]+[1]*x", 40, 200);
        g1->Fit(f1, "N", "", 50, 200);
        f1->SetLineColor(colors[i]);
        f1->SetLineStyle(2);
        f1->Draw("SAME");
        legend->AddEntry(f1, "Fit", "l");

        legend->Draw();
        std::string outfile_path = "/nashome/a/abreaux/Downloads/larsmc_all/CorrectionAttLens_Vs_ScatLens_" + r_range_names[i] + ".root";
        canvas->Print(outfile_path.c_str());
        delete canvas;
    }
}

void CorrectScatLensVsAttLens()
{
    std::string file_path = "/nashome/a/abreaux/Downloads/larsmc_all/FitAttLens_Vs_ScatLens.root";
    std::vector<std::string> r_range_names = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm"};
    int n = 7; // Number of wavelengths in data

    std::vector<double> IS_vec_normal = GetSlopeIntercept(file_path);

    std::vector<double> attlens_normal = GetAttLens(file_path);

    std::vector<double> corrected_attlens_normal = DoCorrection(n, IS_vec_normal, attlens_normal);

    GraphCorrection(n, r_range_names, corrected_attlens_normal);
}