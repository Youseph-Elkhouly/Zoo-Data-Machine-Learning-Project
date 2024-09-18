#include "givenA1.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    struct Animal dataZoo[NUM_SAMPLES]; //declaring the datazoo array
    struct Animal testData[NUM_TEST_DATA];
    int choice;
    int k = 5; // Set a default value for k, or you could prompt the user for it.
	//Example vectors:
	int vector1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int vector2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};


    // Attempt to load the data immediately upon program start.
    printf("Loading data...\n");
	int loadSuccess = readFromFile("a1Data.txt", dataZoo);
   	if (loadSuccess != 1) {
        printf("Failed to load data. Exiting program.\n");

	    return -1;
	}
    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1: Reload Data\n");
        printf("2: Generate Statistics for Feature X\n");
        printf("3: Classify a New Sample\n");
        printf("4: Euclidean Distance\n");
        printf("5: Hamming Distance\n");
        printf("6: Jaccard Similarity\n");
        printf("7: Find Nearest K Neighbors\n");
        printf("8: Predict Class\n");
        printf("9: Find Accuracy\n");
        printf("10: Exit Program\n");

        // Get user choice
        printf("\nEnter your choice (1-10): ");
        scanf("%d", &choice);

        // Variables used in switch cases
        int featureIndex;
        float mean;
        int mode;
        int kNearestNeighbors[NUM_SAMPLES]; // Used for task 7s
		int newSample[NUM_FEATURES]; //declare the newSample array

        // Validate choice and perform the chosen task
  switch (choice) {
            case 1:
            printf("Reloading data...\n");
            if (readFromFile("a1Data.txt", dataZoo) != 1) {
                printf("Failed to reload data.\n");
            } else {
                printf("Data reloaded successfully. Here's the loaded data:\n");
                    for (int i = 0; i < NUM_SAMPLES; i++) {
                        printf("Animal Name: %s\nFeatures: ", dataZoo[i].animalName);
                        for (int j = 0; j < NUM_FEATURES; j++) {
                            printf("%d ", dataZoo[i].features[j]);
                        }
                        printf("\nClass Label: %d\n\n", dataZoo[i].classLabel);
                    }
             }
            break;
       		case 2:
   				 printf("Enter feature index (1-16) for statistics: ");
   				 scanf("%d", &featureIndex);
   				 if (featureIndex < 1 || featureIndex > NUM_FEATURES) {
       			 printf("Error: Invalid feature number.\n");
       			 break;
   		        }
  			 int statSuccess = generateStatisticsFeatureX(dataZoo, featureIndex, &mean, &mode);
   			 if (statSuccess != -1) {
       			 printf("Mean of feature %d: %.2f\n", featureIndex, mean);
      			 printf("Mode of feature %d: %d\n", featureIndex, mode);
   			 } else {
       			 printf("Error generating statistics for feature %d.\n", featureIndex);
   			 }
            break;

       		 case 3:
           		 classDistribution(dataZoo);
           	  break;

    	case 4: {
   		 // Assuming newSample is defined with NUM_FEATURES and initialized with some values
   		 int newSample[NUM_FEATURES] = {/* values representing a new animal's features */};

		    printf("Euclidean Distances from New Sample to Each DataZoo Sample:\n");
   			for (int i = 0; i < NUM_SAMPLES; i++) {
       		float distance = euclideanDistance(newSample, dataZoo[i].features);
       		printf("Distance to Sample %d: %f\n", i + 1, distance);
   		 }
	}
   		 break;
         case 5: {

            // Calculate Hamming distance
            int distance = hammingDistance(vector1, vector2);
            printf("Hamming Distance between the two vectors is: %d\n", distance);
            break;
        }

        case 6:
            // Case 6:
				int vector1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
				int vector2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};

				float similarity = jaccardSimilarity(vector1, vector2);

				printf("Jaccard Similarity between the two vectors: %f\n", similarity);
				break;


        case 7:{
    printf("Enter features for the new sample (0 or 1 for binary features, appropriate integers for others):\n");
    for (int i = 0; i < NUM_FEATURES; i++) {
        printf("Feature %d: ", i + 1);
        while (scanf("%d", &newSample[i]) != 1) {
            // Clear the input buffer to prevent infinite loops
            while (getchar() != '\n');
            printf("Invalid input. Please enter an integer for feature %d: ", i + 1);
        }
    }

    // Allow user to choose the distance function
    int distanceFunction;
    printf("\nChoose the distance function:\n");
    printf("1: Euclidean\n2: Hamming\n3: Jaccard\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &distanceFunction);
    while (distanceFunction < 1 || distanceFunction > 3) {
        printf("Invalid choice. Please select 1 (Euclidean), 2 (Hamming), or 3 (Jaccard): ");
        scanf("%d", &distanceFunction);
    }

    // Ensure 'k' is within a reasonable range
    if (k < 1 || k > NUM_SAMPLES) {
        printf("The value of 'k' is out of bounds. Resetting to default (5).\n");
        k = 5; // Reset k to a default value or prompt for a new value
    }

    findKNearestNeighbors(dataZoo, newSample, k, distanceFunction, kNearestNeighbors);
    printf("\nIndices of the %d nearest neighbors based on ", k);
    switch (distanceFunction) {
        case 1: printf("Euclidean distance:\n"); break;
        case 2: printf("Hamming distance:\n"); break;
        case 3: printf("Jaccard similarity:\n"); break;
    }

    for (int i = 0; i < k; i++) {
        if (kNearestNeighbors[i] != -1) {
            printf("%d ", kNearestNeighbors[i]);
        }
    }
    printf("\nNote: Indices are 0-based and correspond to positions within the dataset.\n");
    break;
}


        case 8:
			// Example new sample features (should be replaced with actual user input or test data)
   			 int newSample[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
   			 int predictedClass = predictClass(dataZoo, kNearestNeighbors, newSample, k);
   			 printf("The predicted class for the new sample is: %d\n", predictedClass);
  			 break;

		case 9: {
    		FILE *file; // Declare the file pointer
    		char line[1024]; // Buffer for reading lines from the CSV file
    		int i; // Counter variable for iterating through the test data entries

    // Attempt to open the testData.csv file for reading
    		file = fopen("testData.csv", "r");
    		if (!file) {
        		printf("Error opening test data file\n");
    		} else {
        		i = 0;
        		while (fgets(line, sizeof(line), file) && i < NUM_TEST_DATA) {
            	// Assuming the structure of each line in testData.csv is known and consistent
            		char animalName[MAX_LENGTH_ANIMAL_NAME];
            		int features[NUM_FEATURES];
            		int classLabel;

            	// Parse the CSV line into the structure expected by your program
            		int parsedItems = sscanf(line, "%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                                     animalName,
                                     &features[0], &features[1], &features[2], &features[3],
                                     &features[4], &features[5], &features[6], &features[7],
                                     &features[8], &features[9], &features[10], &features[11],
                                     &features[12], &features[13], &features[14], &features[15],
                                     &classLabel);
            	if (parsedItems == 18) { // Ensure all items were parsed correctly
                	// Copy parsed data into the testData array at index i
                	strncpy(testData[i].animalName, animalName, MAX_LENGTH_ANIMAL_NAME);
                	testData[i].animalName[MAX_LENGTH_ANIMAL_NAME - 1] = '\0'; // Null-terminate
                	memcpy(testData[i].features, features, sizeof(features));
                	testData[i].classLabel = classLabel;
                	i++;
            	} else {
                	printf("Warning: Incorrectly formatted line.\n");
            	}
        	}
        	fclose(file); // Close the file after reading

        	// Check if the expected number of test data entries were loaded
        		if (i != NUM_TEST_DATA) {
            		printf("Warning: Less test data loaded than expected. Loaded %d entries.\n", i);
        		} else {
            		printf("Test data reloaded successfully.\n");

            	// Calculate and display the accuracy of the k-NN algorithm using the loaded test data
            		float accuracy = findAccuracy(dataZoo, testData, k); // Assumes k is defined and testData is loaded
            		printf("Accuracy of k-NN on test data: %.2f%%\n", accuracy);
        		}
    		}
    		break;
			}

        	case 10:
            	printf("Exiting program.\n");
            	break;

        	default:
         	   printf("Invalid choice. Please enter a number between 1 and 10.\n");
    	}
	} while (choice != 10);

    return 0;
}
