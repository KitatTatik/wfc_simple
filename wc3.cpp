#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>

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
    std::string temp = "";
    std::ifstream fin("input.txt");
    auto begin = std::chrono::high_resolution_clock::now();
    while( (s = getsymbol(fin)) != temp ) ++words[s];
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std:: cout << "\t" << " Elapsed time - file read, map constructed, ns " << elapsed.count() << std::endl;
    begin = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<std::string, int>> ordered(words.begin(), words.end());
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std:: cout << "\t" << " Elapsed time - vector of pairs construction, ns " << elapsed.count() << std::endl;
    begin = std::chrono::high_resolution_clock::now();
    std::sort( ordered.begin(), ordered.end(), []( auto const& a, auto const& b ) { return a.second > b.second; });
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std:: cout << "\t" << " Elapsed time - qsort, ns " << elapsed.count() << std::endl;
    int i = 0;
    std::cout << "\n\n\t" << "Unique words -  " << ordered.size() << std::endl;
    for ( auto const& count : ordered ) {
        if ( i < 20 ) {
            std::cout << "\t" << count.first << " " << count.second << std::endl;
        }
        i++;
    }
}
