#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Token 
{
    public:
        Token(const std::string& lexeme):lexeme(lexeme){};

        friend std::ostream& operator<<(std::ostream& os, const Token& token)
        {
            os << token.lexeme;
            return os;
        }

    private:
        std::string lexeme;
};

class Scanner
{
    public:
        Scanner(const std::string& source) : source(source) {}

        std::vector<Token> scan_tokens()
        {
            std::istringstream ss(source);
            std::string token;

            while(ss >> token)
                tokens.push_back(token);

            return tokens;
        }

    private:
        std::string source;
        std::vector<Token> tokens;
};

class Lox 
{
    public:
        int main(int argc, char **argsv) 
        {
            if (argc > 2)
            {
                std::cout << "Usage: ./slow [script]" << std::endl;
                std::exit(1);
            }
            else if (argc == 2)
            {
                run_file(argsv[1]);
            } 
            else 
            {
                run_prompt();
            }

            return 0;
        }

    private:
        void run_file(const std::string& path) 
        {
            std::ifstream f;
            std::stringstream buf;
            std::string content;

            f.open(path, std::ios::binary);

            if (!f.is_open())
            {
                std::perror("Error opening the file");
                std::exit(1);
            }

            buf << f.rdbuf();
            content = buf.str();

            run(content);

            f.close();
        }

        void run_prompt()
        {
            std::string line;

            while(true)
            {
                std::cout << "> ";

                if (!std::getline(std::cin, line) || line.empty())
                {
                    break;
                }

                run(line);
            }
        }

        void run(const std::string& source)
        {
            Scanner scanner(source);
            std::vector<Token> tokens = scanner.scan_tokens();
            
            for (const auto& token : tokens)
                std::cout << token << std::endl;
        }
};

int main(int argc, char **argsv)
{
    Lox m;
    m.main(argc, argsv);
}

