all: pr17

pr17: lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -o pr17

lex.yy.c: lex.l
	lex lex.l

y.tab.c: yac.y
	yacc -d yac.y

clean:
	rm -rf *.o
