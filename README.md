Projet Asteroids de Maxime Hohl
===============================

TODO
----
 - Déplacer la class Polygon du dossier Renddering au dossier Types.
 - Ajout d'un système de gestion des erreurs (LOG (fichier, terminal) + Message box)
 - Améliorer le calcul de la vitesse des astéroïdes après explosion
 - Ajouter tout les paramètre dans le système de `settings` à la place de constexpr
 - Mettre une seed aléatoire
 - Empecher le démarrage d'une nouvelle partie quand le joueur "spam" la touche espace
 - Ajouter la lecture des settings à partir d'un fichier de config
 - Faire en sorte que les astéroïdes ne se spawn pas dessus

BUGS
----
- Crash lors de la destruction d'un astéroïde avec une vitesse de {0,0}
- A la destruction d'astéroïdes, des fantomes restes dans le système de physique
- Crash lors de la collison tor/astéroïde quand compilé avec MSVC