#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TH2D.h"



///// Globals /////

int n = 14; // Number of simulated HLAr values
int o = 15; // Number of physically measured data points
int p = 7; // Number of wavelengths / scattering lengths

double HLAr_phys[15] = {4.6796, 9.8299, 17.647, 26.925, 27.431, 39.663, 42.327, 51.854, 64.514, 76.691, 89.353, 89.379, 102.440, 114.953, 128.102};
double PC_phys[15] = {110.3438, 115.6717, 118.8258, 119.5821, 118.6187, 113.4634, 105.7662, 100.9778, 93.0502, 87.508, 80.9819, 81.5163, 75.6169, 69.7663, 66.0869};
double PC_phys_err[15] = {0.3625, 0.3919, 0.3828, 0.6462, 0.3742, 0.4532, 0.4411, 0.4654, 0.4634, 0.4485, 0.4608, 0.6914, 0.4654, 0.4913, 0.3638};

double HLAr_sim[14] = {2.22, 5.23, 10.31, 17.93, 25.34, 28.09, 38.25, 40.79, 50.97, 63.65, 76.33, 89.05, 101.83, 127.22}; 

std::vector<std::string> r_range_names = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm", "18to21mm", "21to24mm", "24to27mm", "27to30mm", "30to33mm", "33to36mm", "36to39mm", "39to42mm", "42to45mm", "45to48mm", "48to51mm", "51to54mm", "54to57mm", "57to60mm", "60to63mm", "63to66mm", "66to69mm", "69to72mm", "72to75mm", "75to78mm", "78to81mm", "81to84mm", "84to87mm", "87to90mm", "90to93mm", "93to96mm", "96to99mm"};
std::vector<std::string> wavelengths = {"115nm", "125nm", "128nm", "135nm", "140nm", "150nm", "155nm"};
std::vector<double> wavelength_nums = {115.0, 125.0, 128.0, 135.0, 140.0, 150.0, 155.0};
std::vector<std::string> scatlens = {"56.84", "79.3458", "90.0", "107.949", "124.852", "164.531", "187.59"};
std::vector<double> scatlens_nums = {56.84, 79.3458, 90.0, 107.949, 124.852, 164.531, 187.59};

float r_range_bins[34] = {0.0, 3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 24.0, 27.0, 30.0, 33.0, 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 60.0, 63.0, 66.0, 69.0, 72.0, 75.0, 78.0, 81.0, 84.0, 87.0, 90.0, 93.0, 96.0, 99.0};
float scatlens_bins[8] = {50.0, 65.0, 85.0, 100.0, 115.0, 140.0, 175.0, 200.0};

std::string ginfile_path = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/PCvsR2_";

///////////////////



double ChiSquaredCaluclation(double observed_total, std::vector<double> PC_eval)
{
    double evaluated_total;
    for (int i = 0; i < o; i++) { evaluated_total += PC_eval[i]; }

    double weight = observed_total / evaluated_total;

    double chi_squared;
    for (int i = 0; i < o; i++)
    {
        chi_squared += (((weight * PC_eval[i]) - PC_phys[i]) * ((weight * PC_eval[i]) - PC_phys[i])) / (PC_phys_err[i] * PC_phys_err[i]);
    }

    return chi_squared;
}

double FindMinimum(std::vector<double> chi_sq_115nm, std::vector<double> chi_sq_125nm, std::vector<double> chi_sq_128nm, std::vector<double> chi_sq_135nm, std::vector<double> chi_sq_140nm, std::vector<double> chi_sq_150nm, std::vector<double> chi_sq_155nm)
{
    double min_chi_squared = chi_sq_135nm[0];

    int total_file_num = r_range_names.size();
    for (int i = 0; i < total_file_num; i++)
    {
        if (min_chi_squared > chi_sq_115nm[i]) { min_chi_squared = chi_sq_115nm[i]; }
        if (min_chi_squared > chi_sq_125nm[i]) { min_chi_squared = chi_sq_125nm[i]; }
        if (min_chi_squared > chi_sq_128nm[i]) { min_chi_squared = chi_sq_128nm[i]; }
        if (min_chi_squared > chi_sq_135nm[i]) { min_chi_squared = chi_sq_135nm[i]; }
        if (min_chi_squared > chi_sq_140nm[i]) { min_chi_squared = chi_sq_140nm[i]; }
        if (min_chi_squared > chi_sq_150nm[i]) { min_chi_squared = chi_sq_150nm[i]; }
        if (min_chi_squared > chi_sq_155nm[i]) { min_chi_squared = chi_sq_155nm[i]; }
    }

    return min_chi_squared;
}

