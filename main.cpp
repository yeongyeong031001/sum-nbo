#include <iostream>
#include <cstdio>
#include <cstdint>
#include <iomanip>

uint32_t my_ntohl(uint32_t netlong) {
    return ((netlong & 0xFF000000) >> 24) |
           ((netlong & 0x00FF0000) >> 8)  |
           ((netlong & 0x0000FF00) << 8)  |
           ((netlong & 0x000000FF) << 24);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> ..." << std::endl;
        return 1;
    }

    uint32_t total_sum = 0;
    bool first = true;

    for (int i = 1; i < argc; ++i) {
        FILE* file = fopen(argv[i], "rb");
        if (!file) {
            std::cerr << "Error: Cannot open file " << argv[i] << std::endl;
            return 1;
        }

 
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        if (file_size < sizeof(uint32_t)) {
            std::cerr << "Error: File " << argv[i] << " is too small (less than 4 bytes)" << std::endl;
            fclose(file);
            return 1;
        }

        uint32_t value;
        bool has_data = false;
        while (fread(&value, sizeof(value), 1, file) == 1) {
            has_data = true;
            uint32_t host_value = my_ntohl(value);

            if (!first) {
                std::cout << " + ";
            }
            first = false;

            std::cout << host_value << "(0x"
                      << std::hex << std::setw(4) << std::setfill('0')
                      << host_value << std::dec << ")";

            total_sum += host_value;
        }

        if (!has_data) {
            std::cerr << "Error: File " << argv[i] << " contains no valid 4-byte integers" << std::endl;
            fclose(file);
            return 1;
        }

        fclose(file);
    }

    std::cout << " = " << total_sum << "(0x"
              << std::hex << std::setw(4) << std::setfill('0')
              << total_sum << std::dec << ")" << std::endl;

    return 0;
}
}


