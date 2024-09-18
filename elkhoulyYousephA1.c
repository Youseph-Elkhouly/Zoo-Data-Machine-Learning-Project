#include <stdio.h>
#include "givenA1.h"
#include <math.h> // this is a the standard C library for math functions
 // this is a custom header file that contains the definition of struct IndexedDistance
#include <stdlib.h>
#include <string.h>
#include <time.h>



/* Task 1: 
This function must read the information from a text file called a1Data.txt and store them
in the array called dataZoo, where each element of the array is of type struct Animal.
There are 100 lines in the given text file, where each line stores information of a single
animal. 

For example, content of line 1 of a1Data.txt will be assigned to dataZoo [0] as
the following:

animalName = aardvark
features = 1 0 0 1 0 0 1 1 1 1 0 0 4 0 0 1
classLabel = 1

The above implies that the animal name read is aardvark, feature number 1 is 1, feature
2 is 0, ..., feature number 16 is 1, and the class label of this animal is 1. The function
will either return 1 (to indicate successful operation) or -1 to represent abnormal exit.
For example, if the given file does not exist, the function returns -1. */
    int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]) {
        FILE *fp;
        fp = fopen("a1Data.txt", "r");
        if (fp == NULL) {
            printf("Error opening file\n");
            return -1;
        }
        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            char *token = strtok(line, " ");
            strncpy(dataZoo[i].animalName, token, MAX_LENGTH_ANIMAL_NAME-1);
			dataZoo[i].animalName[MAX_LENGTH_ANIMAL_NAME - 1] = '\0';   //ensuring NULL Termination
            int j = 0;
            while (token != NULL) {
                token = strtok(NULL, " ");
                if (j < NUM_FEATURES) {
                    dataZoo[i].features[j] = atoi(token);
                } else if (j == NUM_FEATURES){
                    dataZoo[i].classLabel = atoi(token);
                }
                j++;
            }
            i++;
        }
        fclose(fp);
        return 1;
    }


/* Task 2 
    given the array dataZoo populated with data read in Task 1, and a feature number this, fucntion generates 
    the mean and mode of that feature and outputs it to the calling function. it returns -1 if the feature number
    is incorrect. NOte that the valid features are numbered from 

*/


	int generateStatisticsFeatureX(struct Animal dataZoo[NUM_SAMPLES], int whichFeature, float *mean, int *mode) {
    	if (whichFeature < 1 || whichFeature > 16) {
        	return -1; // Invalid feature index
    	}

    	// Adjust for 0-based indexing
    	whichFeature--;

    	int featureValues[9] = {0}; // Max possible values for 'legs' feature
    	int total = 0;

    	// Calculate sum and count occurrences of each feature value
    	for (int i = 0; i < NUM_SAMPLES; i++) {
        	int value = dataZoo[i].features[whichFeature];
        	total += value;
        	featureValues[value]++;
    	}

    	// Calculate mean
    	*mean = (float)total / NUM_SAMPLES;

    	// Find mode
    	int maxCount = 0;
    	for (int i = 0; i < sizeof(featureValues) / sizeof(featureValues[0]); i++) {
        	if (featureValues[i] > maxCount) {
            	maxCount = featureValues[i];
            	*mode = i; // Adjust for 0-based indexing of the values
        	}
    	}

    	return 0;
	}




/*
Task 3: this function takes the zoo dataset and displays its class distribution as a histrogram
as shown below: NOte that member name classLabel in struct Animal stores the class label for each 
sample or row. There are 40 rows with classLabel as 1 , 29 rows with classLabel as 2, and so on.

*/
    void classDistribution(struct Animal dataZoo[NUM_SAMPLES]) {
    	int classCounts[NUM_CLASSES] = {0};
    	int maxCount = 0;

 	    // Count occurrences of each class
    	for (int i = 0; i < NUM_SAMPLES; i++) {
        	int classLabel = dataZoo[i].classLabel;
        	if (classLabel >= 1 && classLabel <= NUM_CLASSES) {
            	classCounts[classLabel - 1]++;
            	if (classCounts[classLabel - 1] > maxCount) {
                	maxCount = classCounts[classLabel - 1];
            	}
        	}
    	}

	    // Print the counts at the top
    	for (int i = 0; i < NUM_CLASSES; i++) {
        	printf("(%d) ", classCounts[i]);
    	}
    	printf("\n");

    	// Print the histogram vertically
    	for (int count = maxCount; count > 0; count--) {
        	for (int i = 0; i < NUM_CLASSES; i++) {
            	if (classCounts[i] >= count) {
                	printf("*  ");
            	} else {
                	printf("   ");
            	}
        	}
        	printf("\n");
    	}

	    // Print the class labels at the bottom
    	for (int i = 0; i < NUM_CLASSES; i++) {
        	printf("%d  ", i + 1);
    	}
    	printf("\n");
	}

