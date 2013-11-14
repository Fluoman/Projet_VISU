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

//http://www.developpez.net/forums/d1028267/c-cpp/c/debuter/determiner-nombre-lignes-nombre-colonnes-d-fichier-donnees/
void recupLigneColonne(const char *NomFich, unsigned int Comptage[2])
{
    FILE *FichLec;
    /* NbL nombre de lignes  */
	int NbLFich=0;

	/* NbC nombre de colonnes   */
	int NbCFich=0;

	char saisie;

	FichLec = fopen(NomFich,"r");
	if (FichLec != NULL){
		while ((saisie = getc(FichLec)) != EOF){
            if (saisie == '\n'){
                ++NbLFich;
            }
            if (saisie ==' ' && NbLFich==0){
                ++NbCFich;
            }
        }
        fclose(FichLec);
        Comptage[0]=NbLFich+1;
        Comptage[1]=NbCFich+1;
    }
    return;
}

int main ()
    {
        static float DELTA = 100;
        string entree = "test_interpol.txt";
        string sortie = "sortie_interpol_hardy.txt";
        static ifstream flux_entree;
        static ofstream flux_sortie;
        unsigned int numLC[2];
        float minX, minY, maxX, maxY;
        string POS_1, POS_2, valeur;
        map Carte;

//Récupérer le nombre de points initiaux et de colonnes
        recupLigneColonne(entree.c_str(), numLC);

        flux_entree.open(entree.c_str());
        flux_sortie.open(sortie.c_str());
//Récupérer les points initiaux et leurs différentes valeurs
        for (unsigned int nb_ligne = 0; nb_ligne<numLC[0]; nb_ligne++) {
            for (unsigned int nb_col = 0; nb_col<numLC[1]; nb_col++) {
                switch (nb_col) {
                case 0:
                    flux_entree >> POS_1;
                    break;
                case 1:
                    flux_entree >> POS_2;
                    break;
                case 2:
                    Carte.InitialPoints.push_back(Point(atof(POS_1.c_str()),atof(POS_2.c_str())));
                    flux_entree >> valeur;
                    Carte.InitialPoints[nb_ligne].value.push_back(atof(valeur.c_str()));
                    break;
                default:
                    flux_entree >> valeur;
                    Carte.InitialPoints[nb_ligne].value.push_back(atof(valeur.c_str()));
                    break;
                }
            }
        }
//Récupérer les dimensions de la carte à afficher
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
		Carte.computeHardy();
//Calcul des points interpolés
        for (unsigned int num_pointX = 0; num_pointX < DELTA ; num_pointX++) {
            for (unsigned int num_pointY = 0; num_pointY < DELTA ; num_pointY++) {
                Point nouveau_point(minX+(maxX-minX)/DELTA*(float)num_pointX,minY+(maxY-minY)/DELTA*(float)num_pointY);
                Carte.hardy(nouveau_point);
                //Carte.shepard(nouveau_point);
                Carte.Carte.push_back(nouveau_point);
            }
        }

//Ecriture des points interpolés dans le fichier de sortie
        for (unsigned int i = 0; i<Carte.Carte.size(); i++) {
            flux_sortie << Carte.Carte[i].getLat() << " " << Carte.Carte[i].getLon() << " " << Carte.Carte[i].value[0] << endl ;
        }

        flux_entree.close();
        flux_sortie.close();
        return 0;
    }
