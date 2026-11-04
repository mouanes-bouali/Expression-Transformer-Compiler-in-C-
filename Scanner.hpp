#include "Token.hpp"
#include <string>
#include <vector>
enum DfaState{
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

  std::vector<Token> Tokens;
  int _currentCharacter =-1;
  int _startLexime =-1 ;

  std::vector<std::string> _possibleFunctionNames={"add","sub","tern","mul","div","mod","pow"};
  DfaState state= DfaState::START_STATE;

  bool atTheTextEnd(std::string CodeText) {
    return _currentCharacter >= _codeText.length();
  }

  char getCurrentCharacterInText(int CurrentCharacter) {
    return _codeText[CurrentCharacter];
  }
  void addToken(TokenType type, std::string lexime) {
   Token token=Token(type,lexime) ;
    Tokens.push_back(token);
 }

  char advance()
  {
    return getCurrentCharacterInText(_currentCharacter++);
  }

  void scanToken()
  {
    char character= advance();
    //if current character is a space  then consumeSpaces
    switch (character) {
      case ' ': 
                 //procceddSpaces
      case '/': //peeknextcharacter if next character * than  proccedRemoveComment() 
    
    }



  }

  void scanTokens(){
    while (!atTheTextEnd(_codeText)) {
      _startLexime=_currentCharacter;
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