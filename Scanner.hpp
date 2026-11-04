#include "Token.hpp"
#include <string>
#include <unordered_map>
#include <vector>
enum DfaState {
  START_STATE,
  SIGNED_STATE,
  SIGNED_DIGIT_SEQUENCE_STATE,
  EXPONENT_STATE,
  EXPONENT_DIGIT_SEQUENCE_STATE,
  FRACTION_STATE,
  FRACTION_DIGIT_SEQUENCE_STATE,
  ALPHABET_STATE,

};

class Scanner {
private:
  std::string _codeText;

  std::vector<Token> _tokens;
  int _currentCharacter = -1;
  int _startLexime = -1;

  std::vector<std::string> _possibleFunctionNames = {
      "add", "sub", "tern", "mul", "div", "mod", "pow"};
  DfaState state = DfaState::START_STATE;
  
  const std::unordered_map<std::string, TokenType> _keyWordsMap = {
      {"add", TokenType::ADD},{"sub", TokenType::SUB}, {"pow", TokenType::POW}, {"mul", TokenType::MUL},
      {"div", TokenType::DIV},{"tern", TokenType::TERN}
  };
  bool atTheTextEnd(std::string CodeText) {
    return _currentCharacter >= _codeText.length();
  }
  bool isLowerCaseAlphabet(char character) { return character >= 'a' && character <= 'z'; }
  bool isKeyWord(std::string lexime){
    auto stringFound= _keyWordsMap.find(lexime);
    return stringFound !=_keyWordsMap.end();
  }
  char getCurrentCharacterInText(int CurrentCharacter) {
    return _codeText[CurrentCharacter];
  }
  void addToken(TokenType type, std::string lexime) {
    Token token = Token(type, lexime);
    _tokens.push_back(token);
  }
    std::string subtructStringFromText(int startString, int endString,std::string text)
    {
      return text.substr(startString,endString) ;
    }

  char advance() { return getCurrentCharacterInText(_currentCharacter++); }
  char peekNextCharacter() { return _codeText[_currentCharacter + 1]; }
  void skipComment() {
    while (getCurrentCharacterInText(_currentCharacter) != '*' &&
           peekNextCharacter() != '/') {

      _currentCharacter++;
    }
    _currentCharacter += 2;
  }
  void scanString() {
    char alphabet = advance();
    while (isLowerCaseAlphabet(alphabet)) {
      advance();
    }
    _currentCharacter--;
  }
  void scanToken() {
    char character = advance();
    // if current character is a space  then consumeSpaces

    if (character == ' ') {
      advance();
    }
    if (peekNextCharacter() == '*') {
      _currentCharacter += 2;
      skipComment();
    }
    if (character == '(') {
      addToken(TokenType::LEFT_PAREN, "(");
    }
    if (character == '(') {
      addToken(TokenType::RIGHT_PAREN, ")");
    }
    if (isLowerCaseAlphabet(character)) {

      
      scanString();
     std::string lexime= subtructStringFromText(_startLexime,_currentCharacter,_codeText);
     if (isKeyWord(lexime)) {
      auto keyWord=_keyWordsMap.find(lexime);
      addToken(keyWord->second ,  lexime);
     } 
     
    }
  }

  void scanTokens() {
    while (!atTheTextEnd(_codeText)) {
      _startLexime = _currentCharacter;
      scanToken();
    }
  }

public:
  Scanner(std::string CodeText)

  {
    _codeText = CodeText;
  };
  Scanner(const Scanner &other);
  Scanner &operator=(const Scanner &other);
  Scanner(Scanner &&other) noexcept;
  Scanner &operator=(Scanner &&other) noexcept;
  ~Scanner();
};