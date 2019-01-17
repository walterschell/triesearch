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
            return 32;
    }
}
char to_char(int baudot)
{
	switch(baudot)
	{
	case 0x3: return 'a';
	case 0x19: return 'b';
	case 0xe: return 'c';
	case 0x9: return 'd';
	case 0x1: return 'e';
	case 0xd: return 'f';
	case 0x1a: return 'g';
	case 0x14: return 'h';
	case 0x6: return 'i';
	case 0xb: return 'j';
	case 0xf: return 'k';
	case 0x12: return 'l';
	case 0x1c: return 'm';
	case 0xc: return 'n';
	case 0x18: return 'o';
	case 0x16: return 'p';
	case 0x17: return 'q';
	case 0xa: return 'r';
	case 0x5: return 's';
	case 0x10: return 't';
	case 0x7: return 'u';
	case 0x1e: return 'v';
	case 0x13: return 'w';
	case 0x1d: return 'x';
	case 0x15: return 'y';
	case 0x11: return 'z';
    case 0x4: return ' ';
    default:
        return '*';

	}
}
string to_string(vector<int> digits)
{
	string result;
	for (int digit : digits)
	{
		result += to_char(digit);
	}
	return result;
}
string to_string(vector<int> digits, int max)
{
	string result;
	for (int digit : digits)
	{
		result += to_char(digit);
		max--;
		if (max <= 0)
		{
			break;
		}
	}
	return result;

}
vector<int> to_vector(string word)
{
	vector<int> result;
	for (char c : word)
	{
		result.push_back(to_baudot(c));
	}
	return result;
}

TrieNode::TrieNode(const string &init_word)
{
    //std::cout << " Initializing trie node\n";
    word = init_word;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        children[i] = NULL;
    }
}
void Trie::add_word(const std::string &word)
{
    TrieNode *current = &root_node;
    int index = 0;
    while (index < word.size())
    {
        int symbol = to_baudot(word[index]);
        index++;
        if (symbol == 32) 
        {
           std::cout << "Ignoring: " << word << std::endl;
            return;
        }
        if (current->children[symbol] == NULL)
        {
            current->children[symbol] = new TrieNode;
        }
        current = current->children[symbol];
    }
    current->word = word;
}

int match_sequence(const vector<int> &sequence, uint64_t sequence_start_index, 
                    list<Match> &matches, list<TrieNode *> &partial_matches, 
                    Trie &trie, int min_length)
{
    int match_count = 0;
    uint64_t current_index = sequence_start_index;
    unsigned long count = 0;
    for (int symbol : sequence)
    {
    	if (symbol >= 32)
        {
            std::cout << "Clearing partial matches\n";
        	partial_matches.clear();
        }
        else
        {
            std::list<TrieNode *> next_partials;

            for (auto current = partial_matches.begin(); current != partial_matches.end();)
            {
                auto child = (*current)->children[symbol];
                if (child != NULL && ! child->word.empty() && child->word.size() >= min_length)
                {
                    matches.push_back(Match(child->word, current_index - child->word.size() + 1));
                    std::cout << "Found: " << child->word << "\n";
                    match_count++;
                }
                if (child != NULL)
                {
                	next_partials.push_back(child);
                }
            	current++;

            }
            partial_matches.clear();
            for (auto current : next_partials)
            {
            	partial_matches.push_back(current);
            }
            TrieNode *current = trie.root_node.children[symbol];
            if (NULL != current)
            {
            	partial_matches.push_back(current);
            }
        }
        current_index++;
        count++;
        if (count % 1000 == 0)
        {
            std::cout << "Matched " << count << " entries\n";
        }
    }
    return match_count;
}
std::ostream & operator<<(std::ostream &lhs, const Match &rhs)
{
    return lhs << ">" << rhs.word << "< index: " << rhs.index;
}
