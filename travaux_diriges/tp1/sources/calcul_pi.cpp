#include <chrono>
#include <random>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <omp.h>  // Inclure la bibliothèque OpenMP

// Attention, ne marche qu'en C++ 11 ou supérieur :
double approximate_pi(unsigned long nbSamples)
{
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    myclock::duration d = beginning.time_since_epoch();
    unsigned seed = d.count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    unsigned long nbDarts = 0;

    // Paralléliser la boucle avec OpenMP
    #pragma omp parallel for reduction(+:nbDarts)
    for (unsigned sample = 0; sample < nbSamples; ++sample) {
        double x = distribution(generator);
        double y = distribution(generator);
        // Test if the dart is in the unit disk
        if (x * x + y * y <= 1) nbDarts++;
    }

    // Number of nbDarts throwed in the unit disk
    double ratio = double(nbDarts) / double(nbSamples);
    return 4 * ratio;
}

int main(int nargs, char* argv[])
{
    // Création d'un fichier pour ma propre sortie en écriture :
    /*std::stringstream fileName;
    fileName << "Output_OpenMP.txt";
    std::ofstream output(fileName.str().c_str());*/

    // Début de la mesure du temps
    auto start = std::chrono::high_resolution_clock::now();

    unsigned long nbSamples = 1000000000;  // nombre d'échantillons
    double pi_approx = approximate_pi(nbSamples);
    std::cout << "Approximation de Pi : " << pi_approx << std::endl;

    // Fin de la mesure du temps
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Afficher le temps de calcul
    std::cout << "Temps de calcul : " << elapsed.count() << " secondes" << std::endl;

    output.close();
    return EXIT_SUCCESS;
}
