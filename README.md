# libregex - regular expressions library for C

## Overview
Regex expressions are very useful to describe a formal language. We made a small library that converts a given regular expression into a language (represented by a DFA). Then, several functions helps you to find occurrences of a valid sentence for this language.

## Public API
```C
int    re_compile(t_regex *regex, const char *str);
size_t re_execute(t_regex *regex, const char *str, size_t nmatch, t_rematch *pmatch);
int    re_nextmatch(t_regex *regex, const char *str, char **saveptr, t_rematch *match);
int    re_fullmatch(t_regex *regex, const char *str);
size_t re_count(t_regex *regex, const char *str);
void   re_free(t_regex *regex);
```

## Compilation & Installation
Clone the repository and compile
```
git clone https://github.com/lfalkau/libregex
cd libregex
make
```
Install
```
make install
```
Update
```
cd libregex
git pull
make
make install
```

## Supported regex operators
| Character classes | Special characters | Escape sequences | Groups and ranges | Quantifiers |
| ----------------- | ------------------ | ---------------- | ----------------- | ----------- |
| `\c` Control character | `\n` New line | `\` Escape following character | `.` Any character except newline (\n) | `*` 0 or more |
| `\s` Whitespace | `\r` Carriage return | | `(a❘b)` a or b | `+` 1 or more |
| `\S` Not whitespace | `\t` Tab | | `(...)` Group | `?` 0 or 1 (optional) |
| `\d` Digit | `\v` Vertical tab | | `[abc]` Single character (a or b or c) | |
| `\D` Not digit | `\f` Form feed | | `[^abc]` Single character (not a or b or c) | |
| `\w` Word | | | `[a-q]` Single character range (a or b ... or q) | |
| `\W` Not word | | | `[A-Z]` Single character range (A or B ... or Z) | |
| `\x` Hexadecimal digit | | | `[0-9]` Single digit from 0 to 9 | |
| `\O` Octal digit | | | | |

## Ressources

[Computerphile - Regular Expressions](https://www.youtube.com/watch?v=528Jc3q86F8)

[Regular Expression to NFA](https://www.youtube.com/watch?v=RYNN-tb9WxI)

[NFA to DFA](https://www.youtube.com/watch?v=taClnxU-nao&pp=ugMICgJmchABGAE=)

[Minimizing a DFA](https://www.youtube.com/watch?v=0XaGAkY09Wc)
