CC = gcc
CFLAGS = -Wall -O3

# ALL

all : bin/main_briandais bin/briandais_shakespeare bin/briandais_shakespeare_threads bin/plot_tree

exec_main : bin/main_briandais
	bin/main_briandais

exec_shake : bin/briandais_shakespeare
	bin/briandais_shakespeare > log

exec_shake_threads : bin/briandais_shakespeare_threads
	bin/briandais_shakespeare_threads > log

exec_plot : bin/plot_tree
	bin/plot_tree > plot_result
#DEBUG 

debug : CFLAGS += -DDEBUG -g
debug : all

# TOOLS

obj/tools.o : src/tools.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

# BRIANDAIS TREES

obj/main_briandais.o : src/main_briandais.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

bin/main_briandais : obj/main_briandais.o obj/tools.o obj/BRTree.o
	${CC} ${CFLAGS}  -o $@ $^

shake : bin/briandais_shakespeare

main : bin/main_briandais

shake_threads : bin/briandais_shakespeare_threads


obj/BRTree.o : src/Briandais/BRTree.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

obj/briandais_shakespeare.o : src/briandais_shakespeare.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include 

bin/briandais_shakespeare : obj/briandais_shakespeare.o obj/tools.o obj/BRTree.o
	${CC} ${CFLAGS}  -o $@ $^ -lrt


obj/briandais_shakespeare_threads.o : src/briandais_shakespeare_threads.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include  

bin/briandais_shakespeare_threads : obj/briandais_shakespeare_threads.o obj/tools.o obj/BRTree.o
	${CC} ${CFLAGS}  -o $@ $^ -lrt -lpthread



obj/plot_tree.o : src/plot_tree.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include  

bin/plot_tree : obj/plot_tree.o obj/tools.o obj/BRTree.o
	${CC} ${CFLAGS}  -o $@ $^ 




# MISC.

clean :
	rm -f obj/* bin/* 

cleanall : clean
	rm -f *~ */*~ */*/*~ log 


