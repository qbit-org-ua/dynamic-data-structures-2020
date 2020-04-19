all: trie trie_advanced

trie: trie.cpp
	g++ -Wall -Wextra -std=c++17 -O3 -lncurses trie.cpp -otrie

trie_advanced: trie_advanced.cpp
	g++ -Wall -Wextra -std=c++17 -O3 -lncurses trie_advanced.cpp -otrie_advanced

trie_debug: trie.cpp
	g++ -Wall -Wextra -std=c++17 -fsanitize=address -g -lncurses trie.cpp -otrie_debug

trie_advanced_debug: trie_advanced.cpp
	g++ -Wall -Wextra -std=c++17 -fsanitize=address -g -lncurses trie_advanced.cpp -otrie_advanced_debug

clean:
	$(RM) trie trie_advanced trie_debug trie_advanced_debug
