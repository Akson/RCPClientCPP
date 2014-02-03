#pragma once

#include <vector>
#include <list>
#include <sstream>
#include <array>
namespace RCP
{

template<class T, ::std::size_t N>
inline ::std::ostream &operator<<(::std::ostream &out, const ::std::array<T, N> &values)
{
    out << "[";
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            out << ", ";
        out << *it;
    }
    out << "]";
    return out;
}

template<class T>
inline ::std::ostream &operator<<(::std::ostream &out, const ::std::vector<T> &values)
{
    out << "[";
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            out << ", ";
        out << *it;
    }
    out << "]";
    return out;
}

template<class T>
inline ::std::ostream &operator<<(::std::ostream &out, const ::std::list<T> &values)
{
    out << "[";
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            out << ", ";
        out << *it;
    }
    out << "]";
    return out;
}

template <class T>
::std::string ConvertToString(T value)
{
    ::std::ostringstream valueStream;
    valueStream << value;
    return valueStream.str();
}

template <class T>
void RCPClient::Send(T value)
{
    ::std::ostringstream valueStream;
    valueStream << "{\"_Value\":\"";
    valueStream << value;
    valueStream << "\"}";
    Set("DataType", "JSON");
    RCPClient::Send(valueStream.str().c_str());
}

}