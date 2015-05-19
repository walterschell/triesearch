#include "trie.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
int main(int argc, char *argv[])
{
    vector<int> seq1;
    vector<int> seq2;
    for (long i = 0; i < 100000; i++)
    {
        seq1.push_back(rand() % 32);
        seq2.push_back(rand() % 32);
    }
    std::ifstream in("/usr/share/dict/words");
    Trie trie;
    while (in)
    {
        string foo;
        in >> foo;
        std::cout << "Adding " << foo << "\n";
        trie.add_word(foo);
    }
    std::cout << "Trie built\n";
    list<Match> matches;
    list<TrieNode *> partial_matches;
    match_sequence(seq1, 0, matches, partial_matches, trie);
    std::cout << "First seq had " << matches.size() << " matches\n";
    match_sequence(seq1, seq1.size(), matches, partial_matches, trie);
    std::cout << "After continuation " << matches.size() << " matches\n";
    for (auto match: matches)
    {
        std::cout << "Found this word: " << match << std::endl;
    }
    
    
}
