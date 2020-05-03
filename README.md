Projet Asteroids de Maxime Hohl
===============================

Rapport
-------

Le rapport est disponible dans le dossier `documents/rapport`.

 - Parler de l'ajout de OpenMP lib mais pas nécéssaire car 13ms (calculer fps) 
   constant sur ma machine ce qui est plus que avec OpenMP (car trop peut 
   d'éléments peut-être avec particules)

TODO
----
 - Faire en sorte que les astéroïdes ne se spawn pas dessus
 - Ajouter tout les paramètre dans le système de `settings` à la place de constexpr
 - Ajouter la lecture des settings à partir d'un fichier de config
 - Empecher le démarrage d'une nouvelle partie quand le joueur "spam" la touche espace
 - Ajout de la doc Doxygen
 - TOUJOURS PLUS DE LOG

BUGS
----
 - Crash lors de la destruction d'un astéroïde avec une vitesse de {0,0}
 - Crash lors de la collison tir/astéroïde quand compilé avec MSVC
 - Des astéroides avec une vitesse beaucoup trop élevée aparaissent parfois
