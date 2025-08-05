#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TGraphErrors.h"



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
std::vector<double> scatlens_nums = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5};

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

void GraphChiSquaredRCurves()
{
    double observed_total;
    for (int i = 0; i < o; i++) { observed_total += PC_phys[i]; }

    for (int i = 0; i < r_range_names.size(); i++)
    {
        // Extract 128 nm Data
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

        for (int j = 0; j < p; j++) 
        {
            std::string canvas_name = wavelengths[j] + " ~ r = " + r_range_names[i];
            TCanvas *cmain = new TCanvas("canvas", canvas_name.c_str(), 800, 600);
            TLegend *legend = new TLegend(0.532581, 0.666667, 0.885965, 0.881944, "h", "brNDC");
            legend->SetHeader("Legend", "C");
        
            // Extract and weight results, then plot with real data.
            double PC_sim[14];
            if (wavelengths[j] == "115nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g1->GetPointY(k); }}
            if (wavelengths[j] == "125nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g2->GetPointY(k); }}
            if (wavelengths[j] == "128nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g3->GetPointY(k); }}
            if (wavelengths[j] == "135nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g4->GetPointY(k); }}
            if (wavelengths[j] == "140nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g5->GetPointY(k); }}
            if (wavelengths[j] == "150nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g6->GetPointY(k); }}
            if (wavelengths[j] == "155nm") { for(int k = 0; k < n; k++) { PC_sim[k] = g7->GetPointY(k); }}

            std::vector<double> PC_sim_eval;
            if (wavelengths[j] == "115nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g1->Eval(HLAr_phys[k], 0, "S")); }}
            if (wavelengths[j] == "125nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g2->Eval(HLAr_phys[k], 0, "S")); }}
            if (wavelengths[j] == "128nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g3->Eval(HLAr_phys[k], 0, "S")); }}
            if (wavelengths[j] == "135nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g4->Eval(HLAr_phys[k], 0, "S")); }}
            if (wavelengths[j] == "140nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g5->Eval(HLAr_phys[k], 0, "S")); }}
            if (wavelengths[j] == "150nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g6->Eval(HLAr_phys[k], 0, "S")); }}
            if (wavelengths[j] == "155nm") { for(int k = 0; k < o; k++) { PC_sim_eval.push_back(g7->Eval(HLAr_phys[k], 0, "S")); }}

            double evaluated_total = 0;
            for (int k = 0; k < o; k++) { evaluated_total += PC_sim_eval[k]; }
            double weight = observed_total / evaluated_total;

            double PC_sim_weighted[14];
            for (int k = 0; k < 14; k++) { PC_sim_weighted[k] = (PC_sim[k] * weight); }

            double PC_sim_eval_weighted[15];
            for (int k = 0; k < o; k++) { PC_sim_eval_weighted[k] =  (PC_sim_eval[k] * weight); }

            // Graph Simulated, Extracted, and Real data
            auto *greal = new TGraphErrors(15, HLAr_phys, PC_phys, NULL, PC_phys_err);
            std::string greal_name = r_range_names[i] + ";HLAr (cm);Weighted Photon Count";
            greal->SetNameTitle("greal", greal_name.c_str());
            greal->GetYaxis()->SetRangeUser(0, 250);
            greal->SetMarkerStyle(6);
            greal->SetMarkerColor(kBlue);
            greal->SetLineWidth(2);
            greal->SetLineColor(kBlue);
            greal->Draw("APE");
            legend->AddEntry(greal, "Real Data", "l");

            TGraph *gsim = new TGraph(14, HLAr_sim, PC_sim_weighted);
            gsim->SetName("gsim");
            gsim->SetLineColor(kRed);
            gsim->SetLineWidth(2);
            gsim->Draw("L");
            legend->AddEntry(gsim, "Simulated Data", "l");

            TGraph *gsim_eval = new TGraph(15, HLAr_phys, PC_sim_eval_weighted);
            gsim_eval->SetName("gsim_eval");
            gsim_eval->SetMarkerStyle(6);
            gsim_eval->SetMarkerColor(kGreen);
            gsim_eval->Draw("P");
            legend->AddEntry(gsim_eval, "Extracted Data", "p");

            // Include Chi Squared Calculation in Legend
            double chi_squared = ChiSquaredCaluclation(observed_total, PC_sim_eval);
            legend->AddEntry((TObject*)0, TString::Format("Chi Squared = %g", chi_squared), "");

            legend->Draw();
            cmain->Update();
            std::string outfile_name = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/PCvsR2wRealData_" + wavelengths[j] + r_range_names[i] + ".root";
            cmain->Print(outfile_name.c_str());

            delete cmain;
        }
    }

    return;
}

