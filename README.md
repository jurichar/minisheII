# Minishell

## Eval

- [x] parser

- [x] gestions d'erreurs

- [ ] pas d'interpretation de quote ouverte, de \ ou de ;

- [x] UNE globale (et expliquer pourquoi).

- [x] prompt qui attend une commande.

- [x] historique fonctionnel.

- [x] chercher et executer le bon binaire (relative / absolute PATH).

- [ ] (',") inhibe tt interpretations.

- [x] pipes

- [x] multi-pipe

## redirection

- [x] ">"

- [x] "<"

- [x] ">>"

- [x] "<<"

- [ ] multiple redir.

- [ ] variable d'environnement.

- [ ] $? affiche le status de la derniere pipe EXIT.

## signaux

- [x] ctrl-C

- [x] ctrl-D

- [x] ctrl-\

## builtins

- [x] echo avec -n

- [x] cd avec seulement un chemin relative / absolue

- [x] pwd sans option

- [x] export sans option

- [x] unset sans option

- [x] env sans option ni argument

- [x] exit sans option

## ToFix

- mute TAB

- fleche du haut apres une commande

- reparer historique

- format du nom de variable.

- echo $HOME $HOME $HOME
/home/user42 /home/user42`

- echo $HOME"$HOME"
/home/user42$ME

- "cat < test.sh" : .sh no such file or directory

- "ls >a" a fix