void Make3DChiSquaredHisto(double min_chi_squared, std::vector<double> chi_sq_115nm, std::vector<double> chi_sq_125nm, std::vector<double> chi_sq_128nm, std::vector<double> chi_sq_135nm, std::vector<double> chi_sq_140nm, std::vector<double> chi_sq_150nm, std::vector<double> chi_sq_155nm)
{
    // 3D ChiSquared plot data extraction
    TCanvas *canvas = new TCanvas("canvas", "", 900, 600);
    TH2D *histogram = new TH2D("h1", ";r Range (mm);Scattering Length (cm);Delta Chi Squared", 33, r_range_bins, 7, scatlens_bins);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    gStyle->SetNumberContours(64);

    int total_file_num = r_range_names.size();
    for (int i = 0; i < wavelengths.size(); i++)
    {
        for (int j = 0; j < total_file_num; j++)
        {
            double r_range_num = (j * 3) + 1.5;

            if (wavelengths[i] == "115nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_115nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "125nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_125nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "128nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_128nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "135nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_135nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "140nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_140nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "150nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_150nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "155nm") { histogram->Fill(r_range_num, scatlens_nums[i], (chi_sq_155nm[j] - min_chi_squared)); }
        }
    }

    histogram->Draw("colz");
    canvas->Update();
    canvas->Print("/Users/autobreaux/LArSMC_Downloads/larsmc_all/ChiSq3D.root");
    delete canvas;

    // Individual scattering length data extraction
    TCanvas *tempcanvas = new TCanvas("canvas", "", 800, 600);
    TH1D *temphistogram1 = new TH1D("h1", "115 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);
    TH1D *temphistogram2 = new TH1D("h2", "125 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);
    TH1D *temphistogram3 = new TH1D("h3", "128 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);
    TH1D *temphistogram4 = new TH1D("h4", "135 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);
    TH1D *temphistogram5 = new TH1D("h5", "140 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);
    TH1D *temphistogram6 = new TH1D("h6", "150 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);
    TH1D *temphistogram7 = new TH1D("h7", "155 nm;r Range (mm);Delta Chi Squared;", 33, 0.0, 99.0);

    for (int i = 0; i < wavelengths.size(); i++)
    {
        for (int j = 0; j < total_file_num; j++)
        {
            double r_range_num = (j * 3) + 1.5;

            if (wavelengths[i] == "115nm") { temphistogram1->Fill(r_range_num, (chi_sq_115nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "125nm") { temphistogram2->Fill(r_range_num, (chi_sq_125nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "128nm") { temphistogram3->Fill(r_range_num, (chi_sq_128nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "135nm") { temphistogram4->Fill(r_range_num, (chi_sq_135nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "140nm") { temphistogram5->Fill(r_range_num, (chi_sq_140nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "150nm") { temphistogram6->Fill(r_range_num, (chi_sq_150nm[j] - min_chi_squared)); }
            if (wavelengths[i] == "155nm") { temphistogram7->Fill(r_range_num, (chi_sq_155nm[j] - min_chi_squared)); }
        }
    }

    temphistogram1->Draw();
    temphistogram2->Draw("SAME");
    temphistogram3->Draw("SAME");
    temphistogram4->Draw("SAME");
    temphistogram5->Draw("SAME");
    temphistogram6->Draw("SAME");
    temphistogram7->Draw("SAME");

    tempcanvas->Update();
    tempcanvas->Print("/Users/autobreaux/LArSMC_Downloads/larsmc_all/ChiSq_IndividualScattering.root");
    delete tempcanvas;


    return;
}

void ChiSquaredAnalysis()
{
    std::vector<double> chi_sq_115nm;
    std::vector<double> chi_sq_125nm;
    std::vector<double> chi_sq_128nm;
    std::vector<double> chi_sq_135nm;
    std::vector<double> chi_sq_140nm;
    std::vector<double> chi_sq_150nm;
    std::vector<double> chi_sq_155nm;

    double observed_total;
    for (int i = 0; i < o; i++) { observed_total += PC_phys[i]; }

    int total_file_num = r_range_names.size();
    for (int i = 0; i < total_file_num; i++)
    {
        std::string ginfile_name = ginfile_path + r_range_names[i] + ".root";

        TFile *file = TFile::Open(ginfile_name.c_str());
        TCanvas *ctemp = (TCanvas*)file->Get("canvas");

        TGraph *g1 = (TGraph*)ctemp->GetPrimitive("g1");
        TGraph *g2 = (TGraph*)ctemp->GetPrimitive("g2");
        TGraph *g3 = (TGraph*)ctemp->GetPrimitive("g3");
        TGraph *g4 = (TGraph*)ctemp->GetPrimitive("g4");
        TGraph *g5 = (TGraph*)ctemp->GetPrimitive("g5");
        TGraph *g6 = (TGraph*)ctemp->GetPrimitive("g6");
        TGraph *g7 = (TGraph*)ctemp->GetPrimitive("g7");

        file->Close();
        delete file;

        std::vector<double> PC_sim_eval_115nm;
        std::vector<double> PC_sim_eval_125nm;
        std::vector<double> PC_sim_eval_128nm;
        std::vector<double> PC_sim_eval_135nm;
        std::vector<double> PC_sim_eval_140nm;
        std::vector<double> PC_sim_eval_150nm;
        std::vector<double> PC_sim_eval_155nm;

        for (int j = 0; j < o; j++) { PC_sim_eval_115nm.push_back(g1->Eval(HLAr_phys[j], 0, "S")); }
        for (int j = 0; j < o; j++) { PC_sim_eval_125nm.push_back(g2->Eval(HLAr_phys[j], 0, "S")); }
        for (int j = 0; j < o; j++) { PC_sim_eval_128nm.push_back(g3->Eval(HLAr_phys[j], 0, "S")); }
        for (int j = 0; j < o; j++) { PC_sim_eval_135nm.push_back(g4->Eval(HLAr_phys[j], 0, "S")); }
        for (int j = 0; j < o; j++) { PC_sim_eval_140nm.push_back(g5->Eval(HLAr_phys[j], 0, "S")); }
        for (int j = 0; j < o; j++) { PC_sim_eval_150nm.push_back(g6->Eval(HLAr_phys[j], 0, "S")); }
        for (int j = 0; j < o; j++) { PC_sim_eval_155nm.push_back(g7->Eval(HLAr_phys[j], 0, "S")); }

        chi_sq_115nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_115nm));
        chi_sq_125nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_125nm));
        chi_sq_128nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_128nm));
        chi_sq_135nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_135nm));
        chi_sq_140nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_140nm));
        chi_sq_150nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_150nm));
        chi_sq_155nm.push_back(ChiSquaredCaluclation(observed_total, PC_sim_eval_155nm));
    }

    double min_chi_squared = FindMinimum(chi_sq_115nm, chi_sq_125nm, chi_sq_128nm, chi_sq_135nm, chi_sq_140nm, chi_sq_150nm, chi_sq_155nm);
    Make3DChiSquaredHisto(min_chi_squared, chi_sq_115nm, chi_sq_125nm, chi_sq_128nm, chi_sq_135nm, chi_sq_140nm, chi_sq_150nm, chi_sq_155nm);

    return;
}

// TCanvas *canvas = new TCanvas("canvas", "Photon Count vs. LAr Height (cm)", 800, 600);
    // TLegend *legend = new TLegend(0.585213, 0.730903, 0.885965, 0.881944, "h", "brNDC");

    // // Physically Measured Values Graph
    // TGraph *gphys = new TGraph(o, HLAr_phys, PC_phys);
    // gphys->SetMarkerColor(kRed+4);
    // gphys->SetMarkerStyle(20);
    // gphys->SetLineColor(kRed+4);
    // gphys->SetLineWidth(2);
    // gphys->Draw("LP"); 
    // legend->AddEntry(gphys, "Measurements", "p");

    // // Evaluated Measured Values Calculation & Graph
    // double PC_phys_eval[n];
    // for (int i = 0; i < n; i++) 
    // { 
    //     PC_phys_eval[i] = gphys->Eval(HLAr_sim[i]); 
    // }

    // TGraph *gphyseval = new TGraph(n, HLAr_sim, PC_phys_eval);
    // gphyseval->SetMarkerColor(kRed+2);
    // gphyseval->SetMarkerStyle(20);
    // gphyseval->Draw("SAME P"); 
    // legend->AddEntry(gphyseval, "Evaluations", "p");

    // // Save & Close Canvas
    // legend->Draw();
    // canvas->Update();
    // canvas->Print("/nashome/a/abreaux/Downloads/larsmc_all/RealPCvsHLAr.root");
    // delete canvas;

    // // Transport
    // std::vector<double> PC_phys_eval_vec;
    // for (int i = 0; i < n; i++)
    // {
    //     PC_phys_eval_vec.push_back(PC_phys_eval[i]);
    // }

    // Make3DChiSquaredHisto(PC_phys_eval_vec);

// std::vector<double> PC_115nm;
// std::vector<double> PC_125nm;
// std::vector<double> PC_128nm;
// std::vector<double> PC_135nm;
// std::vector<double> PC_140nm;
// std::vector<double> PC_150nm;
// std::vector<double> PC_155nm;

// for (int j = 0; j < n; j++)
// {
//     PC_115nm.push_back(g1->GetPointY(j));
//     PC_125nm.push_back(g2->GetPointY(j));
//     PC_128nm.push_back(g3->GetPointY(j));
//     PC_135nm.push_back(g4->GetPointY(j));
//     PC_140nm.push_back(g5->GetPointY(j));
//     PC_150nm.push_back(g6->GetPointY(j));
//     PC_155nm.push_back(g7->GetPointY(j));
// }

// double chi_sq_115nm = ChiSquaredCaluclation(PC_phys_eval, PC_115nm);
// double chi_sq_125nm = ChiSquaredCaluclation(PC_phys_eval, PC_125nm);
// double chi_sq_128nm = ChiSquaredCaluclation(PC_phys_eval, PC_128nm);
// double chi_sq_135nm = ChiSquaredCaluclation(PC_phys_eval, PC_135nm);
// double chi_sq_140nm = ChiSquaredCaluclation(PC_phys_eval, PC_140nm);
// double chi_sq_150nm = ChiSquaredCaluclation(PC_phys_eval, PC_150nm);
// double chi_sq_155nm = ChiSquaredCaluclation(PC_phys_eval, PC_155nm);