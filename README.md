Projet Asteroids de Maxime Hohl
===============================

Rapport
-------

Le rapport est disponible dans le dossier `documents/rapport`.

TODO
----
 - Améliorer le calcul de la vitesse des astéroïdes après explosion
 - mettre une taille aléatoire sur les astéroides générés après destruction
 - Faire en sorte que les astéroïdes ne se spawn pas dessus
 - Ajouter tout les paramètre dans le système de `settings` à la place de constexpr
 - Ajouter la lecture des settings à partir d'un fichier de config
 - Mettre une seed aléatoire
 - Empecher le démarrage d'une nouvelle partie quand le joueur "spam" la touche espace
 - Ajout de la doc Doxygen
 - Ajout de pmp pour les moteur de physique et les astéroides
 - TOUJOURS PLUS DE LOG

BUGS
----
 - Crash lors de la destruction d'un astéroïde avec une vitesse de {0,0}
 - Crash lors de la collison tir/astéroïde quand compilé avec MSVC
 - Des astéroides avec une vitesse beaucoup trop élevée aparaissent parfois
