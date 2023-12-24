# <font color="red"> Projet **Systeme D'exploitation** Les Threads </font>

##Q1: Quelles sont les structures de données à utiliser ?

Il faut utiliser des structures de données pour représenter les matrices B, C, et A,
ainsi qu'un tampon T pour stocker les résultats intermédiaires.
On peut utiliser des tableaux bidimensionnels pour les matrices et un tableau unidimensionnel pour le tampon.

##Q2: Comment allez-vous protéger l'accès à ces données?

Pour protéger l'accès aux données partagées entre les threads,
on peut utiliser des verrous (mutex) et des sémaphores.
Un mutex peut être utilisé pour assurer l'accès exclusif aux matrices B, C, et A,
et un ensemble de sémaphores pour synchroniser la communication entre les producteurs et les consommateurs.

##Q3: Quels sont les risques ?

Les risques principaux incluent les conditions de concurrence (race conditions),
où plusieurs threads tentent d'accéder ou de modifier les mêmes données simultanément.
Cela peut conduire à des résultats imprévisibles et des erreurs dans le calcul des matrices.
#multiplication-matrice-using-threads

# multiplication-matrice-using-threads
