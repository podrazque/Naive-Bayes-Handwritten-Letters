#ifndef BAYES_H
#define BAYES_H


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <math.h>
#include <iomanip>

using std::vector;
using std::string;
using std::cout;
using std::endl;


class Bayes {
public:
	vector<string> createVector(string file);
	vector<vector<string> > createDigitVector(vector<string> input);
	vector<vector<vector<string> > > createImageLabelVector(vector<string> imageInput, vector<string> labelInput);
	vector<vector<vector<double> > > calculateProbability(vector<vector<vector<string> > > input);

	vector<vector<double> > createProbabilityVector(vector<vector<vector<double> > >, vector<vector<string> >);
	vector<vector<vector<string> > > createImageVector(vector<string> imageInput);
	vector<int>  checkCorrectness(vector<vector<double> > probabilityMatrix, vector<string> testLabels);

	void outputNumbers(string numberString, string fileName);
	void outputModel(string modelString);

	string outputString(vector<vector<vector<double> > > input, double accuracy);
	string outputStringModel(vector<vector<vector<double> > > input);
	double calculatePixel(vector<vector<string> > input, unsigned y, unsigned x);
};

#endif