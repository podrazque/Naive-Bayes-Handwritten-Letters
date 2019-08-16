#include <iostream>
#include <string>
#include "Bayes.h"
#include <string>
#include <fstream>


using namespace std;

int main()
{
	Bayes bayes;
	vector<vector<vector<string> > > sortedArray = bayes.createImageLabelVector(bayes.createVector("trainingimages"), bayes.createVector("traininglabels"));
	vector<vector<vector<double> > > probabilities = bayes.calculateProbability(sortedArray);
	

	

	vector<vector<string> > imagevec = bayes.createDigitVector(bayes.createVector("testimages.txt"));
	
	vector<vector<double> > matrix = bayes.createProbabilityVector(probabilities, imagevec);

	vector<int> correct = bayes.checkCorrectness(matrix, bayes.createVector("traininglabels"));

	for(unsigned long i = 0; i < correct.size(); i++)
	{
		cout << " " << correct[i];
	}
	
	string output = bayes.outputString(probabilities, 0.4);
	string modelOutput = bayes.outputStringModel(probabilities);
	bayes.outputNumbers(output, "numbers.txt");
	bayes.outputModel(modelOutput);
	
	return 0;
}