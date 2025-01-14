//Importation des classes en fichier .h
#ifndef UNITTEST_H
#define UNITTEST_H

//Importation des libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "grid.h"

using namespace std;

// Classe pour effectuer les tests unitaires
class UnitTest {
public:
    static void runTest(const string& fileName) {
        // Lire le fichier de test
        ifstream file(fileName);
        if (!file.is_open()) { //Si le fichier n'est pas ouvert
            cerr << "Unable to open test file: " << fileName << endl;
            return;
        }

        // Lire les dimensions de la grille
        int rows, cols;
        file >> rows >> cols;

        // Lire l'état initial de la grille
        vector<vector<int>> initialState(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> initialState[i][j]; // Lis le fichier pour representer les cellules vivante et morte chacune leurs tours
            }
        }

        // Créer la grille et retransmet l'organisation de la grille initial
        ConsoleGrid grid(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid.getCell(i, j).SetState(initialState[i][j]); // Initialise la grille
            }
        }

        // Lire le nombre d'itérations
        int iterations;
        file >> iterations;

        cout << "Initial state:\n";
        grid.display(); //Affichage avant itérations

        // Effectuer les itérations
        for (int i = 0; i < iterations; ++i) {
            grid.update();
        }

        cout << "Final state after " << iterations << " iteration(s):\n";
        grid.display(); //Affichage après itérations

        // Lire la grille de l'etat final
        vector<vector<int>> expectedState(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> expectedState[i][j];
            }
        }

        // Comparer l'état final apres éxécution avec l'état attendu prévue
        bool passed = true;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid.getCell(i, j).GetState() != (expectedState[i][j])) {       //si false alors :
                    passed = false;
                    cerr << "Error at cell (" << i << ", " << j << "): "            //Quel cellule
                              << "Expected " << expectedState[i][j]                 //Resultat attendu
                              << ", Found " << (grid.getCell(i, j).GetState())      //Resultat obtenu
                              << endl;
                }
            }
        }

        // Afficher le résultat du test
        if (passed) {
            cout << "Test passed: " << fileName << endl;
        } else {
            cerr << "Test failed: " << fileName << endl;
        }
    }
};

#endif