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
void RCPClient::Send(T value)
{
    Set("DataType", "JSON");

    ::std::ostringstream valueStream;
    valueStream << "{\"_Value\":";
    valueStream << value;
    valueStream << "}";

    auto str = valueStream.str();
    PreprareAndSendMessage(str.c_str(), str.length());
}

}