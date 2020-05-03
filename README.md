Projet Asteroids de Maxime Hohl
===============================

Rapport
-------

Le rapport est disponible dans le dossier `documents/rapport`.

TODO
----
 - Améliorer le calcul de la vitesse des astéroïdes après explosion
 - Ajouter tout les paramètre dans le système de `settings` à la place de constexpr
 - Mettre une seed aléatoire
 - Empecher le démarrage d'une nouvelle partie quand le joueur "spam" la touche espace
 - Ajouter la lecture des settings à partir d'un fichier de config
 - Faire en sorte que les astéroïdes ne se spawn pas dessus
 - Ajout de la doc Doxygen
 - Ajout de pmp pour les moteur de physique et les astéroides
 - PLUS DE LOG
 - remove rotation informations from asteroids
 - set random scale on new spawning asteroids

BUGS
----
 - Crash lors de la destruction d'un astéroïde avec une vitesse de {0,0}
 - Crash lors de la collison tor/astéroïde quand compilé avec MSVC
