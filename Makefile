CC = gcc
CFLAGS = -Wall -O3 -std=gnu99 -ansi -pedantic -D_POSIX_C_SOURCE=199309L

# ALL

all : bin/main_briandais bin/briandais_shakespeare bin/briandais_shakespeare_threads bin/plot_tree bin/main_tries bin/plot_trie bin/swap_test

exec_main : bin/main_briandais
	bin/main_briandais

exec_shake : bin/briandais_shakespeare
	bin/briandais_shakespeare > log

exec_shake_threads : bin/briandais_shakespeare_threads
	bin/briandais_shakespeare_threads > log

exec_shake_tries : bin/tries_shakespeare
	bin/tries_shakespeare > log

exec_main_tries : bin/main_tries
	bin/main_tries

exec_plot : bin/plot_tree
	bin/plot_tree > plot_result_tree
	scripts/plot_tree.gp

exec_plot_trie : bin/plot_trie
	bin/plot_trie > plot_result_trie
	scripts/plot_trie.gp

exec_swap_test : bin/swap_test
	bin/swap_test
#DEBUG 

debug : CFLAGS += -DDEBUG -g
debug : all

# TOOLS

obj/tools.o : src/tools.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

# BRIANDAIS TREES

obj/main_briandais.o : src/main_briandais.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

bin/main_briandais : obj/main_briandais.o obj/tools.o obj/BRTree.o obj/HTrie.o
	${CC} ${CFLAGS}  -o $@ $^

obj/BRTree.o : src/Briandais/BRTree.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

obj/briandais_shakespeare.o : src/briandais_shakespeare.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include 

bin/briandais_shakespeare : obj/briandais_shakespeare.o obj/tools.o obj/BRTree.o obj/HTrie.o
	${CC} ${CFLAGS}  -o $@ $^ -lrt

obj/briandais_shakespeare_threads.o : src/briandais_shakespeare_threads.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include  

bin/briandais_shakespeare_threads : obj/briandais_shakespeare_threads.o obj/tools.o obj/BRTree.o obj/HTrie.o
	${CC} ${CFLAGS}  -o $@ $^ -lrt -lpthread

# HYBRID TRIES

obj/main_tries.o : src/main_tries.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

bin/main_tries : obj/main_tries.o obj/tools.o obj/HTrie.o obj/BRTree.o
	${CC} ${CFLAGS}  -o $@ $^

obj/HTrie.o : src/Hybrid_Tries/HTrie.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include

obj/tries_shakespeare.o : src/tries_shakespeare.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include 

bin/tries_shakespeare : obj/tries_shakespeare.o obj/tools.o obj/HTrie.o obj/BRTree.o 
	${CC} ${CFLAGS}  -o $@ $^ -lrt



# PLOT

obj/plot_tree.o : src/plot_tree.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include  

bin/plot_tree : obj/plot_tree.o obj/tools.o obj/BRTree.o obj/HTrie.o 
	${CC} ${CFLAGS}  -o $@ $^ 


obj/plot_trie.o : src/plot_trie.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include  

bin/plot_trie : obj/plot_trie.o obj/tools.o obj/HTrie.o obj/BRTree.o
	${CC} ${CFLAGS}  -o $@ $^ 

# SWAP STRUCTURES

obj/swap_test.o : src/swap_test.c
	${CC} ${CFLAGS} -o $@ -c $^ -I include  

bin/swap_test : obj/swap_test.o obj/HTrie.o obj/BRTree.o obj/tools.o
	${CC} ${CFLAGS}  -o $@ $^ 

# MISC.

clean :
	rm -f obj/* bin/* 

cleanall : clean
	rm -f *~ */*~ */*/*~ log briandais_search_results plot_result_tree plot_result_trie temp_file 


