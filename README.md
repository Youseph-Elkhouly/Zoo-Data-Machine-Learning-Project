# Zoo-Data-Machine-Learning-Project
Full Project Explanation:

This project consists of multiple C files aimed at reading animal data from a file, performing data analysis, and using machine learning concepts to classify new animal samples based on features.
Key Files:

    elkhoulyYousephA1Main.c: This is the main entry point for the program, containing the logic for user interaction and the menu system.
    elkhoulyYousephA1.c: This file contains helper functions, such as reading from files and calculating distances.

Detailed Breakdown:
1. Main Program (elkhoulyYousephA1Main.c):

This file handles the overall flow of the program. Key features include:

    Data Loading:
        The program immediately tries to load animal data from a file called a1Data.txt. It reads this data into a structure array called dataZoo, where each element contains an animal's name, features, and class label.
        If the file cannot be opened, the program exits.

    Menu-Driven Interface:
        After loading the data, the user is presented with a menu that offers several operations:
            Reload the data from the file.
            Generate statistics for a specific feature.
            Classify a new sample.
            Calculate different types of distances (Euclidean, Hamming, Jaccard).
            Find the nearest K neighbors for a sample (K-Nearest Neighbors algorithm).
            Predict the class of a sample.
            Find accuracy based on certain test data.
            Exit the program.

    Switch Case Handling:
        Based on the user's choice, different functions are invoked. For example:
            Generate Statistics: This could involve calculating the mean or mode for a specific feature across all animals.
            Distance Calculations: These options calculate the distance between two feature vectors (animals).
            K-Nearest Neighbors (KNN): This uses the feature distances to find the closest animals to a new sample and predict its class.

2. Helper Functions (elkhoulyYousephA1.c):

This file contains the functions that support the main program’s functionality.

    readFromFile:
        This function reads data from a1Data.txt, where each line represents an animal’s name, a set of 16 features, and a class label.
        The file is parsed line by line, and the data is stored in the dataZoo array, which is of type struct Animal.
        If the file does not exist or there’s an error opening it, the function returns -1.

    Distance Functions:
        The project includes several functions to compute distances between animals' feature vectors:
            Euclidean Distance: Computes the straight-line distance between two feature vectors.
            Hamming Distance: Counts the number of positions where the features differ.
            Jaccard Similarity: Measures the similarity between two sets of features.

    K-Nearest Neighbors (KNN):
        This part of the program likely uses a KNN algorithm to find the closest animals to a new input sample based on their feature vectors and classify the new animal.

3. File Structure (a1Data.txt):

    The file is expected to contain 100 lines, each representing an animal.
    A typical line contains:

animalName feature1 feature2 ... feature16 classLabel

Example:

    aardvark 1 0 0 1 0 0 1 1 1 1 0 0 4 0 0 1 1

        animalName: The name of the animal.
        features: A set of 16 binary or numerical values representing different characteristics of the animal.
        classLabel: An integer representing the class this animal belongs to.

Key Concepts Used in the Program:

    File I/O:
        The program reads from a file using standard C file handling (fopen, fgets, etc.).
        The data is parsed and stored in a structured format.

    Structures in C:
        The program defines a struct Animal that stores the name, features, and class of each animal.

    Distance Metrics:
        The project involves calculating various types of distances between feature vectors, which are essential in machine learning for classification.

    K-Nearest Neighbors (KNN):
        KNN is a simple machine learning algorithm that classifies new samples based on the classes of their nearest neighbors in the feature space.

Example Workflow:

    The user starts the program, which loads the data from a1Data.txt.
    The user is presented with a menu, allowing them to choose various options like calculating statistics, classifying a new sample, or finding the nearest neighbors using KNN.
    The program processes the user input, invokes the appropriate function, and displays the result.
