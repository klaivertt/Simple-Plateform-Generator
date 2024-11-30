# Simple Plateform Generator

## Description

Ce programme en C utilise la bibliothèque **SFML** pour créer et gérer une carte contenant des plateformes composées de tuiles. Les plateformes peuvent être générées avec ou sans bordures, selon des modèles personnalisables. Ce programme permet :

- La création de plateformes avec différentes configurations de bordures (bordure complète, uniquement à gauche, uniquement à droite ou sans bordures).
- La personnalisation des plateformes en fonction de leur taille, des motifs de leurs tuiles et de leur position d'origine.
- L'organisation des plateformes sur une carte définie par ses dimensions et la taille des tuiles.

Ce programme est aussi une bonne introduction à la **modularité en C**, car il sépare les fonctionnalités en différentes fonctions bien définies. Cela facilite la lecture, la maintenance et l'évolution du code.

---

## Fonctionnalités

### 1. **Création de Plateformes**

Le programme propose plusieurs fonctions pour générer des plateformes avec des configurations spécifiques de bordures :

- `CreatePlateformeWithBorder` : Génère une plateforme avec des bordures sur tous les côtés.
- `CreatePlateformeWithLeftBorder` : Crée une plateforme avec une bordure uniquement sur le côté gauche.
- `CreatePlateformeWithRightBorder` : Crée une plateforme avec une bordure uniquement sur le côté droit.
- `CreatePlateformeWithNoBorder` : Génère une plateforme sans bordures fixes, permettant une configuration personnalisée des tuiles internes.

### 2. **Personnalisation des Plateformes**

Chaque plateforme est définie par :
- **Taille** : Nombre de tuiles en largeur et en hauteur.
- **ID des tuiles** : Tuiles de base, aléatoires et finales pour personnaliser les motifs.
- **Origine** : Position de la plateforme sur la carte.

### 3. **Gestion de la Carte**

La fonction `LoadMap` organise les plateformes sur une carte :
- Définit la taille de la carte (en nombre de tuiles).
- Spécifie les dimensions des tuiles (en pixels).
- Place plusieurs plateformes avec différentes configurations sur la carte.

---

## Familiarisation avec la Modularité en C


Dans ce programme, les différentes fonctions (par exemple, `CreatePlateformeWithBorder`, `CreatePlateformeWithLeftBorder`, etc.) sont dans des fichier différent pour permettre une meilleur flexibiliter dans le code;
---

## Utilisation

### Exemple : Chargement d'une Carte
La fonction `LoadMap` crée une carte exemple avec des plateformes :
1. Une petite plateforme avec des bordures complètes.
2. Une grande plateforme avec une bordure uniquement à gauche.
3. Une plateforme sans bordures définies, permettant des motifs personnalisés.
4. Une grande plateforme avec une bordure uniquement à droite.

### Extrait de Code
Voici un exemple de création et de placement de plateformes sur la carte :

