#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

void MakeALSLGraphPDFs(std::string norm_infile_name, std::string norm_outfile_pdf_name)
{
    TFile *infile = TFile::Open(norm_infile_name.c_str());
    TCanvas *c1 = (TCanvas*)infile->Get("canvas");

    c1->Print(norm_outfile_pdf_name.c_str());
}

void MakeALSLFitPDFs(std::string fit_infile_name, std::string fit_outfile_pdf_name)
{
    TFile *infile = TFile::Open(fit_infile_name.c_str());
    TCanvas *c1 = (TCanvas*)infile->Get("canvas");

    c1->Print(fit_outfile_pdf_name.c_str());
}

void MakeALSLCorrectionPDFs(std::string correction_infile_path, std::string correction_outfile_pdf_path)
{
    std::vector<std::string> r_range_names = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm"};

    for (int i = 0; i < r_range_names.size(); i ++)
    {
        std::string correction_infile_name = correction_infile_path + r_range_names[i] + ".root";
        std::string correction_outfile_pdf_name = correction_outfile_pdf_path + r_range_names[i] +".pdf";

        TFile *infile = TFile::Open(correction_infile_name.c_str());
        TCanvas *c1 = (TCanvas*)infile->Get("canvas");

        c1->Print(correction_outfile_pdf_name.c_str());
    }
}

void MakePDFs()
{
    std::string norm_infile_name = "/nashome/a/abreaux/Downloads/larsmc_all/ScatLens_Vs_AttLens.root";
    std::string fit_infile_name = "/nashome/a/abreaux/Downloads/larsmc_all/FitScatLens_Vs_AttLens.root";
    std::string correction_infile_name = "/nashome/a/abreaux/Downloads/larsmc_all/CorrectionScatLens_Vs_AttLens_";
    
    std::string norm_outfile_pdf_name = "/nashome/a/abreaux/Downloads/larsmc_all/SLvsAL.pdf";
    std::string fit_outfile_pdf_name = "/nashome/a/abreaux/Downloads/larsmc_all/FitSLvsAL.pdf";
    std::string correction_outfile_pdf_name = "/nashome/a/abreaux/Downloads/larsmc_all/CorrectSLvsAL_";

    MakeALSLGraphPDFs(norm_infile_name, norm_outfile_pdf_name);
    MakeALSLFitPDFs(fit_infile_name, fit_outfile_pdf_name);
    MakeALSLCorrectionPDFs(correction_infile_name, correction_outfile_pdf_name);
}