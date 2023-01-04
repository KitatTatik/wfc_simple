#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

std::string getsymbol( std::istream &in ) {
    char c;
    std::string result = "";
    c = in.get();
    while( !std::isalpha(c) && !in.eof() ) {
        c = in.get();
    }
    while( std::isalpha(c) ) {
        result.push_back( std::tolower(c) );
        c = in.get();
    }
    return result;
}

int main() {
    std::unordered_map<std::string,int> words;
    std::string s;
    std::string empty = "";
    while( (s = getsymbol(std::cin)) != empty ) ++words[s];
    std::vector<std::pair<std::string, int>> ordered(words.begin(), words.end());
    std::sort( ordered.begin(), ordered.end(), []( auto const& a, auto const& b ) { return a.second > b.second; });
    int i = 0;
    std::cout << "\n\n\t" << "Unique words -  " << ordered.size() << "\n";
    for ( auto const& count : ordered ) {
        if ( i < 20 ) {
            std::cout << "\t" << count.first << " " << count.second << "\n";
        }
        i++;
    }
}
