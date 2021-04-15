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
git clone https://gitlab.com/bccyv/libregex.git
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
### Character classes
`\c` Control character

`\s` Whitespace [ \t\r\n\v\f]

`\S` Not Whitespace [^ \t\r\n\v\f]

`\d` Digit [0-9]

`\D` Not digit [^0-9]

`\w` Word [A-Za-z0-9_]

`\W` Not Word [^A-Za-z0-9_]

`\x` Hexadecimal digit [A-Fa-f0-9]

`\O` Octal Digit [0-7]

### Special characters
`\n` New line
`\r` Carriage return
`\t` Tab
`\v` Vertical tab
`\f` Form feed
### Escape sequences
`\` Escape following character
### Groups and ranges
`.` Any character except newline (\n)
`(a|b)` a or b
`(...)` Group
`[abc]` Single character (a or b or c)
`[^abc]` Single character (not a or b or c)
`[a-q]` Single character range (a or b ... or q)
`[A-Z]` Single character range (A or B ... or Z)
`[0-9]` Single digit from 0 to 9
### Quantifiers
`*` 0 or more
`+` 1 or more
`?` 0 or 1 (optional)
