#include <string>
#include <iostream>

enum TokenType{
 LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,QST_MRK,PERCE,UP_ARR,
  

  // Literals.
  IDENTIFIER, STRING, NUMBER,EXPO,

  // Keywords.
  ADD,SUB,MUL,DIV,MOD,POW,TERN


};


class Token {
public:
    Token(TokenType type, std::string lexeme)
    {
        _type=type;
        _lexeme=lexeme;
    }
    Token(const Token& other);
    Token& operator=(const Token& other);
    Token(Token&& other) noexcept;
    Token& operator=(Token&& other) noexcept;
    ~Token();

private:
TokenType _type;
std::string _lexeme;

};

