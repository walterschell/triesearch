#include "trie.h"
int to_baudot(char c)
{
    switch (c) 
    {
        case 'A': case 'a': return 0x3;
        case 'B': case 'b': return 0x19;
        case 'C': case 'c': return 0xe;
        case 'D': case 'd': return 0x9;
        case 'E': case 'e': return 0x1;
        case 'F': case 'f': return 0xd;
        case 'G': case 'g': return 0x1a;
        case 'H': case 'h': return 0x14;
        case 'I': case 'i': return 0x6;
        case 'J': case 'j': return 0xb;
        case 'K': case 'k': return 0xf; 
        case 'L': case 'l': return 0x12;
        case 'M': case 'm': return 0x1c;
        case 'N': case 'n': return 0xc;
        case 'O': case 'o': return 0x18;
        case 'P': case 'p': return 0x16;
        case 'Q': case 'q': return 0x17;
        case 'R': case 'r': return 0xa;
        case 'S': case 's': return 0x5;
        case 'T': case 't': return 0x10;
        case 'U': case 'u': return 0x7;
        case 'V': case 'v': return 0x1e;
        case 'W': case 'w': return 0x13;
        case 'X': case 'x': return 0x1d;
        case 'Y': case 'y': return 0x15;
        case 'Z': case 'z': return 0x11;
        case '0': return 0x16;
        case '1': return 0x17;
        case '2': return 0x13;
        case '3': return 0x3;
        case '4': return 0xa;
        case '5': return 0x10;
        case '6': return 0x15;
        case '7': return 0x7;
        case '8': return 0x6;
        case '9': return 0x18;
        case ' ': return 0x4;
        default:
            return 33;
    }
}
void Trie::add_word(const std::string &word)
{
    TrieNode *current = &root_node;
    int index = 0;
    while (index < word.size() -1)
    {
        int symbol = to_baudot(word[index]);
        if (symbol == 33) 
        {
            continue;
        }
        if (current->children[symbol] == NULL)
        {
            current->children[symbol] = new TrieNode;
        }
        current = current->children[symbol];
    }
    current->word = word;
}
int match_sequence(const string &sequence, uint64_t sequence_start_index, list<Match> matches, list<TrieNode *> &partial_matches, Trie &trie)
{
    int match_count = 0;
    uint64_t current_index = sequence_start_index;
    for (char c : sequence)
    {
        int symbol = to_baudot(c);
        if (symbol == 33)
        {
            partial_matches.clear();
        }
        else
        {
            for (auto current : partial_matches)
            {
                current = current->children[symbol];
                if (current != NULL && ! current->word.empty())
                {
                    matches.push_back(Match(current->word, current_index));
                    match_count++;
                }
            }
            TrieNode *current = trie.root_node.children[symbol];
            partial_matches.push_back(current);
            partial_matches.remove_if([](TrieNode *node){return (node == NULL);});
        }
        current_index++;
    }
    return match_count;
}