/*
Task 4: This function computes and returns the Euclidean distance between 2 arrays, each with 16 features.
Euclidean distance between between two arrays v1 and v2 both of the same size (say N) this is computed as.
euclidean distance (V1, V2) = square root of the summation of (v1[i] - v2[i])^2 for i = 0 to N-1
*/
    float euclideanDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]){

        float sum = 0;
        for (int i =0; i < NUM_FEATURES; i++){
            sum += pow(vector1[i] - vector2[i], 2);
        }
        return sqrt(sum);

    }

/*
Task 5: This function computes and returns the Hamming distance between 2 arrays, each with 16 features.
Hamming distance between between two arrays v1 and v2 both of the same size (say N) this is computed as.
*/
    	int hammingDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {
    	int distance = 0;
    	for (int i = 0; i < NUM_FEATURES; i++) {
        	if (vector1[i] != vector2[i]) {
            	distance++;
       	    }
    	}
    	return distance;
	}


/*
task 6:

Assume that vector1 and 2 have 16 features or columns vector1 = 1110101110000111 and vector2 = 1001001111004001

jaccard similarity = number of 1-1 matches in v1 and v2 / number of features in v1 or v2 -number of 0-0 matches  = 5/13 = 0.38

Note that the 1-1 matches in vector1 and vector2 are shown in red in the given
example; whereas 0-0 matches in vector1 and vector2 are shown in green. Both vector1
and vector2 have 16 features

*/

// Function to compute Jaccard


// Function to compute Jaccard Similarity
	float jaccardSimilarity (int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]){

    	int matches = 0;
    	int total = NUM_FEATURES;

	    for(int i =0; i <NUM_FEATURES; i++){

    	    if (vector1[i] == 1 && vector2[i] == 1){
        	    matches++;
        	}
        	if (vector1[i] == 0  &&  vector2[i] == 0){
            	total--;
        	}
    	}
    	return (float)matches/total;
	}



/*
Task 7: This function takes 4 inputs, i.e., (1) the given dataset (100 * (animal name, 16 features,
a class label)), (2) features of a new data sample (note that each data has 16 features),
(3) value of k that signifies the total number of neighbors to find, (4) index of the desired
distance function (note that this index can 1, 2 or 3, where 1 represents Euclidean
distance, 2 represents Hamming distance, and 3 represents Jaccard’s similarity.
It outputs an array called kNearestNeighbors that stores the indices of the k nearest
neighbors of newSample using the given whichDistanceFunction. Note that although
the size of kNearestNeighbors is defined as NUM_SAMPLES, only k of its elements
are used to store indices of its k neighbors.
Steps of k-nearest-neighbors algorithm of ML are described below:
1. for i = 1 to NUM_SAMPLES:
find the distance of the new data sample with the ith data sample in zoo dataset.
2. Sort all these distances in decreasing order. Note that you need the indices of the
data samples, so you must maintain them.
3. Save the indices associated with the first K distances in the sorted list in
kNearestNeighbors

*/

/*
Helper function: to define the comparison function for qsort


*/
	int compareIndexedDistance(const void *a, const void *b){

	    float distA = ((IndexedDistance *)a)-> distance; 
    	float distB = ((IndexedDistance *)b)-> distance;
    	return (distA > distB)-(distA < distB);


	}

	void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES]) {
    	IndexedDistance distances[NUM_SAMPLES];

	    // Calculate distances from newSample to all samples in dataZoo
    	for (int i = 0; i < NUM_SAMPLES; i++) {
        	distances[i].index = i; // Correctly set the index here
        	// Initialize distance based on the chosen distance function
        	switch (whichDistanceFunction) {
            	case 1: // Euclidean distance
                	distances[i].distance = euclideanDistance(newSample, dataZoo[i].features);
               		break;
            	case 2: // Hamming distance
                	distances[i].distance = (float)hammingDistance(newSample, dataZoo[i].features);
                	break;
            	case 3: // Jaccard similarity
                	distances[i].distance = 1 - jaccardSimilarity(newSample, dataZoo[i].features); // Adjust for similarity to work with sorting
                	break;
            	default:
                	printf("Invalid distance function.\n");
                	return;
        	}
        	printf("Distance between test sample and dataZoo[%d]: %f\n", i, distances[i].distance);
    	}

    	// Sort distances in increasing order
    	qsort(distances, NUM_SAMPLES, sizeof(IndexedDistance), compareIndexedDistance);

	    // Save the indices of the first k distances
    	for (int i = 0; i < k; i++) {
        	kNearestNeighbors[i] = distances[i].index;
    	}

    	// Optionally, mark unused elements if k < NUM_SAMPLES
    	for (int i = k; i < NUM_SAMPLES; i++) {
        	kNearestNeighbors[i] = -1; // Indicate unused slots if necessary
    	}
	}



