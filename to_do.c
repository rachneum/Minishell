TO_DO_LIST

[[PARSING PART]]

// - make a function to free everything V
// - could make token_l_free work from any node V
// - add  '$' implementation
// - remove quotes in the tokenization
- check all error returns
// - implement redir in parsing
- adapt free function for the t_cmd list - should be good needs testing
- check parsing for built-ins

[[EXECUTION PART]]

/*
>   out_red Redirige la sortie (stdout) d'une commande vers un fichier. Si le fichier existe déjà, il est écrasé.
ex: echo "Bonjour" > fichier.txt
La commande echo "Bonjour" va afficher "Bonjour" dans le terminal. Avec >, la sortie est envoyée dans le fichier fichier.txt. Si le fichier existe déjà, son contenu sera remplacé par "Bonjour".

>>  Redirige la sortie (stdout) d'une commande vers un fichier, mais cette fois-ci, au lieu de l'écraser, il ajoute la sortie à la fin du fichier.
ex: echo "Salut" >> fichier.txt
La commande ajoute "Salut" à la fin du fichier fichier.txt sans supprimer son contenu précédent.

<   in_red  Prend l'entrée d'une commande à partir d'un fichier au lieu de l'attendre dans le terminal.
ex: cat < fichier.txt
la commande cat lit le contenu de fichier.txt grâce à < et l'affiche dans le terminal.
*/

[[ERRORS]]

->cat << lol | ls

->ls | cat << lol | cat Makefile (fonctionne 1 fois sur 2??)

->cat << lol | cat << yeah | cat << yo (a besoin des 3 délimitateurs pour s’arrêter, dois renvoyer ce que j’ai rentré av le dernier délimitateur)

->cat Makefile > lol > lol1 > lol2(doit créer le fichier lol, lol1 aussi)

->j’ai ajouté un printf pour exit mais mtn exit s’affiche qd je fais un retour à la ligne??

->segfault ./minishell espace

