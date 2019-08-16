#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Bayes.h"


TEST_CASE("Generated sorted digits vector returns correct vector") 
{
    Bayes b;

    const int numberOfDigits = 2, digitHeight = 28;

    vector<string> image_input = b.createVector("trainingimages");
    vector<string> label_input = b.createVector("traininglabels");

    image_input.resize(digitHeight * numberOfDigits);
    label_input.resize(numberOfDigits);

    vector<vector<vector<string> > > actual;

    actual = b.createImageLabelVector(image_input, label_input);

    vector<vector<vector<string> > > expected;
	
    expected.reserve(10);
    for (int i = 0; i < 10; i++){
        expected.push_back(vector<vector<string>>());
    }

    vector<vector<string> > digit_blocks = b.createDigitVector(image_input);
    expected[0].push_back(digit_blocks[1]);
    expected[5].push_back(digit_blocks[0]);
    REQUIRE(expected == actual);
}

TEST_CASE("Splitting a vector into blocks of vectors works as expected")
 {
    Bayes b;
    vector<string> input;
    for (int i = 0; i < 10; i++)
	{
        input.push_back(std::to_string(i));
    }

	vector<vector<string>> expected;

    expected.push_back(vector<string>());

    for (int i = 0; i < 10; i++){
        expected[0].push_back(std::to_string(i));
    }

    REQUIRE(expected == b.createDigitVector(input));
}

TEST_CASE("Reading from a file reads correctly") {
    Bayes b;
    vector<string> ret = b.createVector("read.txt");
    string expected = "you should be reading this boss";
    REQUIRE(expected == ret[0]);
}
