all:
	g++ -std=c++17 main.cpp splay_tree.cpp database_handler.cpp -lsqlite3 -o cache_project
