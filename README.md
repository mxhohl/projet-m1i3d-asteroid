Projet Asteroids de Maxime Hohl
===============================

Rapport
-------

Le rapport est disponible dans le dossier `documents/rapport`.
La génération du pdf à partir du fichier LaTeX nécéssitent les poslices de 
caractère suivantes :
 - Linux Libertine - http://www.linuxlibertine.org
 - JetBrains Mono - https://www.jetbrains.com/lp/mono/

Compilation
-----------

Le projet fonction grâce à CMake.

Il peut être compilé avec MinGW sur Windows mais présente un bogue avec MSVC 
(cf. section *3.2. Bogues connus* du rapport).

Il est testé et fonctionne avec GCC sur Linux et Mac OS X et devrait fonctionner 
correctement avec les dérivés de LLVM (clang, Apple LLVM, etc.) bien que ce ne
soit pas testé.

Pour Compiler sous UNIX, suivre les étapes suivantes :
```bash
mkdir build
cd build
cmake ..
make
./asteroids
```

Pour compiler sous windows, on peut suivre les mêmes étapes que pour les 
systèmes UNIX avec PowerShell ou utiliser un IDE compatible CMake et MinGW 
(CLion, QtCreator, etc.). 

TODO et bogues
--------------

### TODO

 - Faire en sorte que les astéroïdes ne se spawn pas dessus
 - Ajouter tout les paramètre dans le système de `settings` à la place de constexpr
 - Ajouter la lecture des settings à partir d'un fichier de config
 - Empecher le démarrage d'une nouvelle partie quand le joueur "spam" la touche espace
 - Ajout de la doc Doxygen
 - TOUJOURS PLUS DE LOG

### BOGUES

 - Crash lors de la destruction d'un astéroïde avec une vitesse de {0,0}
 - Crash lors de la collison tir/astéroïde quand compilé avec MSVC
 - Des astéroides avec une vitesse beaucoup trop élevée aparaissent parfois
