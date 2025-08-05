#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

void GraphIt(std::string ginfile_path1, std::vector<std::string> scatlens, std::vector<std::string> r_range_names, std::vector<std::string> wavelengths, int n, std::vector<double> PC_115nm, std::vector<double> PC_125nm, std::vector<double> PC_128nm, std::vector<double> PC_135nm, std::vector<double> PC_140nm, std::vector<double> PC_150nm, std::vector<double> PC_155nm)
{
    double HLAr_sim[14] = {2.22, 5.23, 10.31, 17.93, 25.34, 28.09, 38.25, 40.79, 50.97, 63.65, 76.33, 89.05, 101.83, 127.22}; 

    for (int i = 0; i < r_range_names.size(); i++)
    {
        TCanvas *canvas = new TCanvas("canvas", "Photon Count vs. LAr Height (cm)", 800, 600);
        TLegend *legend = new TLegend(0.585213, 0.730903, 0.885965, 0.881944, "h", "brNDC");
        legend->SetHeader("Scattering Length (cm)", "C");
        legend->SetNColumns(3);
        gStyle->SetPalette(109);

        for (int j = 0; j < wavelengths.size(); j++)
        {
            double PC[n];
            for (int k = 0; k < n; k++)
            {
                if (wavelengths[j] == "115nm") { PC[k] = PC_115nm[i * n + k]; }
                if (wavelengths[j] == "125nm") { PC[k] = PC_125nm[i * n + k]; }
                if (wavelengths[j] == "128nm") { PC[k] = PC_128nm[i * n + k]; }
                if (wavelengths[j] == "135nm") { PC[k] = PC_135nm[i * n + k]; }
                if (wavelengths[j] == "140nm") { PC[k] = PC_140nm[i * n + k]; }
                if (wavelengths[j] == "150nm") { PC[k] = PC_150nm[i * n + k]; }
                if (wavelengths[j] == "155nm") { PC[k] = PC_155nm[i * n + k]; }
            }

            if (wavelengths[j] == "115nm") 
            { 
                TGraph *g1 = new TGraph(n, HLAr_sim, PC);

                g1->SetMarkerColor(kBlack);
                g1->SetMarkerStyle(6);
                g1->SetLineWidth(2);

                g1->SetNameTitle("g1", ";LAr Height (cm);Photon Count");
                g1->Draw("ALP PLC");

                legend->AddEntry(g1, scatlens[j].c_str(), "l");
            }

            if (wavelengths[j] == "125nm") 
            { 
                TGraph *g2 = new TGraph(n, HLAr_sim, PC);

                g2->SetMarkerColor(kBlack);
                g2->SetMarkerStyle(6);
                g2->SetLineWidth(2);

                legend->AddEntry(g2, scatlens[j].c_str(), "l");

                g2->SetName("g2");
                g2->Draw("SAME LP PLC"); 
            }

            if (wavelengths[j] == "128nm") 
            { 
                TGraph *g3 = new TGraph(n, HLAr_sim, PC);

                g3->SetMarkerColor(kBlack);
                g3->SetMarkerStyle(6);
                g3->SetLineWidth(2);

                legend->AddEntry(g3, scatlens[j].c_str(), "l");

                g3->SetName("g3");
                g3->Draw("SAME LP PLC"); 
            }

            if (wavelengths[j] == "135nm") 
            { 
                TGraph *g4 = new TGraph(n, HLAr_sim, PC);

                g4->SetMarkerColor(kBlack);
                g4->SetMarkerStyle(6);
                g4->SetLineWidth(2);

                legend->AddEntry(g4, scatlens[j].c_str(), "l");

                g4->SetName("g4");
                g4->Draw("SAME LP PLC"); 
            }

            if (wavelengths[j] == "140nm") 
            { 
                TGraph *g5 = new TGraph(n, HLAr_sim, PC);

                g5->SetMarkerColor(kBlack);
                g5->SetMarkerStyle(6);
                g5->SetLineWidth(2);

                legend->AddEntry(g5, scatlens[j].c_str(), "l");

                g5->SetName("g5");
                g5->Draw("SAME LP PLC"); 
            }

            if (wavelengths[j] == "150nm") 
            { 
                TGraph *g6 = new TGraph(n, HLAr_sim, PC);

                g6->SetMarkerColor(kBlack);
                g6->SetMarkerStyle(6);
                g6->SetLineWidth(2);

                legend->AddEntry(g6, scatlens[j].c_str(), "l");

                g6->SetName("g6");
                g6->Draw("SAME LP PLC"); 
            }
            if (wavelengths[j] == "155nm")
            {
                TGraph *g7 = new TGraph(n, HLAr_sim, PC);

                g7->SetMarkerColor(kBlack);
                g7->SetMarkerStyle(6);
                g7->SetLineWidth(2);

                legend->AddEntry(g7, scatlens[j].c_str(), "l");

                g7->SetName("g7");
                g7->Draw("SAME LP PLC"); 
            }
        }

        legend->Draw();
        canvas->Update();

        std::string goutfile_name = ginfile_path1 + "all/PCvsR2_" + r_range_names[i] + ".root";
        canvas->Print(goutfile_name.c_str());
        delete canvas;
    }

    return;
}

