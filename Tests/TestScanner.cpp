#include <cstdio>
#define CATCH_CONFIG_MAIN
#include "../src/Scanner.hpp"
#include "catch.hpp"


#include <string>
#include <vector>

TEST_CASE("Test: Scaning function add") {

  std::string addString = "add  g";
  auto Scanner = new class Scanner(addString, ErrorHandler());
  Scanner->scanTokens();
  std::vector<Token> tokens = Scanner->getTokens();
  printf("%s\n", tokens[0].getLexime().c_str());
  REQUIRE("add" == tokens[0].getLexime());
}
TEST_CASE("Test: Scaning function sub") {
  std::string addString = "sub";
  auto Scanner = new class Scanner(addString, ErrorHandler());
  Scanner->scanTokens();
  std::vector<Token> tokens = Scanner->getTokens();
  printf("%s\n", tokens[0].getLexime().c_str());
  REQUIRE(addString == tokens[0].getLexime());
}
TEST_CASE("Test: Scaning function with a number 123") {
  std::string addString = "+ 123.e1";
  auto Scanner = new class Scanner(addString, ErrorHandler());
  Scanner->scanTokens();
  std::vector<Token> tokens = Scanner->getTokens();
  printf("%s\n", tokens[0].getLexime().c_str());
  REQUIRE(addString == tokens[0].getLexime());
}
TEST_CASE("Test: Scaning function with a comment") {
  std::string addString = "/*hi add subb hajdk */";
  auto Scanner = new class Scanner(addString, ErrorHandler());
  Scanner->scanTokens();
  std::vector<Token> tokens = Scanner->getTokens();

  REQUIRE(tokens.empty());
}

TEST_CASE("Test: Scaning function sub and add") {
  std::string addString = "sub/*ajdjak adkwadka*/ add";
  auto Scanner = new class Scanner(addString, ErrorHandler());
  Scanner->scanTokens();
  std::vector<Token> tokens = Scanner->getTokens();
  printf("%s\n", tokens[0].getLexime().c_str());
  REQUIRE("sub" == tokens[0].getLexime());
  REQUIRE("add" == tokens[1].getLexime());
}