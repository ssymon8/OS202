Pour ce projet, j'ai travaillé avec un processeur du type Intel core i5-1240P disposant de 8 coeurs physiques et 2 threads par coeurs. Le cache a la répartition suivante: 8 instances de 384 Kib de cache L1d, 8 instances de 256KiB de cache L1i, 8 instances 10 MiB de cache L2, 1 instance de 12 MiB de cache L3.

En séquentiel, le temps moyen pour chaque pas de temps est de 0.00008s et on passe à 0.001s en ajoutant l'affichage. Il y a 594 itérations.

Parallélisation avec openMP:

m_fire_front est le dictionnaire qui nous intéresse (déclaré dans model.hpp par std::unordered_map<std::size_t, std::uint8_t> m_fire_front;). On va donc, dans un premier temps,  récupérer toutes les clefs de m_fire_front et les mettre dans une liste « indices_coord » puis on va itérer la fonction Model::update dessus.

CF simulation.cpp

Après ces modifications, on vérifie qu’on obtient bien la même simulation : 594 time steps  c’est bien la même simulation. Avec un temps de l’ordre de 1.37ms pour step+affichage (parralélisation avec 2 threads).
3: 1.07ms, 4: 2.6 ms, 5: 3.2 ms, 6: 3.1 ms, 7: 3.01 ms, 8: 3.2 ms

On observe une tendance très étrange qui est que la simulation ralenti avec le nombre de thread ajoutés. Cela doit être dû à une mauvaise utilisation du cache ou alors une mauvaise communication entre les threads.