/*

task 8:
Given the k-nearest neighbors of a new data sample, this function predicts its class and
returns it. To do this, it assigns the most frequent class among the K neighbors as the
predicted class for the input data sample. Note that the new sample (parameter 3) has
NUM_FEATURE values, one for each feature.
Example: Assume k = 5,
newSample = 1 1 1 0 1 0 1 1 1 0 0 0 0 1 1 1
And k neighbors for the new sample (indices of the k neighbors) are 8, 12, 24, 39,
55
Then using the class label given in the dataZoo dataset, it finds the most frequent class
label.
Class label of 8 = 4
Class label of 12 = 2
Class label of 24 = 2
Class label of 39 = 6
Class label of 56 = 2
The most frequent class label among the above is 2, therefore this function predicts the
class for the given new data sample as 

*/

// Task 8: Implement the predictClass function
	int predictClass(struct Animal dataZoo[NUM_SAMPLES], int neighborsForNewSample[NUM_SAMPLES], int newSample[NUM_FEATURES], int k) {
    	int classCounts[NUM_CLASSES] = {0}; // Array to store counts of each class
    	int maxClassCount = 0; // Count of the most frequent class
    	int predictedClass = -1; // Initialize predicted class as -1 (invalid)

    	// Count the occurrences of each class among the neighbors
    	for (int i = 0; i < k; i++) {
        	int neighborIndex = neighborsForNewSample[i];
        	int neighborClass = dataZoo[neighborIndex].classLabel;
        	classCounts[neighborClass]++;
        	if (classCounts[neighborClass] > maxClassCount) {
            	maxClassCount = classCounts[neighborClass];
            	predictedClass = neighborClass;
        	}
    	}

    	return predictedClass;
	}


/*



t is common in the ML world to evaluate the performance of the algorithm using
performance measures such as accuracy. Accuracy is measured as:
𝑎𝑐𝑐𝑢𝑟𝑎𝑐𝑦 = 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑐𝑜𝑟𝑟𝑒𝑐𝑡 𝑝𝑟𝑒𝑑𝑖𝑐𝑡𝑖𝑜𝑛𝑠
𝑡𝑜𝑡𝑎𝑙 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑝𝑟𝑒𝑑𝑖𝑐𝑡𝑖𝑜𝑛𝑠
For example, if the total number of samples (and therefore the total number of
predictions) is 10, and the number of predictions correctly made by the ML algorithm is
6, then the accuracy will be calculated as 60%.
For this assignment, a small test dataset (with NUM_TEST_DATA samples) is given in
a file called testData.csv. Your function must find (predict) the class of each data given
in the testData file and use them to compute the accuracy of the k-nearest-neighbor ML
algorithm used.
*/

// Task 9: Implement the findAccuracy function
	float findAccuracy(struct Animal dataZoo[NUM_SAMPLES], struct Animal testData[NUM_TEST_DATA], int k) {
    int correctPredictions = 0; // Count of correct predictions

    	for (int i = 0; i < NUM_TEST_DATA; i++) {
        	// Find the k-nearest neighbors for each test sample
        	int neighborsForTestSample[NUM_SAMPLES];
        	findKNearestNeighbors(dataZoo, testData[i].features, k, 1, neighborsForTestSample);

        	// Predict the class for the test sample using the k-nearest neighbors
        	int predictedClass = predictClass(dataZoo, neighborsForTestSample, testData[i].features, k);

       	 	// Check if the prediction is correct
        	if (predictedClass == testData[i].classLabel) {
            	correctPredictions++;
        	}
    	}

    // Calculate accuracy as a percentage
    	float accuracy = (float)correctPredictions / NUM_TEST_DATA * 100.0;
    	return accuracy;
	}

