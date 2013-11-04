#include "map.h"
#include "point.h"
#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

map::map()
{
}

float map::shepard(Point &P, unsigned int i) {
    float numerator = 0.0;
    float denominator = 0.0;
    std::vector<Point>::iterator it = this->InitialPoints.begin();
    while (it != this->InitialPoints.end()) {
        float dist = (*it).distanceEuclidienne(P);
        float value = (*it).getValue(i);
		if (value != -1) {
	        if (dist == 0) {
					P.value.push_back(value);
	                return value;
	   	     }
	        numerator += value/dist;
 	       	denominator += 1/dist;
		}
        it++;
    }
	if (denominator != 0) {
		P.value.push_back(numerator/denominator);
	} else {
		P.value.push_back(-1);
		return -1;
	}
	return numerator/denominator;

}
void map::computeHardy() {
// Resolution du systeme pour hardy
// coeffHardy est un vecteur de vecteur coeffs, les coeffs étant dans le meme ordre que les points initiaux
	float c = 1;
	int size = InitialPoints.size();
	for (int k=0;k<InitialPoints[0].value.size();k++) {
	
		std::vector<float> coeff_i;
		// Résoudre le systee linéaire pour hardy
		// Resultat de la résolution dans coeff_i
		Matrix3f A(size,size);
		Vector3f B(size);
		for (int i=0;i<size;i++) {
			for (int j=0;j<size;j++) {
				A(i,j) = sqrt(c + pow(InitialPoints[i].distanceEuclidienne(InitialPoints[j]),2));
			}
			B(i) = InitialPoints[i].value[k];
		}
		Matrix3f res = A.colPivHouseholderQr().solve(B);
		for (int i=0;i<size;i++) {
			coeff_i.push_back(res(i));
		}
		coeffHardy.push_back(coeff_i);
	}	

}

float map::hardy(Point &P, unsigned int i) {
    // Hardy inverse multiquadrics
    float c = 1;
    float res = 0;
    std::vector<Point>::iterator it = this->InitialPoints.begin();
	std::vector<float>::iterator it2 = this->coeffHardy[i].begin();
    while (it != this->InitialPoints.end() && it2 != this->coeffHardy[i].end()) {
        float dist = (*it).distanceEuclidienne(P);
        float value = (*it).getValue(i);
		if (value != -1) {
	        res += (*it2)*sqrt(dist*dist + c);
		}
		it++;
		it2++;
    }
	P.value.push_back(res);
    return res; }
map::~map()
{
    //dtor
}
