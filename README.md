# libregex - regular expressions library for C

## Overview
Regex expressions are very useful to describe a formal language. We made a small library that converts a given regular expression into a language (represented by a DFA). Then, several functions helps you to find occurrences of a valid sentence for this language.

## Public API
```C
int re_compile(t_regex *regex, const char *str);
size_t re_execute(t_regex *regex, const char *str, size_t nmatch,
                  t_rematch *pmatch);
int re_nextmatch(t_regex *regex, const char *str, char **saveptr,
                 t_rematch *match);
int re_fullmatch(t_regex *regex, const char *str);
size_t re_count(t_regex *regex, const char *str);

void re_free(t_regex *regex);
```

## Compilation & Instalation
Clone the repository
```
git clont https://gitlab.com/bccyv/libregex.git
```
Compile
```
make
```
Install
```
make install
```

## supported regex operators
![Image](https://i.goopics.net/XJVlb.png)
