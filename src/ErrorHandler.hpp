#include <cstdio>
#include <string>
class ErrorHandler {
public:
   ErrorHandler()=default;

 void printCharacterUndefined(char character){
    printf("character undefined %c",character);
 }
 void printNumberFormatWrong(){
    printf("Number format wrong");
 }
 void printStringNotDefined(std::string string){
   printf("string undefined %s",string.c_str());
 }
 void LexicalerrorHappened()
 {
    lexicalSyntaxIssueFound=true;
 }
 bool isTherAnLexicalError()
 {
    return lexicalSyntaxIssueFound;
 }



private:
    bool lexicalSyntaxIssueFound=false;
};