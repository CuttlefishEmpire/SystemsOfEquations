#include "TokenParser.hpp"
#include "../Functions/FunctionModule.hpp"
#include <cstring>
#include <sstream>

deque<string> unparsedInputToStringList(string input)
{
    char delimiter = ' ';
    stringstream inputStream(input);

    string segment;
    deque<string> result;

    while (getline(inputStream, segment, delimiter))
    {
        result.push_back(segment);

    }

    return result;
}

TokenType stringToTokenType(string single)
{
    switch (single.front())
    {
        case '0': case '1': case '2':
        case '3': case '4': case '5':
        case '6': case '7': case '8':
        case '9':
            return TokenType::Literal;
        default:
            break;
    }

    if (single == "(")
    {
        return TokenType::LeftParenthesis;
    }
    else if (single == ")")
    {
        return TokenType::RightParenthesis;
    }
    else if (single.front() == '-' && single.length() > 1)
    {
        return TokenType::Literal;
    }

    return TokenType::Function;
}

Token tokenizeSingle(string single)
{
    TokenType tokenType = stringToTokenType(single);
    Function function = stringToFunction(single);
    return Token(single, tokenType, function);
}

deque<Token> stringListToInfixTokenList(deque<string> stringList)
{
    deque<Token> result;
    for (string single : stringList)
    {
        result.push_back(tokenizeSingle(single));
    }
    return result;
}

deque<Token> parse(string input)
{
    return stringListToInfixTokenList(unparsedInputToStringList(input));
}
