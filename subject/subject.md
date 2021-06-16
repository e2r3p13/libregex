# ft_regex

Loic buckwell – lfalkau@student.42.fr
Gabriel Lafond-Thenailles – glafond-@student.42.fr
42AI – contact@42ai.fr

# module01 – Regular languages & automatons

### Introduction
Take a breathe, you’re done with boolean logic for now. Are you still alive?
Good! But wait… It’s only the first step of a wider theory: The automata theory. Today you’ll dive deeper into it and work with finite state machines, in order to build your own regex library.
Even if regex is a dirty word for many programmers, take the time to understand them, they are kind of a magic power when they’re used well.


### General rules
* For this piscine, function prototypes are described in C, but you may use the language you want. There are a few constraints, though:
  * It must support generic types
  * It must support functions as first class citizens (example: supports lambda expressions) 
  * It must natively implements bitwise operations over integer types, or at least bitwise operations over a bitmap/boolmap type; though the former is strongly recommended 
  * Optional: support for operator overloading 
* We recommend that you use paper if you need to. Drawing visual models, making notes of technical vocabulary... This way, it’ll be easier to wrap your head around the new concepts you’ll discover, and use them to build your understanding for more and more related concepts. Also, doing computations by head is really hard and error-prone, so having all the steps written down helps you figure out where you made a mistake when you did, especially when dealing with automatons!
* Don’t stay blocked because you don’t know how to solve an exercise: make use of peer-learning! You can ask for help on Slack (42 or 42-AI) or Discord (42-AI) for example. 
* You are not allowed to use any library that makes the job for you, even the one included in your language’s standard library, unless explicitly stated otherwise. 
* For every exercises you may have to respect a given time and/or space complexity. These will be checked during peer review. 
  * The time complexity is calculated relative to the number of executed instructions 
  * The space complexity is calculated relative to the maximum amount of memory allocated simultaneously
  * Both have to be calculated against the size of the function’s input (a number, the length of a string, etc...) 
      
# Foreword

Regular expressions originated in 1951, when mathematician Stephen Cole Kleene described regular languages using his mathematical notation called regular events. These arose in theoretical computer science, in the subfields of automata theory (models of computation) and the description and classification of formal languages. Other early implementations of pattern matching include the SNOBOL language, which did not use regular expressions, but instead its own pattern matching constructs. 
Regular expressions entered popular use from 1968 in two uses: pattern matching in a text editor and lexical analysis in a compiler. Among the first appearances of regular expressions in program form was when Ken Thompson built Kleene's notation into the editor QED as a means to match patterns in text files. For speed, Thompson implemented regular expression matching by just-in-time compilation (JIT) to IBM 7094 code on the Compatible Time-Sharing System, an important early example of JIT compilation. He later added this capability to the Unix editor ed, which eventually led to the popular search tool grep's use of regular expressions ("grep" is a word derived from the command for regular expression searching in the ed editor: g/re/p meaning "Global search for Regular Expression and Print matching lines"). Around the same time when Thompson developed QED, a group of researchers including Douglas T. Ross implemented a tool based on regular expressions that is used for lexical analysis in compiler design.
Many variations of these original forms of regular expressions were used in Unix programs at Bell Labs in the 1970s, including vi, lex, sed, AWK, and expr, and in other programs such as Emacs. Regexes were subsequently adopted by a wide range of programs, with these early forms standardized in the POSIX.2 standard in 1992. 
In the 1980s the more complicated regexes arose in Perl, which originally derived from a regex library written by Henry Spencer (1986), who later wrote an implementation of Advanced Regular Expressions for Tcl. The Tcl library is a hybrid NFA/DFA implementation with improved performance characteristics. Software projects that have adopted Spencer's Tcl regular expression implementation include PostgreSQL. Perl later expanded on Spencer's original library to add many new features. Part of the effort in the design of Raku (formerly named Perl 6) is to improve Perl's regex integration, and to increase their scope and capabilities to allow the definition of parsing expression grammars. The result is a mini-language called Raku rules, which are used to define Raku grammar as well as provide a tool to programmers in the language. These rules maintain existing features of Perl 5.x regexes, but also allow BNF-style definition of a recursive descent parser via sub-rules. 
The use of regexes in structured information standards for document and database modeling started in the 1960s and expanded in the 1980s when industry standards like ISO SGML (precursored by ANSI "GCA 101-1983") consolidated. The kernel of the structure specification language standards consists of regexes. Its use is evident in the DTD element group syntax. 
Starting in 1997, Philip Hazel developed PCRE (Perl Compatible Regular Expressions), which attempts to closely mimic Perl's regex functionality and is used by many modern tools including PHP and Apache HTTP Server. 
Today, regexes are widely supported in programming languages, text processing programs (particularly lexers), advanced text editors, and some other programs. Regex support is part of the standard library of many programming languages, including Java and Python, and is built into the syntax of others, including Perl and ECMAScript. Implementations of regex functionality is often called a regex engine, and a number of libraries are available for reuse. In the late 2010s, several companies started to offer hardware, FPGA, GPU implementations of PCRE compatible regex engines that are faster compared to CPU implementations. 

# Mandatory part

Turn in directory: ft_regex
Allowed math functions: none

### Goal:
You must write the following functions that will allow you to interpret regular expressions and use them. Depending on the language that you use, you will implement or not the function that frees the memory that you allocate.
### Instructions:
Here are the functions to write:
`int ft_regcomp(regex_t *restrict preg, const char *restrict regex);`
`int ft_regexec(const regex_t *restrict preg, const char *restrict string, size_t nmatch, regmatch_t pmatch[restrict]);`
`int ft_regexec(const regex_t *restrict preg, const char *restrict string, size_t nmatch, regmatch_t pmatch[restrict]);`
`void ft_regfree(regex_t *preg);`
They are adapted from the standard C regex Library, you’ll find their man page on your favorite browser. Note that depending on the language that you use, the ft_regfree function may be omitted.
Your regex engine must implement at least the following symbols:

**Quantifiers:**
* *
* +
* ?

**Groups and Ranges:**
* .
* (a | b)
* (…)
* [abc]
* [^abc]
* [a-c]

**Character Classes:**
* \c
* \s
* \S
* \d
* \D
* \w
* \W
* \x
* \O

**Special Characters:**
* \n
* \r
* \t
* \v
* \f

**Escape Sequences:**
* \
