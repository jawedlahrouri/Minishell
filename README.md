[![Academic Year](https://img.shields.io/badge/Epitech-Tek1-blue?style=for-the-badge&logo=epitech&logoColor=white)](https://www.epitech.eu/)
[![Language: C](https://img.shields.io/badge/Language-C-00599C.svg?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Module](https://img.shields.io/badge/Module-B--PSU--200-informational?style=for-the-badge)](#)

# 🐚 Minishell — Interpréteur de Commandes Unix (mysh)

**Minishell** est un interpréteur de commandes Unix complet développé en langage C. Il reproduit le fonctionnement fondamental d'un shell POSIX en traitant la saisie utilisateur, l'exécution de binaires externes via `fork`/`execve`, la gestion des variables d'environnement, les commandes intégrées (*builtins*), les pipelines et les redirections de flux.

---

## 🚀 Fonctionnalités Implémentées

### 🔧 Commandes Internes (Builtins)
- **`cd [path]`** : Changement de répertoire de travail (prise en charge de `cd -` pour le répertoire précédent, `cd` ou `cd ~` pour le répertoire HOME, mise à jour des variables `PWD` et `OLDPWD`).
- **`setenv [NAME] [VALUE]`** : Définition ou modification d'une variable d'environnement avec validation des caractères alphanumériques.
- **`unsetenv [NAME]`** : Suppression d'une variable d'environnement existante.
- **`env`** : Affichage exhaustif des variables d'environnement actives.
- **`exit [status]`** : Fermeture propre du shell avec propagation du code de retour.

### ⚙️ Exécution & Résolution de Binaires
- Analyse de la variable d'environnement `PATH` pour localiser automatiquement les exécutables.
- Exécution directe par chemin absolu (`/bin/ls`) ou relatif (`./my_program`).
- Gestion rigoureuse des erreurs système (`Command not found`, `Permission denied`, `Exec format error`).

### 🔀 Pipelines & Redirections de Flux
- **Pipelines (`|`)** : Exécution concurrente de commandes reliées par des tubes Unix (`pipe()` et `dup2()`).
- **Redirection de sortie (`>`, `>>`)** : Écriture avec écrasement ou ajout en fin de fichier.
- **Redirection d'entrée (`<`)** : Injection du contenu d'un fichier en entrée standard.
- **Point-virgule (`;`)** : Enchaînement séquentiel de plusieurs commandes sur une même ligne.

### 🛡️ Gestion des Signaux & Robustesse
- Interception de `SIGINT` (Ctrl+C) : affiche un nouveau prompt sans interrompre le shell.
- Fin de fichier (Ctrl+D) : fermeture gracieuse du shell.
- Détection des arrêts anormaux de processus fils avec message explicite (`Segmentation fault (core dumped)`, `Floating exception`).

---

## 🛠️ Compilation & Exécution

```bash
make        # Génère l'exécutable 'mysh'
make clean  # Nettoie les fichiers objets (.o)
make fclean # Supprime les fichiers compilés
make re     # Recompile l'ensemble

./mysh      # Lance le shell interactif
```
