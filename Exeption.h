#pragma once
#include <string>
class Exception
{
private:
	std::string m_error;
public:
	Exception(const std::string& str) : m_error(str) { }
	~Exception() { }

	std::string getError() const { return m_error; }
};

