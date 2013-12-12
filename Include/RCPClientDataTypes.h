#pragma once

#include <vector>
#include <list>
#include <sstream>

namespace RCP
{

template <class T> ::std::string ConvertToString(T value)
{
	::std::ostringstream valueStream;
	valueStream << value;
	return valueStream.str();
}

template <class T> ::std::string ConvertToString(::std::list<T> values)
{
	::std::ostringstream valueStream;
	valueStream << "[";
	for(auto it = values.begin(); it != values.end(); it++)
	{
		if(it != values.begin())
			valueStream << ",";
		valueStream << ConvertToString<T>(*it);
	}
	valueStream << "]";
	return valueStream.str();
}

template <class T> ::std::string ConvertToString(::std::vector<T> values)
{
	::std::ostringstream valueStream;
	valueStream << "[";
	for(auto it = values.begin(); it != values.end(); it++)
	{
		if(it != values.begin())
			valueStream << ",";
		valueStream << ConvertToString<T>(*it);
	}
	valueStream << "]";
	return valueStream.str();
}

template <class T> void RCPClient::Send(T value)
{
    ::std::ostringstream valueStream;
    valueStream << "{\"_Value\":";
    valueStream << ConvertToString(value);
    valueStream << "}";
	Set("DataType", "JSON");
    RCPClient::Send(valueStream.str().c_str());
}

}