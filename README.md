Projet Asteroids de Maxime Hohl
===============================

TODO
----
 - Déplacer la class Polygon du dossier Renddering au dossier Types.
 - Utiliser un système de coordonés custom pour les GUI (forcer les éléments dans 
   un Panel et avoir un Panel "Global")
 - Ajout d'un système de gestion des erreurs (LOG (fichier, terminal) + Message box)
 - Faire en sorte que les astéroïdes ne spawn pas les un sur les autres

BUGS
----
- Crash lors de la destruction d'un astéroïde avec une vitesse de {0,0}
- A la destruction d'astéroïdes, des fantomes restes dans le système de physique
- Crash lors de la collison tor/astéroïde quand compilé avec MSVC