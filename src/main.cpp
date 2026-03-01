#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello from Lex compiler v0.1.0\n";

    if (argc > 1) {
        std::cout << "Input file: " << argv[1] << "\n";
    }

    return 0;
}
