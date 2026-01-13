# Woody Woodpacker

## Description
Woody Woodpacker est un packer pour executables ELF 64-bits sous Linux. Son objectif est de chiffrer la section de code (`.text`) d'un binaire cible, de l'injecter avec un shellcode de déchiffrement ("stub"), et de modifier les métadonnées ELF pour que ce shellcode s'exécute en premier, déchiffre le programme original, et lui rende la main.

## Fonctionnement Détaillé

Le programme suit une séquence précise pour modifier le binaire cible sans corrompre son exécution.

### 1. Initialisation et Parsing
*   Le programme ouvre le fichier cible et vérifie sa signature via les **Magic Bytes** ELF (`0x7F 'E' 'L' 'F'`).
*   Il charge l'intégralité du fichier en mémoire via `mmap` pour faciliter la manipulation des octets.

### 2. Allocation et Injection du Payload
Contrairement à une injection dans une "code cave" (espace vide existant), ce packer agrandit physiquement le fichier :
*   Il calcule une nouvelle **Adresse Virtuelle (vaddr)** alignée sur une page (`0x1000`/4096 bytes) à la suite du dernier segment `PT_LOAD` existant.
*   Il ajoute le shellcode (le décrypteur) à la toute fin du fichier (`append_payload`).

### 3. Manipulation des En-têtes (Segment Hijacking)
Pour rendre ce nouveau code exécutable sans créer de nouveau header (ce qui décalerait tout le fichier), le packer utilise une technique de **détournement de segment** :
*   Il parcourt les Program Headers (`Phdr`) à la recherche d'un segment de type `PT_NOTE`.
*   Il transforme ce segment `PT_NOTE` en `PT_LOAD`.
*   Il met à jour ses propriétés pour mapper le shellcode ajouté à la fin du fichier :
    *   `p_offset` : Pointe vers la fin du fichier (payload).
    *   `p_filesz` / `p_memsz` : Ajustés à la taille du payload.
    *   `p_flags` : Définit les permissions sur `PF_R | PF_X` (Lecture + Exécution).

### 4. Chiffrement (Polymorphisme)
Le chiffrement est réalisé avant l'écriture finale :
*   **Génération de clé** : Une clé de 8 octets (64 bits) est générée via `/dev/urandom`.
*   **Localisation** : Le programme identifie le segment `PT_LOAD` contenant le code exécutable original.
*   **Modification des permissions** : Il ajoute le flag `PF_W` (Écriture) au segment de code original (`phdr->p_flags |= PF_W`). **Ceci est critique** : sans cela, le shellcode ferait un *Segfault* en tentant de déchiffrer (écrire) dans la mémoire du programme au lancement.
*   **Algorithme** : Il applique un **XOR** sur la section `.text` (à partir du point d'entrée) avec la clé générée.

### 5. Finalisation et Patching
Avant de générer le fichier de sortie (`woody`), le packer met à jour les informations nécessaires au fonctionnement du shellcode :
*   **Entry Point** : L'en-tête ELF principale (`e_entry`) est modifiée pour pointer vers la nouvelle adresse du shellcode.
*   **Patching du Shellcode** : Les valeurs placeholders dans le shellcode injecté sont remplacées par les valeurs utiles :
    *   `v_start_addr` : L'adresse virtuelle où commence le chiffrement.
    *   `v_size` : La taille de la zone chiffrée.
    *   `v_key` : La clé XOR générée.
    *   **Saut Relatif** : L'instruction `JMP` (opcode `0xE9`) à la fin du shellcode est patchée avec l'offset nécessaire pour retourner à l'ancien Entry Point (`old_entry`) après le déchiffrement.

## Le Shellcode (.s)

Le code injecté est écrit en assembleur NASM 64-bits et effectue les actions suivantes au runtime :
1.  **Sauvegarde du contexte** : `push` de tous les registres (rax, rdi, rsi, etc.) pour ne pas perturber l'état du programme hôte.
2.  **Déchiffrement** :
    *   Récupère l'adresse de départ, la taille et la clé stockées dans les variables du shellcode.
    *   Exécute une boucle de déchiffrement : `XOR` de l'octet courant avec la clé, puis rotation de la clé (`ror rdx, 8`) pour l'octet suivant.
3.  **Fingerprint de fin** : Affiche à nouveau `..WOODY..`.
4.  **Restauration** : `pop` des registres pour restaurer l'état exact avant l'injection.
5.  **Retour** : Saute (`jmp`) vers le véritable point d'entrée du programme (maintenant déchiffré).

## Spécificités Techniques

*   **Alignement** : Gestion stricte de l'alignement mémoire (`0x1000`) pour respecter les contraintes du noyau Linux.
*   **Adressage Relatif** : Le shellcode utilise `default rel` et `lea` pour être totalement indépendant de sa position en mémoire (Position Independent Code).
