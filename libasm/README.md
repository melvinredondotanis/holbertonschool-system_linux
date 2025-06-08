# libasm

## Les différences entre les syntaxes Intel et AT&T

### Syntaxe Intel
- **Ordre des opérandes**: `instruction destination, source`
- **Registres**: Pas de préfixe (`eax`, `ebx`)
- **Valeurs immédiates**: Pas de préfixe (`mov eax, 42`)
- **Taille des opérandes**: Indiquée par l'instruction (`mov DWORD PTR [ebx], eax`)
- **Adressage mémoire**: Utilisation de crochets (`mov eax, [ebx+8*ecx+12]`)
- **Aspect général**: Plus lisible et intuitive pour les débutants

### Syntaxe AT&T
- **Ordre des opérandes**: `instruction source, destination` (ordre inversé)
- **Registres**: Préfixés par `%` (`%eax`, `%ebx`)
- **Valeurs immédiates**: Préfixées par `$` (`movl $42, %eax`)
- **Taille des opérandes**: Suffixe sur l'instruction (`movl` pour long, `movw` pour word)
- **Adressage mémoire**: Utilisation de parenthèses et notation complexe (`movl 12(%ebx,%ecx,8), %eax`)
- **Aspect général**: Plus verbeux et considéré plus compliqué par certains

## Les différents registres généraux (GPR) en x86

### Registres 64-bits (x86-64)
- **RAX**: Accumulateur, utilisé pour les opérations arithmétiques et la valeur de retour des fonctions
- **RBX**: Registre de base, historiquement utilisé pour l'adressage indexé
- **RCX**: Compteur, utilisé dans les boucles et les opérations de chaîne
- **RDX**: Registre de données, utilisé pour l'entrée/sortie et certaines opérations arithmétiques
- **RSI**: Source Index, utilisé comme pointeur source dans les opérations sur les chaînes
- **RDI**: Destination Index, utilisé comme pointeur de destination dans les opérations sur les chaînes
- **RSP**: Stack Pointer, pointe vers le sommet de la pile
- **RBP**: Base Pointer, sert de référence pour accéder aux paramètres et variables locales
- **R8-R15**: Registres supplémentaires introduits avec x86-64

### Versions partielles des registres
- Versions 32-bits: **EAX**, **EBX**, etc. (moitié basse)
- Versions 16-bits: **AX**, **BX**, etc. (moitié basse de la version 32-bits)
- Versions 8-bits basses: **AL**, **BL**, etc.
- Versions 8-bits hautes (des registres 16-bits): **AH**, **BH**, etc.

## Les différents registres de drapeaux (flags)

Le registre **RFLAGS** (64-bits) contient de nombreux drapeaux, dont les plus importants sont:

- **ZF** (Zero Flag): Indique si le résultat d'une opération est zéro
- **CF** (Carry Flag): Signale un dépassement de capacité dans une opération non signée
- **SF** (Sign Flag): Reflète le bit de signe (bit le plus significatif) du résultat
- **OF** (Overflow Flag): Signale un dépassement arithmétique dans une opération signée
- **PF** (Parity Flag): Indique si le nombre de bits à 1 dans le résultat est pair
- **AF** (Auxiliary Flag): Utilisé pour les opérations BCD (Binary Coded Decimal)
- **DF** (Direction Flag): Détermine la direction (croissante/décroissante) pour les opérations sur les chaînes
- **IF** (Interrupt Flag): Active/désactive la réponse aux interruptions matérielles
- **TF** (Trap Flag): Utilisé pour le débogage pas à pas

## Qu'est-ce qu'un cadre de pile (stack frame)

Un cadre de pile est une zone réservée sur la pile pour chaque appel de fonction, qui contient:
- L'adresse de retour (où reprendre l'exécution après la fonction)
- L'ancien pointeur de base (sauvegarde du RBP)
- Les variables locales de la fonction
- Espace pour les registres sauvegardés
- Les paramètres supplémentaires (au-delà du 6ème en x86-64)

Il fournit un contexte d'exécution isolé pour chaque fonction, permettant la récursivité et une bonne gestion de la mémoire.

## Comment configurer un cadre de pile (stack frame)

