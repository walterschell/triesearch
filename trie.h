#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <cstdint>
#include <list>
#include <vector>
#include <iostream>
using std::list;
using std::string;
using std::vector;

const int ALPHABET_SIZE = 32;
int to_baudot(char c);

struct TrieNode
{
    TrieNode(const string &init_word="");
    string word;
    TrieNode *children[ALPHABET_SIZE];
};
struct Trie
{
        void add_word(const std::string &word);
        TrieNode root_node;
};
struct Match
{
    string word;
    uint64_t index;
    Match(const string &init_word, uint64_t init_index) : word(init_word), index(init_index) {}
    friend std::ostream & operator<<(std::ostream &lhs, const Match &rhs);
};
int match_sequence(const vector<int> &sequence, uint64_t sequence_start_index, list<Match> &matches, list<TrieNode *> &partial_matches, Trie &trie, int min_length = 4);
#endif
