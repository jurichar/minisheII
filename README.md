# Minishell

## Eval

- [x] parser

- [x] gestions d'erreurs

- [ ] pas d'interpretation de quote ouverte, de \ ou de ;.

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

- [ ] "<<"

- [ ] multiple redir.

- [ ] variable d'environnement.

- [ ] $? affiche le status de la derniere pipe EXIT.

## signaux

- [ ] ctrl-C

- [ ] ctrl-D

- [ ] ctrl-\

## builtins

- [x] echo avec -n

- [x] cd avec seulement un chemin relative / absolue

- [x] pwd sans option

- [ ] export sans option

- [ ] unset sans option

- [x] env sans option ni argument

- [x] exit sans option

## ToFix

- unset fonctionne pas

- export sans '=' , export ecrase pas, export avec +=

- export avec plusieurs, doit ecraser. diff entr env et list export.

- format du nom de variable.

- premier char, alpha ou _ puis alpha ou num
essayer unset de la premiere var de l'env, puis env
expension

- echo $HOME $HOME $HOME
/home/user42 /home/user42`

- echo $HOME"$HOME"
/home/user42$ME

- "cat < test.sh" : .sh no such file or directory

- "ls >a" a fix

## Docs

### Pipe

- [Link 1](http://www.zeitoun.net/articles/communication-par-tuyau/start\n)

- [Link 2](http://www.zeitoun.net/_media/articles/communication-par-tuyau/stdxxx_2.png\n)

- [Link 3](http://www.rozmichelle.com/pipes-forks-dups/\n)

- [Link 4](https://tldp.org/LDP/lpg/node11.html\n)
