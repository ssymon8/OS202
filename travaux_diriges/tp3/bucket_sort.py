from mpi4py import MPI
import numpy as np 
import random as rand

# MPI initialization 
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
nbp = comm.Get_size()

MAX = 1000
ARRAY_SIZE=MAX//nbp+1

if rank==0: #on crée la liste initiale
    liste=np.array()
    for i in range(100):
        a=rand.randint(0,1000)
        np.append(liste,a)
    print("Liste initiale : ", liste)
    
#on broadcast à tous les process la liste initiale
liste = comm.bcast(liste, root=0)

#chaque process crée un array propre et on va y placer les nombres...
array = np.array([i for i in liste if rank * ARRAY_SIZE <= i < (rank + 1) * ARRAY_SIZE])

#puis trie cet array
array.sort()

# on regarde la taille des listes de chaque processus
sendcounts = np.array(comm.gather(len(array), root=0))

# si je suis le processus maître, je réceptionne les arrays triés
if rank == 0:
    buffer_recep = np.empty(sum(sendcounts), dtype=int)

# on récupère les arrays triés
comm.Gatherv(array, (buffer_recep, sendcounts), root=0)

# si je suis le processus maître, je concatène les arrays triés
if rank == 0:
    liste_triee = buffer_recep
    print("Liste triée :", liste_triee)

MPI.Finalize()







