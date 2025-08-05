#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TROOT.h"

void MakeClassFiles_140nm()
{
    std::string file_path = "/exp/dune/data/users/abreaux/";
    std::vector<std::string> file_names = {"larsmc_h2d22cm_140nm.root", "larsmc_h5d23cm_140nm.root", "larsmc_h10d31cm_140nm.root", "larsmc_h17d93cm_140nm.root", "larsmc_h25d34cm_140nm.root", "larsmc_h28d09cm_140nm.root", "larsmc_h38d25cm_140nm.root", "larsmc_h40d79cm_140nm.root", "larsmc_h50d97cm_140nm.root", "larsmc_h63d65cm_140nm.root", "larsmc_h76d33cm_140nm.root", "larsmc_h89d05cm_140nm.root", "larsmc_h101d83cm_140nm.root", "larsmc_h127d22cm_140nm.root"};
    std::vector<std::string> class_names = {"Track_h2d22cm_140nm", "Track_h5d23cm_140nm", "Track_h10d31cm_140nm", "Track_h17d93cm_140nm", "Track_h25d34cm_140nm", "Track_h28d09cm_140nm", "Track_h38d25cm_140nm", "Track_h40d79cm_140nm", "Track_h50d97cm_140nm", "Track_h63d65cm_140nm", "Track_h76d33cm_140nm", "Track_h89d05cm_140nm", "Track_h101d83cm_140nm", "Track_h127d22cm_140nm"};

    for(int i = 0; i < file_names.size(); i++)
    {
        std::string file_name = file_path + file_names[i];
        std::string class_name = class_names[i];
        
        TFile *file = TFile::Open(file_name.c_str());
        TTree *TrackTree = (TTree*)file->Get("TrackTree");
        TrackTree->MakeClass(class_name.c_str());
    }

    return;
}