# 🐚 Minishell — Unix Command Interpreter

[![Academic Year](https://img.shields.io/badge/Epitech-Tek1-blue?style=for-the-badge&logo=epitech&logoColor=white)](https://www.epitech.eu/)
[![Module](https://img.shields.io/badge/Module-B--PSU--200-informational?style=for-the-badge)](#)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](#)

## 📘 Description
**Minishell** est une réimplémentation complète d'un interpréteur de commandes Unix inspiré de `tcsh` et `bash`. Il prend en charge le cycle d'invite, l'analyse lexicale, la résolution du `PATH`, et les appels système fondamentaux (`fork`, `execve`, `waitpid`).

## ⚙️ Fonctionnalités
- Commandes intégrées (built-ins) : `cd`, `setenv`, `unsetenv`, `env`, `exit`.
- Gestion des signaux Unix (SIGINT, SIGSEGV, SIGFPE, core dump).
- Gestion des redirections et des pipes entre processus.
- Variables d'environnement dynamiques.

## 🔨 Compilation & Utilisation
```bash
make
./mysh
```
