# Guide de Conversion C vers C++

## Vue d'ensemble

Cette branche (`cpp-version`) contient l'implémentation en C++ du projet RayTracer, originellement écrit en C. Tous les fichiers sources ont été convertis pour être compatibles avec C++11.

## Changements Effectués

### 1. Fichiers Sources
- **30 fichiers .c** ont été renommés en **.cpp**
- Tous les fichiers conservent la même fonctionnalité que la version C

### 2. Système de Build (Makefile)
- Compilateur changé de `cc` à `g++`
- Ajout du flag `-std=c++11` pour utiliser C++11
- Mise à jour des règles de compilation pour les fichiers `.cpp`

### 3. En-têtes (miniRT.h)
- Remplacement des en-têtes C par leurs équivalents C++:
  - `float.h` → `cfloat`
  - `math.h` → `cmath`
  - `stdio.h` → `cstdio`
  - `stdlib.h` → `cstdlib`
  - `string.h` → `cstring`
- Ajout de blocs `extern "C"` pour les bibliothèques C (libft, mlx, get_next_line)

### 4. Code Source
- **Literals composés C99** convertis en initialisation C++ appropriée
  - Exemple: `(t_vec3){x, y, z}` → initialisation explicite via variables
- Toutes les fonctions vectorielles mises à jour pour la compatibilité C++
- Fichiers modifiés:
  - `calcul_de_vecteur.cpp`
  - `calcul_de_vecteur2.cpp`
  - `trace.cpp`
  - `update_camera.cpp`

## Compilation

Pour compiler le projet C++:

```bash
# Initialiser les sous-modules (si nécessaire)
git submodule update --init --recursive

# Compiler
make

# Nettoyer
make clean

# Recompiler complètement
make re
```

## Différences Clés C vs C++

1. **Initialisation de structures**: En C++, les literals composés ne sont pas supportés de la même manière
2. **En-têtes**: Utilisation des en-têtes C++ standard plutôt que les en-têtes C
3. **Linkage**: Les bibliothèques C nécessitent `extern "C"` pour la compatibilité

## Compatibilité

- **Standard C++**: C++11
- **Compilateur**: g++ (GCC C++ compiler)
- **Bibliothèques externes**: Inchangées (libft, minilibx-linux)

## Notes

- La fonctionnalité reste identique à la version C
- Tous les algorithmes de ray tracing sont préservés
- Les structures de données restent les mêmes (pas de conversion en classes C++ pour cette version)

## Prochaines Étapes Possibles

Pour une version C++ plus idiomatique, considérer:
- Conversion des structures en classes avec méthodes
- Utilisation de constructeurs
- Surcharge d'opérateurs pour les opérations vectorielles
- Utilisation de `std::vector` au lieu de tableaux fixes
- Gestion automatique de la mémoire avec smart pointers
