#include <iostream>
#include <fstream>
#include <cstdint>
#include <arpa/inet.h>
#include <iomanip>      

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> ..." << std::endl;
        return 1;
    }

    uint32_t total_sum = 0;
    bool first = true;  

    for (int i = 1; i < argc; ++i) {
        std::ifstream file(argv[i], std::ios::binary);
        if (!file) {
            std::cerr << "Error: Cannot open file " << argv[i] << std::endl;
            return 1;
        }

        uint32_t value;
        while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            uint32_t host_value = ntohl(value); 

            
            if (!first) {
                std::cout << " + ";
            }
            first = false;

  
            std::cout << host_value << "(0x" 
                      << std::hex << std::setw(4) << std::setfill('0') 
                      << host_value << std::dec << ")";
            
            total_sum += host_value;
        }

        file.close();
    }


    std::cout << " = " << total_sum << "(0x"
              << std::hex << std::setw(4) << std::setfill('0') 
              << total_sum << std::dec << ")" << std::endl;

    return 0;
}

