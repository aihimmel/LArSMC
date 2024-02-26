#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoMaterial.h"

void gdml_vis(TString gdml_file) 
{
    gSystem->Load("libGeom");
    gSystem->Load("libGdml");
    TGeoManager *geom = TGeoManager::Import(gdml_file);

    TList *materials = gGeoManager->GetListOfMaterials();
    TIter next(materials);
    TGeoMaterial *mat;
    while ((mat = (TGeoMaterial*)next())) mat->SetTransparency(50);
    gGeoManager->GetTopVolume()->Draw("ogl");

    /*
    TGeoMaterial *mat_sipm = geom->GetMaterial("SI");
    mat_sipm->SetTransparency( 100 );

    TGeoMaterial *mat_lar = geom->GetMaterial("LAr");
    mat_lar->SetTransparency( 80 );

    TGeoMaterial *mat_gar = geom->GetMaterial("GAr");
    mat_lar->SetTransparency( 30 );

    TGeoMaterial *mat_ss = geom->GetMaterial("steel_stainless");
    mat_lar->SetTransparency( 20 );

    TGeoMaterial *mat_air = geom->GetMaterial("Air");
    mat_lar->SetTransparency( 50 );
    
    TGeoVolume *world = gGeoManager->GetTopVolume();
    world->SetLineColor( 18 );
    
    geom->SetTopVisible();

    std::cout << "Getting Volume..." << std::endl;
    
    TGeoVolume *tank = geom->GetVolume("volTank");
    tank->SetLineColor( 11 );

    TGeoVolume *cage = geom->GetVolume("volCage");
    cage->SetLineColor( 13 );

    TGeoVolume *gar = geom->GetVolume("volGAr");
    gar->SetLineColor( 33 );

    TGeoVolume *lar = geom->GetVolume("volLAr");
    lar->SetLineColor( 9 );
    
    for(int i = 0; i < 6; i++)
    {
        std::cout << Form("volOpDet_%d", i) << std::endl;
        TGeoVolume *sipm = geom->GetVolume(Form("volOpDet_%d", i));
        if(sipm)
        {
            sipm->SetLineColor( 28 );
        }
    }

    world->Draw("ogl");   
    */
}

