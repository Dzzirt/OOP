#include "stdafx.h"
#include "ExpressionConverter.h"
using namespace std;

std::vector<char> CExpressionConverter::operations = {'/', '+', '-', '*', '(', ')'};

// ParseExprSum
void CExpressionConverter::HandlePlusAndMinus(std::string & output, size_t & index)
{
	HandleMultAndDiv(output, index);
	while (m_expression[index] == '+' || m_expression[index] == '-') {
		char temp = m_expression[index];
		index++;
		HandleMultAndDiv(output, index);
		output += temp;
		output += " ";
	}
}

// ParseExprMul
void CExpressionConverter::HandleMultAndDiv(std::string & output, size_t & index)
{
	HandleVariables(output, index);
	while (m_expression[index] == '*' || m_expression[index] == '/') {
		char temp = m_expression[index];
		index++;
		HandleVariables(output, index);
		output += temp;
		output += " ";
	}
}

// ParseAtom
void CExpressionConverter::HandleVariables(std::string & output, size_t & index)
{
	if (m_expression[index] == '(') {
		index++;
		HandlePlusAndMinus(output, index);
		if (m_expression[index] != ')') {
			throw std::invalid_argument("Error: wrong number of brackets");
		}
		else
		{
			index++;
		};
	}
	else 
	{
		// while isdigit() -> while in '0'..'9'
		// boost::any_of("0123456789.,")
		while (std::find(operations.begin(), operations.end(), m_expression[index]) == operations.end()
			&& index < m_expression.size())
		{
			output += m_expression[index];
			index++;
		}
		output += " ";
	}	
}

std::string CExpressionConverter::ToSuffixNotation(const std::string &expression)
{
	m_expression = expression;
	m_expIndex = 0;
	string output;
	m_expression.erase(remove_if(m_expression.begin(), m_expression.end(), isspace), m_expression.end());
	HandlePlusAndMinus(output, m_expIndex);
	return output;
}