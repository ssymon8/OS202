Cf simulation.cpp

Temps globaux d'execution:

2: 689ms, 3: 785ms, 4: 1061ms, 5: 1227ms, 6: 4455ms, 7: 4920ms, 8: 7553ms

On a un accélération flagrante par rapport à la première partie (environ 40% pour 2 processus) mais je n'arrive pas à expliquer pourquoi le programme ralenti en ajoutant des threads et encore moi le saut de temps d'execution entre 5 et 6 threads.
Il doit encore y avoir un problème de communication entre les différents threads, bien que le tout soit en mémoire partagée. Peut-être les communications entre les caches individuels des coeurs sont mauvaises?
