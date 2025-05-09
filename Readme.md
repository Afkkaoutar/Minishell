# MINISHELL - 42

Ce projet a été réalisé par deux personnes et divisé en deux parties :

- **Parce** : Partie d'analyse, où les entrées de l'utilisateur sont traitées.
- **Exec** : Partie d'exécution, où les commandes analysées sont effectivement lancées.

---

## 📖 Présentation du projet

Le projet **Minishell** consiste en la création d'un shell minimaliste qui permet à l'utilisateur d'interagir avec le système d'exploitation via des commandes en ligne de commande. Il vise à reproduire les fonctionnalités de base d'un shell comme Bash, avec une attention particulière à la gestion des signaux, des redirections, des variables d'environnement et de l'historique.

### Fonctionnalités :

- **Exécution des commandes** : Exécution de commandes avec ou sans chemin absolu ou relatif.
- **Historique** : Navigation dans l'historique des commandes avec les flèches haut/bas.
- **Redirections** : Support des redirections (`<`, `>`, `>>`).
- **Pipes** : Implémentation des pipes (`|`), permettant l'enchaînement de commandes.
- **Here-Doc** : Support de la commande `<<` pour les redirections d'entrée multiples.
- **Gestion des guillemets** : Prise en charge des guillemets simples (`'`) et doubles (`"`) pour échapper les caractères spéciaux, ainsi que des variables d'environnement dans les guillemets doubles.
- **Variables d'environnement** : Gestion des variables d'environnement et des exportations.
- **Signaux** : Gestion des signaux comme dans Bash (Ctrl+C, Ctrl+\ et Ctrl+D).

---

## 🛠️ Fonctionnalités principales

### 1. **Commandes internes**
Le shell implémente les commandes internes suivantes :

- **echo** : Affiche un message, avec support de l'option `-n` pour supprimer le saut de ligne.
- **cd** : Change le répertoire courant avec des chemins relatifs ou absolus.
- **pwd** : Affiche le répertoire de travail actuel.
- **export** : Définit une variable d'environnement.
- **unset** : Supprime une variable d'environnement.
- **env** : Affiche les variables d'environnement.
- **exit** : Quitte le shell avec un code de sortie (par défaut `0` si aucun argument).

### 2. **Analyse des entrées utilisateur (Parsing)**

Le processus de parsing consiste à lire et interpréter les commandes entrées par l'utilisateur. Voici comment nous avons traité les variables d'environnement et les commandes :

- Initialisation des variables d'environnement avec `env` et gestion via une liste chaînée.
- Séparation des éléments de chaque variable d'environnement à l'aide du caractère `=`.

### 3. **Redirections et Pipes**

Le shell gère les redirections de flux, telles que la redirection de la sortie standard avec `>` ou la redirection d'entrée avec `<`. Il est aussi capable d'enchaîner plusieurs commandes avec des **pipes** (`|`), permettant ainsi d'envoyer la sortie d'une commande comme entrée d'une autre.

### 4. **Gestion des signaux**

Le projet intègre une gestion des signaux pour contrôler le comportement du shell lors de certaines actions :

- **SIGINT** (Ctrl+C) : Interrompt l'exécution et affiche à nouveau le prompt sans quitter le shell.
- **SIGQUIT** (Ctrl+\) : Ignoré pour éviter des comportements indésirables.
- **SIGTERM** et autres signaux : Gérés pour permettre un comportement contrôlé lors de la fermeture du shell.

### 5. **Gestion de l'historique**

Les commandes sont stockées dans un historique permettant à l'utilisateur de naviguer entre les précédentes commandes à l'aide des flèches haut et bas.

---

## 🖥️ Compilation et Exécution

### Compilation :

1. Clonez le dépôt sur votre machine :
    ```bash
    git clone <URL_DE_VOTRE_REPO>
    ```

2. Naviguez dans le répertoire du projet et compilez avec `make` :
    ```bash
    cd minishell
    make
    ```

### Exécution :

Pour exécuter le shell, entrez la commande suivante :
```bash
./minishell
