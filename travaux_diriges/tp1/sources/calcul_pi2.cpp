#include <chrono>
#include <random>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <mpi.h>  // Inclure la bibliothèque MPI

// Attention, ne marche qu'en C++ 11 ou supérieur :
double approximate_pi(unsigned long nbSamples, int rank, int nbp)
{
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    myclock::duration d = beginning.time_since_epoch();
    unsigned seed = d.count() + rank;  // Utiliser un seed différent pour chaque processus
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    unsigned long nbDarts = 0;

    unsigned long localSamples = nbSamples / nbp; //on répartit le nombre de point à jeter pour chaque process
    for (unsigned sample = 0; sample < localSamples; ++sample) {
        double x = distribution(generator);
        double y = distribution(generator);
        // Test if the dart is in the unit disk
        if (x * x + y * y <= 1) nbDarts++;
    }

    return nbDarts;
}

int main(int nargs, char* argv[])
{
    // Initialiser MPI
    MPI_Init(&nargs, &argv);

    // Obtenir le nombre de processus et le rang du processus
    int nbp, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nbp);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Création d'un fichier pour ma propre sortie en écriture :
    /*std::stringstream fileName;
    fileName << "Output_MPI_" << std::setfill('0') << std::setw(5) << rank << ".txt";
    std::ofstream output(fileName.str().c_str());*/

    // Début de la mesure du temps
    auto start = std::chrono::high_resolution_clock::now();

    // Nombre total d'échantillons
    unsigned long nbSamples = 1000000;  // Exemple de nombre d'échantillons

    // Appeler la fonction pour approximer pi
    unsigned long localDarts = approximate_pi(nbSamples, rank, nbp);

    // Réduire les résultats de tous les processus
    unsigned long totalDarts;
    MPI_Reduce(&localDarts, &totalDarts, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculer l'approximation de pi
    double pi_approx = 0.0;
    if (rank == 0) {
        double ratio = double(totalDarts) / double(nbSamples);
        pi_approx = 4 * ratio;
        std::cout << "Approximation de Pi : " << pi_approx << std::endl;
    }

    // Fin de la mesure du temps
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Afficher le temps de calcul
    if (rank == 0) {
        std::cout << "Temps de calcul : " << elapsed.count() << " secondes" << std::endl;
    }

    output.close();
    MPI_Finalize();
    return EXIT_SUCCESS;
}
