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

________________________________________

[[EXECUTION PART]]

[Redirections]

>   out_red Redirige la sortie (stdout) d'une commande vers un fichier. Si le fichier existe déjà, il est écrasé.
ex: echo "Bonjour" > fichier.txt
La commande echo "Bonjour" va afficher "Bonjour" dans le terminal. Avec >, la sortie est envoyée dans le fichier fichier.txt. Si le fichier existe déjà, son contenu sera remplacé par "Bonjour".

>>  Redirige la sortie (stdout) d'une commande vers un fichier, mais cette fois-ci, au lieu de l'écraser, il ajoute la sortie à la fin du fichier.
ex: echo "Salut" >> fichier.txt
La commande ajoute "Salut" à la fin du fichier fichier.txt sans supprimer son contenu précédent.

<   in_red  Prend l'entrée d'une commande à partir d'un fichier au lieu de l'attendre dans le terminal.
ex: cat < fichier.txt
la commande cat lit le contenu de fichier.txt grâce à < et l'affiche dans le terminal.

________________________________________

[[ERRORS]]

//->  cat << lol | cat << yeah | cat << yo (a besoin des 3 délimitateurs pour s’arrêter, dois renvoyer ce que j’ai rentré av le dernier délimitateur).

//->  ls | cat << lol | wc (ne va doit exec le ls mais simplement faire le heredoc et afficher wc).

//->  cat << lol | ls

//->  ajouter printf exit.

->  cat << lol | cat << yeah | cat << yo 
    write something : cat << lol | cat << yeah | cat << yo
    > yo
    > yeah
    > lol
    yo
    yeah
    > 

->  ls | cat << lol | wc pareril qu’en bas, wc ne renvoie que des 0??

->  write something : ls | cat << lol | wc
    > haha
    > hihi
    > lol
    haha
    hihi
           0       0       0
    au lieu de
    bash-3.2$ ls | cat << lol | wc
    > haha
    > hihi
    > lol
           2       2      10




________________________________________

   [[BUILT_IN]]

//->  Les commandes intégrées comme cd, export, unset, et exit n'ont pas d'effet durable dans un pipeline car
//    elles sont exécutées dans un sous-shell et ne modifient pas l'environnement du shell principal.
//    Les autres commandes (echo, pwd, env) fonctionnent comme prévu dans les pipelines car elles ne tentent pas de modifier l'environnement.
//    
//->  if plusieurs cmd, regarder si il y a built_in,
//    si oui, fork, quel type de buil_in?
//    si c'est un built_in apl la fct du built_in,
//    sinon exec
//    si built_in = cd, export, unset, exit
//    si built_in = echo, pwd, env ->rediriger les pipes
___________________________
