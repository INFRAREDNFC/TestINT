# sort-jenkins-ci

Prosty projekt w języku C przygotowany do zadania z Jenkins CI.

Jenkins pobiera repozytorium z GitHuba, kompiluje program przez `make` i uruchamia wynikowy plik `./sort`.

## Uruchomienie lokalne

```bash
make clean all
./sort
```

Oczekiwany wynik:

```text
Przed sortowaniem: 9 4 1 7 3 8 2 6 5
Po sortowaniu:    1 2 3 4 5 6 7 8 9
```
