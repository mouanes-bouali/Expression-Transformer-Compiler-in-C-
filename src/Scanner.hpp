#include "Token.hpp"
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>
#include "ErrorHandler.hpp"


class Scanner {
private:
  ErrorHandler _errorHandler;
  std::string _codeText;
  std::vector<Token> _tokens;

  
  int _currentCharacterIndex = -1;
  int _startLeximeIndex = -1;
  bool inFinalState=false;

  const std::unordered_map<std::string, TokenType_> _keyWordsMap = {
      {"add", TokenType_::ADD}, {"sub", TokenType_::SUB},
      {"pow", TokenType_::POW}, {"mul", TokenType_::MUL},
      {"div", TokenType_::DIV}, {"tern", TokenType_::TERN}};





  bool atTheTextEnd() {
    return _currentCharacterIndex >= _codeText.length();
  }




  bool isLowerCaseAlphabet(char character) {
    return character >= 'a' && character <= 'z';
  }
  bool isKeyWord(std::string lexime) {
    auto stringFound = _keyWordsMap.find(lexime);
    return stringFound != _keyWordsMap.end();
  }
  bool isSign(char charcter) { return charcter == '=' || charcter == '+'; }
  bool isNumber(char character) { return character >= '0' && character <= '9'; }
  bool isDot(char character) { return character == '.'; }
  bool isExponent(char character) { return character == 'e'; }




  

  void setCodeText(std::string text){
    _codeText=text;
  }
  void addToken(TokenType_ type, std::string lexime) {
    Token token = Token(type, lexime);
    _tokens.push_back(token);
  }
  
  std::string extractStringFromText(int startString, int endString,
                                     std::string text) {
    return text.substr(startString, endString);
  }

  char advance() { return getCurrentCharacterInText(_currentCharacterIndex++); }

  char peekNextCharacter() { return _codeText[_currentCharacterIndex + 1]; }
  

  void skipComment() {
    while (getCurrentCharacterInText(_currentCharacterIndex) != '*' &&
           peekNextCharacter() != '/') {

      _currentCharacterIndex++;
    }
    _currentCharacterIndex += 2;
  }
   void skipSpace() {
    while (getCurrentCharacterInText(_currentCharacterIndex)==' '){
       _currentCharacterIndex++;
    }
   }
  void scanString() {
    char alphabet = advance();
    while (isLowerCaseAlphabet(alphabet)) {
      
      alphabet=advance();
    }

    _currentCharacterIndex--;
  }
  void scanExponent() {}

  void scanNumberAfterSign() {
    
    char number = advance();
    if (isNumber(number)) {
        inFinalState=true;
    }
    while (isNumber(number)) {
      
      number = advance();
    }
    char character = number;
    if (isDot(character)) {
      inFinalState=false;
      scanNumberAfterDot();
    }
    if (isExponent(character)) {
      
    }
  }
  void scanNumberAfterDot() {
    char number = advance();
    if (isNumber(number)) {
      inFinalState=true;
    }
    while (isNumber(number)) {
      number = advance();
    }


    char character = number;
    if (isExponent(character)) {
      inFinalState=true;
      scanNumberAfterExponent();
    }
  }
  void scanNumberAfterExponent() {
    char character = advance();
    if (isSign(character)) {
        character = advance();
    }
    while (isNumber(character)) {
      character = advance();
    }
  }
  void scanToken() {
    char character = advance();
    // if current character is a space  then consumeSpaces
    switch (character) {
      case ' ':  skipSpace(); break;
      case '/':  if (getCurrentCharacterInText(_currentCharacterIndex) == '*') {   _currentCharacterIndex += 2; skipComment();} break;

      case '(': addToken(TokenType_::LEFT_PAREN, "("); break;
     case ')': addToken(TokenType_::RIGHT_PAREN, ")");break;
      
      default:
            if (isNumber(character)) {
             scanNumberAfterSign();
             if (inFinalState==false) {
                    //throw expection No number after DOt non defined;
                    _errorHandler.printNumberFormatWrong();
                    _errorHandler.isTherAnLexicalError();
                   }else {
                   addToken(NUMBER, extractStringFromText(_startLeximeIndex, _currentCharacterIndex, _codeText));
                   }
                   
            }else if (isSign(character) ) {
                    inFinalState=false;
                    skipSpace();
                   scanNumberAfterSign();
                   if (inFinalState==false) {
                    //throw expection No number after DOt non defined;
                    _errorHandler.printNumberFormatWrong();
                    _errorHandler.isTherAnLexicalError();
                   }
                    addToken(NUMBER,  extractStringFromText(_startLeximeIndex, _currentCharacterIndex, _codeText));

           }else if (isLowerCaseAlphabet(character)){

               

                  scanString();
                  std::string lexime = extractStringFromText(_startLeximeIndex, _currentCharacterIndex, _codeText);
                  
                 if (isKeyWord(lexime)) {
                       auto keyWord = _keyWordsMap.find(lexime);
                      addToken(keyWord->second, lexime);
                
                    }else {
                       //throw expection string not defined
                       _errorHandler.LexicalerrorHappened();
                       _errorHandler.printStringNotDefined(lexime);
                    }
           }else {
            //throw expection charcter not defined
            _errorHandler.printCharacterUndefined(character);
            _errorHandler.LexicalerrorHappened();
           }
    }
   
   
   
  }

 

public:
  Scanner(std::string CodeText,ErrorHandler errorHundler)

  {_errorHandler=errorHundler;
    _codeText = CodeText;
  };
  Scanner(const Scanner &other);
  Scanner &operator=(const Scanner &other);
  Scanner(Scanner &&other) noexcept;
  Scanner &operator=(Scanner &&other) noexcept;
  ~Scanner();
char getCurrentCharacterInText(int CurrentCharacter) {
    return _codeText[CurrentCharacter];
  }
 
  std::vector<Token> getTokens(){
    return _tokens;
  }

   void scanTokens() {
    _currentCharacterIndex=0;
    while (!atTheTextEnd()) {
      _startLeximeIndex = _currentCharacterIndex;
      scanToken();
    }
  }
};