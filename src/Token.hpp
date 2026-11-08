#include <iostream>
#include <string>


enum TokenType_


{
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  QST_MRK,
  PERCE,
  UP_ARR,

 
  IDENTIFIER,
  STRING,
  NUMBER,
  EXPO,

  // KeyWords.
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  POW,
  TERN

};

class Token {

private:
  TokenType_ _type;
  std::string _lexeme;

public:
  Token(TokenType_ type, std::string lexeme) {
    _type = type;
    _lexeme = lexeme;
  }
  Token(const Token &other) = default;
  Token &operator=(const Token &other) = default;
  Token(Token &&other) noexcept = default;
  Token &operator=(Token &&other) noexcept = default;
  ~Token() = default;

std::string   getLexime()
{
    return _lexeme;
}
};
