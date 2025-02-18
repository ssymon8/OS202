# include <chrono>
# include <random>
# include <cstdlib>
# include <sstream>
# include <string>
# include <fstream>
# include <iostream>
# include <iomanip>
# include <mpi.h>


int main( int nargs, char* argv[] )
{
	MPI_Init( &nargs, &argv );
	MPI_Comm globComm;
	MPI_Comm_dup(MPI_COMM_WORLD, &globComm);
	int nbp;
	MPI_Comm_size(globComm, &nbp);
	int rank;
	MPI_Comm_rank(globComm, &rank);

    int jeton=0;
    int tag=123;
    MPI_Status status;

    if(rank==0){
        MPI_Send(&jeton, 1, MPI_INT, rank+1,tag, globComm);
        MPI_Recv(&jeton, 1, MPI_INT, nbp-1, tag, globComm,&status);
    }
    else{
        MPI_Recv(&jeton, 1, MPI_INT, nbp-1, tag, globComm,&status);
        jeton++;
        MPI_Send(&jeton, 1, MPI_INT, (rank+1)%nbp, tag, globComm);        
    }

	std::cout<< "je suis le rank"<<rank<<"et ma valeur est"<< jeton<<std::endl;



	output.close();
	// A la fin du programme, on doit synchroniser une dernière fois tous les processus
	// afin qu'aucun processus ne se termine pendant que d'autres processus continue à
	// tourner. Si on oublie cet instruction, on aura une plantage assuré des processus
	// qui ne seront pas encore terminés.
	MPI_Finalize();
	return EXIT_SUCCESS;
}