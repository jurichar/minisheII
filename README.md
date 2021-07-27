# Minishell :


## ToDo :

- [ ] builtin

- [x] parsing

- [x] exec

- [x] redir

- [ ] pipe

- [ ] gestions d'erreurs


## ToFix :

- PLUS BESOIN DE GERER "\" et ";"

- ";|" fonctionne po (genre built_exec printf de sep il fait des trucs etrange + si on met un sep en premier ca fait crash) 

- "ls>a" a fix\n

- ";" a remettre\n

## Work :

### Pipe :

- [Link 1](http://www.zeitoun.net/articles/communication-par-tuyau/start\n)

- [Link 2](http://www.zeitoun.net/_media/articles/communication-par-tuyau/stdxxx_2.png\n)

- [Link 3](http://www.rozmichelle.com/pipes-forks-dups/\n)

- [Link 4](https://tldp.org/LDP/lpg/node11.html\n)

Tu peux faire un wrapper de fork fork_child(int in, int out, int fd_to_close) qui gere tous les cas de fork a faire (que ca soit pipe ou commande normale)

Pour une commande normale tu fais fork_child(STDIN_FILENO, STDOUT_FILENO, -1 (rien a close))
pour un pipe tu met tes in et out qu'il faut et fd_to_close le fd a close dans le fork (celui du pipe qui sert pas) et tu fais des if (in != STDIN_FILENO) ou (out != STDOUT_FILENO) pour detecter si c'est un cas de pipe ou pas (donc si il faut dup des fd dans le fork ou close des fd dans le fork et le parent apres avoir dup)
la fonction return le pid donc elle s'utilise exactement comme un fork normal sauf que dans le fork tu as les bon fd pour etre pipe
la fonction tiens en 15 lignes apres t'as juste a gerer ta suite de pipe en appelant pipe() une fois par |