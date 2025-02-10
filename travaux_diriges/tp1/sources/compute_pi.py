from mpi4py import MPI
import time
import numpy as np

# Initialiser MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Nombre total d'échantillons
nb_samples = 40_000_000

local_nb_samples = nb_samples // size #on attribue à chaque process un nombre de smaples à traiter

# Mesurer le temps de début
beg = time.time()

# Tirage des points (x,y) tirés dans un carré [-1;1] x [-1; 1]
np.random.seed(rank)  # Utiliser un seed différent pour chaque processus
x = 2. * np.random.random_sample((local_nb_samples,)) - 1.
y = 2. * np.random.random_sample((local_nb_samples,)) - 1.

# Création masque pour les points dans le cercle unité
filtre = np.array(x * x + y * y < 1.)

# Compte le nombre de points dans le cercle unité
local_sum = np.add.reduce(filtre, 0)

# Réduire les résultats de tous les processus
total_sum = comm.reduce(local_sum, op=MPI.SUM, root=0)

# Calculer l'approximation de pi
if rank == 0:
    approx_pi = 4. * total_sum / nb_samples
    end = time.time()
    print(f"Temps pour calculer pi : {end - beg} secondes")
    print(f"Pi vaut environ {approx_pi}")

# Finaliser MPI
MPI.Finalize()
