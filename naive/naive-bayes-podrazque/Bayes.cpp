#include "Bayes.h"

vector<string> Bayes::createVector(string file)
{
	std::ifstream infile(file);
	string line;
	vector<string> returnArray;

	while(getline(infile, line))
	{
		returnArray.push_back(line);
	}
	return returnArray;
}

vector<vector<double> > Bayes::createProbabilityVector(vector<vector<vector<double> > > predictionVector, vector<vector<string> > testVector)
{	
	vector<vector<double> > sumVectorVector;
	vector<double> sumVector;
	for(unsigned i = 0; i < testVector.size(); i++)
	{
		double sumForTest = 0;
		for(unsigned t = 0; t < 10; t++)
		{
			vector<vector<double> > predictionAtLine;
			for(unsigned j = 0; j < 28; j++)
			{
				vector<double> predictionAtPixel;
				for(unsigned k = 0; k < testVector[i][j].size(); k++)
				{
					if(testVector[i][j][k] == '#' || testVector[i][j][k] == '+')
					{
						double decimal = predictionVector[t][j][k];
						sumForTest += ((abs(log(decimal)))) + 0.1;
					}
					else
						sumForTest += 0.1;
				}
			}
			sumVector.push_back(sumForTest);
			sumForTest = 0;
		}
		sumVectorVector.push_back(sumVector);
		sumVector.clear();
	}
	
	return sumVectorVector;
}

vector<int>  Bayes::checkCorrectness(vector<vector<double> > probabilityMatrix, vector<string> testLabels)
{
	vector<int> correctnessVector;
	double one = 0;
	double zero = 0;
	for(unsigned i = 0; i < probabilityMatrix.size(); i++)
	{
		auto correctNumber = testLabels[i];
		int assumedIndex;
		auto min = *min_element(probabilityMatrix[i].begin(), probabilityMatrix[i].end());
		for(unsigned long j = 0; j < probabilityMatrix[i].size(); j++)
		{
			if(probabilityMatrix[i][j] == min)
			{
				assumedIndex = j;
			}
		}

		cout << endl << correctNumber << " -- " << assumedIndex << endl;
		
		if(assumedIndex == stoi(correctNumber))
		{
			one++;
			correctnessVector.push_back(1);
		}
		else
		{
			zero++;
			correctnessVector.push_back(0);
		}
	}
	cout << endl << one / (zero + one) << endl;
	return correctnessVector;
}

// vector that stores the individual digit vectors
vector<vector<string> > Bayes::createDigitVector(vector<string> input)
{
	vector<vector<string> > ret;
    vector<string> * temp = new vector<string>;
    for(unsigned int i = 0; i < input.size(); i++)
	{
        if (i % 28 == 0 && i != 0) 
		{
            ret.push_back(*temp);
            delete temp;
            temp = new vector<string>;
        }
        temp->push_back(input[i]);
    }
    ret.push_back(*temp);
    delete temp;
    return ret;
}


vector<vector<vector<string> > > Bayes::createImageLabelVector(vector<string> imageInput, vector<string> labelInput)
{
    vector<vector<string> > digitVector = createDigitVector(imageInput);
    vector<vector<vector<string> > > sortedVector;
    vector<vector<string> > numbersVector;

    unsigned i = 0;
	auto beginning = digitVector.begin();
	auto end = digitVector.end();

	// when I didn't have this I was getting seg faults, found the solution here - https://stackoverflow.com/questions/35027944/why-am-i-getting-a-segmentation-fault-only-sometimes
	//I do this to put 10 vectors 0-9 in the sorting array, that will allow me to append the "images" to the corresponding index
	sortedVector.reserve(10); 

    for (int i = 0; i < 10; i++)
	 {
        sortedVector.push_back(numbersVector);
    }

    for (auto iter = beginning; iter < end; iter++)
	 {
        int label = stoi(labelInput[i]); //string to int
        sortedVector[label].push_back(*iter);
		i++;
    }
    return sortedVector;
}

double Bayes::calculatePixel(vector<vector<string> > input, unsigned y, unsigned x)
{
	double occurences = 0;
	unsigned sizeOfSample = input.size();
	for(unsigned long it = 0; it < sizeOfSample; it++)
	{
		auto curr = input[it];
		if(curr.size() < y + 1)
		{
			return 0;
		}
		string currLine = curr[y];
		if(currLine.size() < x + 1)
		{
			return 0;
		}
		if(currLine[x] == '#' || currLine[x] == '+')
		{
			occurences++; 
		}
	}
	return (occurences/sizeOfSample);
}

vector<vector<vector<double> > > Bayes::calculateProbability(vector<vector<vector<string> > > input)
{
    vector<vector<vector<double> > > probabilityVector;
	for(unsigned long i = 0; i < 10; i++)
	{
		vector<vector<double> > letterProbabilityVector;
		{
			for(unsigned y = 0; y < 28; y++)
			{
				vector<double> lineProbability;
				for(unsigned x = 0; x < 28; x++)
				{	
					double probabilityReturn = calculatePixel(input[i], y, x);
					lineProbability.push_back(probabilityReturn);
				}
				letterProbabilityVector.push_back(lineProbability);
			}
		}
		probabilityVector.push_back(letterProbabilityVector);
	}
    
    return probabilityVector;
}

void Bayes::outputModel(string modelString)
{
	std::ofstream push;
	push.open("model.txt");
	push << modelString;
}

string Bayes::outputStringModel(vector<vector<vector<double> > > input)
{
	string returnString;
	for(int i = 0; i < 10; i++)
	{	
		for(int y = 0; y < 28; y++)
		{
			for(int x = 0; x < 28; x++)
			{
				auto x_str = std::to_string(input[i][y][x]);
				returnString += x_str;
			}
			returnString += "\n";
		}
	}
	return returnString;
}

void Bayes::outputNumbers(string numberString, string fileName)
{
	std::ofstream push;
	push.open(fileName);
	push << numberString;
}

string Bayes::outputString(vector<vector<vector<double> > > input, double accuracy)
{
	string returnString;
	for(int i = 0; i < 10; i++)
	{
		for(int y = 0; y < 28; y++)
		{
			for(int x = 0; x < 28; x++)
			{
				if(input[i][y][x] > accuracy)
				{
					returnString += "X";
				}
				else
					returnString += "_";
			}
			returnString += "\n";
		}
	}
	return returnString;
}
