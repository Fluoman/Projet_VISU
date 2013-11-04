#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <deque>
#include "point.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    static string directory = "D:\\Seb\\Scribouillages\\Autres\\Compil\\Projet_VISU\\";
    string nom_stations = "FichierDesSitesDeAirRhoneAlpes.csv";
    string val_stations = "ParticulePM10Aout2012.csv";
    string commun = "common.csv";
    nom_stations = directory+nom_stations;
    val_stations = directory+val_stations;
    commun = directory+commun;
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

    cout << "Hello world!" << endl;
    return 0;
}