Le prologue standard d'une fonction en x86-64:
```asm
fonction:
    push rbp           ; Sauvegarde l'ancien pointeur de base
    mov rbp, rsp       ; Crée un nouveau pointeur de base
    sub rsp, N         ; Réserve N octets pour les variables locales
```

Pour les variables locales:
- Premier élément à `[rbp-8]`
- Deuxième élément à `[rbp-16]`, etc.

Pour les paramètres (au-delà des 6 premiers):
- Premier paramètre supplémentaire à `[rbp+16]`
- Deuxième paramètre supplémentaire à `[rbp+24]`, etc.

L'épilogue standard:
```asm
    mov rsp, rbp       ; Restaure le pointeur de pile
    pop rbp            ; Restaure l'ancien pointeur de base
    ret                ; Retourne à l'adresse appelante
```

## Comment appeler une fonction

Pour appeler une fonction en assembleur x86-64:

1. **Préparer les arguments**: Placer les 6 premiers arguments dans les registres RDI, RSI, RDX, RCX, R8, R9 (dans cet ordre)
2. **Empiler les arguments supplémentaires**: S'il y a plus de 6 arguments, empiler les arguments restants de droite à gauche
3. **Aligner la pile**: S'assurer que RSP est aligné sur 16 octets avant l'appel
4. **Appeler la fonction**: Utiliser l'instruction `call fonction`
5. **Après l'appel**: La valeur de retour se trouve dans RAX (et RDX pour les valeurs 128 bits)
6. **Nettoyer la pile**: Si nécessaire, ajuster RSP pour enlever les arguments empilés

```asm
; Appel à une fonction avec 3 arguments
mov rdi, 10       ; Premier argument
mov rsi, 20       ; Deuxième argument
mov rdx, 30       ; Troisième argument
call ma_fonction  ; Appel de la fonction
; La valeur de retour est dans RAX
```

## Comment faire un appel système

Un appel système sous Linux en x86-64:

1. **Placer le numéro de l'appel système** dans RAX
2. **Préparer les arguments**: Utiliser RDI, RSI, RDX, R10, R8, R9 pour les 6 premiers arguments
3. **Exécuter l'instruction** `syscall`
4. **Vérifier le résultat**: La valeur de retour est dans RAX, une valeur négative indique une erreur

```asm
; Exemple d'appel système write(1, message, len)
mov rax, 1        ; syscall write
mov rdi, 1        ; fd = 1 (stdout)
mov rsi, message  ; buffer
mov rdx, len      ; length
syscall           ; Exécute l'appel système
```

## Comment passer des paramètres à une fonction

En x86-64 selon la convention System V AMD64:

1. **Les 6 premiers entiers/pointeurs** vont dans: RDI, RSI, RDX, RCX, R8, R9
2. **Les 8 premiers arguments flottants** vont dans: XMM0-XMM7
3. **Les arguments supplémentaires** sont empilés de droite à gauche
4. **Les structures** sont généralement passées par référence (pointeur), ou par valeur selon leur taille

```asm
; Fonction avec 7 arguments entiers
mov rdi, arg1
mov rsi, arg2
mov rdx, arg3
mov rcx, arg4
mov r8, arg5
mov r9, arg6
push arg7              ; Argument supplémentaire sur la pile
call ma_fonction
add rsp, 8             ; Nettoie la pile (enlève arg7)
```

## Comment récupérer les paramètres

Dans la fonction appelée:

1. **Les 6 premiers arguments entiers/pointeurs** sont déjà dans RDI, RSI, RDX, RCX, R8, R9
2. **Les arguments sur la pile** sont accessibles via RBP:
   - Premier argument empilé à `[rbp+16]`
   - Deuxième argument empilé à `[rbp+24]`, etc.

```asm
ma_fonction:
    push rbp
    mov rbp, rsp
    ; RDI contient déjà le premier argument
    ; RSI contient déjà le deuxième argument
    ; Pour accéder au 7ème argument (sur la pile):
    mov rax, [rbp+16]
    ; Traitement de la fonction...
    pop rbp
    ret
```

Cette approche directe de manipulation des paramètres est ce qui rend l'assembleur plus explicite mais aussi plus complexe que les langages de haut niveau.
