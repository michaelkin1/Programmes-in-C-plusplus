#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
using namespace std;

const int NUMBER_OF_LETTERS = 26; // A-Z
const int NUMBER_OF_LANGUAGES = 4; // Number of languages for comparison

// Global variable to store the absolute path to the files
string FILE_PATH = "Path/to/text/files"; // Specify the path to the folder containing the text files you want to read

const double LANGUAGE_PROFILE[NUMBER_OF_LANGUAGES][NUMBER_OF_LETTERS] =
{
    {8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, 7.39, 0.12, 0.81, 3.76, 2.85, 6.71, 7.79, 1.54, 0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19, 1.89, 0.03}, // English
    {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, 7.08, 0.38, 0.04, 5.51, 2.82, 8.11, 5.19, 2.78, 1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54, 0.30, 0.15}, // French
    {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, 3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77, 0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05, 0.45, 0.00}, // Swedish
    {5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, 8.63, 0.19, 1.14, 3.68, 3.12, 10.64, 1.74, 0.42, 0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01, 0.69, 1.24}  // German
};

class Text {
private:
    // Initialize variables
    string text;                // Input text
    int absHistogram[NUMBER_OF_LETTERS]; // Absolute frequencies
    double relHistogram[NUMBER_OF_LETTERS]; // Relative frequencies
    int numLetters;             // Total number of letters

public:
    Text() : text(""), numLetters(0) {
        for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
            absHistogram[i] = 0;
            relHistogram[i] = 0.0;
        }
    }

    void setText(const string &newText) {
        text = newText;
    }

    bool calculateAbsoluteHistogram() {
        // Reset histogram and count letters
        for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
            absHistogram[i] = 0;
        }
        numLetters = 0;

        for (char ch : text) {
            if (isalpha(ch)) {
                ch = toupper(ch); // Convert to uppercase
                absHistogram[ch - 'A']++; // Update histogram
                numLetters++;
            }
        }
        return numLetters > 0;
    }

    // Convert absolute histogram to relative (percentage)
    void absToRel() {
        if (numLetters > 0) {
            for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
                relHistogram[i] = (100.0 * absHistogram[i]) / numLetters;
            }
        }
    }

    void plotRelativeHistogram() const {
        // Plot the relative histogram
        cout << "Letter distribution:" << endl;
        for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
            cout << char('A' + i) << " ";
            int stars = static_cast<int>(relHistogram[i] / 0.5);
            for (int j = 0; j < stars; ++j) {
                cout << "*";
            }
            cout << endl;
        }
    }

    void calculateHistogram() {
        if (calculateAbsoluteHistogram()) {
            absToRel();
        }
    }

    // Return the most likely language based on the squared sum
    string interpret() {
        double squaredSums[NUMBER_OF_LANGUAGES] = {0.0, 0.0, 0.0, 0.0};
        for (int i = 0; i < NUMBER_OF_LANGUAGES; ++i) {
            for (int j = 0; j < NUMBER_OF_LETTERS; ++j) {
                squaredSums[i] += pow(relHistogram[j] - LANGUAGE_PROFILE[i][j], 2);
            }
        }

        int minIndex = 0;
        for (int i = 1; i < NUMBER_OF_LANGUAGES; ++i) {
            if (squaredSums[i] < squaredSums[minIndex]) {
                minIndex = i;
            }
        }

        string languages[NUMBER_OF_LANGUAGES] = {"English", "French", "Swedish", "German"};

        // Print the squared sums and the most likely language
        cout << "Total number of letters: " << numLetters << endl;
        cout << "English has squared sum = " << squaredSums[0] << endl;
        cout << "French has squared sum = " << squaredSums[1] << endl;
        cout << "Swedish has squared sum = " << squaredSums[2] << endl;
        cout << "German has squared sum = " << squaredSums[3] << endl;
        cout << "It is most likely that the language is " << languages[minIndex] << "." << endl;

        return languages[minIndex];
    }
};

string name_of_file() {
    // Read the filename from user input
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    return FILE_PATH + filename; // Return the full path to the file
}

string loadFile(string filePath) {
    // Try to open the file specified by the path entered earlier
    ifstream file(filePath);
    if (!file) {
        // If the file is not found, try adding ".txt"
        string filename = filePath.substr(FILE_PATH.length()); // Extract only the filename
        filePath += ".txt";
        file.open(filePath);
        if (!file) {
            // If the file is still not found, exit with an error message
            cout << "No file found with the name " << filename << ".txt" << endl;
            exit(EXIT_FAILURE); // Exit the program if the file is not found
        }
    }

    // Read the file's contents and return it as a string
    string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    return content;
}

int main() {
    // Declare variables
    Text myText; // Create an object of type Text

    // Load and process the file
    string filePath = name_of_file();
    string fileContent = loadFile(filePath);

    // Send the fileContent string to the myText object
    myText.setText(fileContent);

    // Calculate the histogram and interpret the language
    myText.calculateHistogram();
    myText.interpret();
    myText.plotRelativeHistogram();

    return 0;
}
