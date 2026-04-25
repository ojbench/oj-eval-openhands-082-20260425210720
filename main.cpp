

#include <iostream>
#include <string>
#include "src.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    LinkedHashMap map(n, false); // Initialize with traverseByIndex as default
    
    for(int i = 0; i < m; i++) {
        std::string op;
        std::cin >> op;
        
        if(op == "INSERT") {
            int key;
            std::string value;
            std::cin >> key >> value;
            map.insert(key, value);
        }
        else if(op == "REMOVE") {
            int key;
            std::string value;
            std::cin >> key >> value;
            map.remove(key, value);
        }
        else if(op == "ASK") {
            int key;
            std::cin >> key;
            std::vector<std::string> result = map.ask(key);
            for(size_t j = 0; j < result.size(); j++) {
                if(j > 0) std::cout << " ";
                std::cout << result[j];
            }
            std::cout << std::endl;
        }
        else if(op == "TRAVERSE") {
            std::string type;
            std::cin >> type;
            if(type == "TIME") {
                map.forEachMethod = traverseByTime;
            } else if(type == "INDEX") {
                map.forEachMethod = traverseByIndex;
            }
            
            std::vector<Data> result = map.forEach();
            for(size_t j = 0; j < result.size(); j++) {
                if(j > 0) std::cout << " ";
                std::cout << result[j].key << ":" << result[j].value;
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}

