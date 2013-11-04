#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <deque>
#include "point.h"
#include "map.h"

using namespace std;

int parser()
{
    string nom_stations = "FichierDesSitesDeAirRhoneAlpes.csv";
    string val_stations = "ParticulePM10Aout2012.csv";
    string commun = "common.csv";
    nom_stations = nom_stations;
    val_stations = val_stations;
    commun = commun;
    static ifstream flux_coord;
    static ifstream flux_val;
    static ofstream flux_out;

    flux_coord.open(nom_stations.c_str());
    flux_val.open(val_stations.c_str());
    flux_out.open(commun.c_str());
    string Nom;
    string Longitude;
    string Latitude;
    string blank;
    string STRING_val;
        for(unsigned int num_colonne = 1 ; num_colonne<=16; num_colonne++) {
            switch (num_colonne) {
                case 2:
                    flux_coord >> Nom;
                    break;
                case 6:
                    flux_coord >> Longitude;
                    break;
                case 7:
                    flux_coord >> Latitude;
                    break;
                default:
                    flux_coord >> blank;
                    break;
            }
        }
        flux_out << Nom << ";" << Longitude << ";" << Latitude << ";" << endl;

        for(unsigned int num_colonne = 0 ; num_colonne<=721; num_colonne++){
                flux_val >> blank;
        }

        for(unsigned int num_colonne = 1 ; num_colonne<=16; num_colonne++) {
            switch (num_colonne) {
                case 2:
                    flux_coord >> Nom;
                    break;
                case 6:
                    flux_coord >> Longitude;
                    break;
                case 7:
                    flux_coord >> Latitude;
                    break;
                default:
                    flux_coord >> blank;
                    break;
            }
        }

        Point FIRST(atof(Longitude.c_str()), atof(Latitude.c_str()));

        for(unsigned int num_colonne = 0 ; num_colonne<=721; num_colonne++) {
            flux_val >> blank;
            if (num_colonne >= 1 && num_colonne < 31)
                FIRST.value.push_back(atof(blank.c_str()));
        }
        flux_out << Nom << ";" << Longitude << ";" << Latitude << ";" << FIRST.distance(FIRST) << endl;

    for (unsigned int num_ligne = 2; num_ligne <=10; num_ligne++){
        for(unsigned int num_colonne = 1 ; num_colonne<=16; num_colonne++) {
            switch (num_colonne) {
                case 2:
                    flux_coord >> Nom;
                    break;
                case 6:
                    flux_coord >> Longitude;
                    break;
                case 7:
                    flux_coord >> Latitude;
                    break;
                default:
                    flux_coord >> blank;
                    break;
            }
        }
        Point TEST(atof(Longitude.c_str()), atof(Latitude.c_str()));    //il faut que les séparateurs pour la décimale soient des points
        for(unsigned int num_colonne = 0 ; num_colonne<=721; num_colonne++) {
            flux_val >> blank;
            if (num_colonne >= 1 && num_colonne < 31)
                TEST.value.push_back(atof(blank.c_str()));
        }
        flux_out << Nom << ";" << Longitude << ";" << Latitude << ";" << TEST.distance(FIRST) << endl;
        TEST.~Point();
    }

    flux_coord.close();
    flux_out.close();
    flux_val.close();
    return 0;
}

int main ()
    {
        static float DELTA = 100;
        string entree = "test_interpol.txt";
        string sortie = "sortie_interpol_hardy.txt";
        static ifstream flux_entree;
        static ofstream flux_sortie;

        flux_entree.open(entree.c_str());
        flux_sortie.open(sortie.c_str());

        map Carte;
        float minX, minY, maxX, maxY;
        for (unsigned int i = 0; i < Carte.InitialPoints.size(); i++){
            if (i==0) {
                minX = Carte.InitialPoints[i].getLat();
                maxX = Carte.InitialPoints[i].getLat();
                minY = Carte.InitialPoints[i].getLon();
                maxY = Carte.InitialPoints[i].getLon();
            } else {
                if (Carte.InitialPoints[i].getLat() < minX)
                    minX = Carte.InitialPoints[i].getLat();
                if (Carte.InitialPoints[i].getLat() > maxX)
                    maxX = Carte.InitialPoints[i].getLat();


                if (Carte.InitialPoints[i].getLon() < minY)
                    minY = Carte.InitialPoints[i].getLon();
                if (Carte.InitialPoints[i].getLon() > maxY)
                    maxY = Carte.InitialPoints[i].getLon();
            }
            flux_sortie << Carte.InitialPoints[i].getLat() << " " << Carte.InitialPoints[i].getLon() << " " << Carte.InitialPoints[i].value[0] << endl ;
        }

        for (unsigned int num_pointX = 0; num_pointX < DELTA ; num_pointX++) {
            for (unsigned int num_pointY = 0; num_pointY < DELTA ; num_pointY++) {
                Point nouveau_point(minX+(maxX-minX)/DELTA*(float)num_pointX,minY+(maxY-minY)/DELTA*(float)num_pointY);
                Carte.hardy(nouveau_point);
            }
        }

        for (unsigned int i = 0; i<Carte.Carte.size(); i++) {
            flux_sortie << Carte.Carte[i].getLat() << " " << Carte.Carte[i].getLon() << " " << Carte.Carte[i].value[0] << endl ;
        }

        flux_entree.close();
        flux_sortie.close();
        return 0;
    }