void GetGraph(std::string ginfile_path1, std::string ginfile_path2, std::vector<std::string> r_range_names, std::vector<std::string> wavelengths, const int n, std::vector<std::string> scatlens)
{
    std::vector<double> PC_115nm;
    std::vector<double> PC_125nm;
    std::vector<double> PC_128nm;
    std::vector<double> PC_135nm;
    std::vector<double> PC_140nm;
    std::vector<double> PC_150nm;
    std::vector<double> PC_155nm;

    for (int i = 0; i < wavelengths.size(); i++)
    {
        for (int j = 0; j < r_range_names.size(); j++)
        {
            std::string ginfile_name = ginfile_path1 + wavelengths[i] + ginfile_path2 + r_range_names[j] + "_" + wavelengths[i] + ".root"; 

            TFile *file = TFile::Open(ginfile_name.c_str());
            TCanvas *ctemp = (TCanvas*)file->Get("canvas");
            TGraph *gtemp = (TGraph*)ctemp->GetPrimitive("g1");

            for (int k = 0; k < n; k++) 
            { 
                if (wavelengths[i] == "115nm") { PC_115nm.push_back(gtemp->GetPointY(k)); }
                if (wavelengths[i] == "125nm") { PC_125nm.push_back(gtemp->GetPointY(k)); }
                if (wavelengths[i] == "128nm") { PC_128nm.push_back(gtemp->GetPointY(k)); }
                if (wavelengths[i] == "135nm") { PC_135nm.push_back(gtemp->GetPointY(k)); }
                if (wavelengths[i] == "140nm") { PC_140nm.push_back(gtemp->GetPointY(k)); }
                if (wavelengths[i] == "150nm") { PC_150nm.push_back(gtemp->GetPointY(k)); }
                if (wavelengths[i] == "155nm") { PC_155nm.push_back(gtemp->GetPointY(k)); }
            }
        }
    }
    GraphIt(ginfile_path1, scatlens, r_range_names, wavelengths, n, PC_115nm, PC_125nm, PC_128nm, PC_135nm, PC_140nm, PC_150nm, PC_155nm);
    return;
}

void GraphPhotonCountVsHLAr_all()
{
    std::vector<std::string> r_range_names = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm", "18to21mm", "21to24mm", "24to27mm", "27to30mm", "30to33mm", "33to36mm", "36to39mm", "39to42mm", "42to45mm", "45to48mm", "48to51mm", "51to54mm", "54to57mm", "57to60mm", "60to63mm", "63to66mm", "66to69mm", "69to72mm", "72to75mm", "75to78mm", "78to81mm", "81to84mm", "84to87mm", "87to90mm", "90to93mm", "93to96mm", "96to99mm"};
    std::vector<std::string> wavelengths = {"115nm", "125nm", "128nm", "135nm", "140nm", "150nm", "155nm"};
    std::vector<std::string> scatlens = {"56.84", "79.3458", "90.0", "107.949", "124.852", "164.531", "187.59"};
    std::string ginfile_path1 = "/nashome/a/abreaux/Downloads/larsmc_";
    std::string ginfile_path2 = "/gPhotonCount_vs_r2_";
    int n = 14; // Number of LAr Height points used in analysis

    GetGraph(ginfile_path1, ginfile_path2, r_range_names, wavelengths, n, scatlens);
    return;
}