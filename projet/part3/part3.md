Cf les fichiers simulation.cpp et model.cpp.

Cette partie constituait grosso modo une compilation des 2 parties précédentes. Avec une double parallélisation des tâches. Il fallait donc faire attention à bien attribuer les coeurs à chaque tâche. Aux vues des parties précédentes, j'ai choisi de garder le calcul de la carte dans Model::update() à 2 coeurs et de jouer avec les coeurs consacrés à la partie MPI du programme.

2: 903ms, 3:3123ms , 4: 4071ms, 5: 893ms, 6: 6300ms

Je ne sais vraiment pas quoi tirer de ces résultats car les valeurs ne sont pas aberrantes puisque j'ai ré-essayer plusieurs fois pour chacun des cas.