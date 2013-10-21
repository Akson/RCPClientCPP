#pragma once


#include <sstream>


template <class T> void RCPClient::Send(T value, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
    std::ostringstream valueStream;
    valueStream << "{\"Value\":";
    valueStream << value;
    valueStream << "}";
    RCPClient::Send(
        valueStream.str().c_str(),
        substreamName,
        commands ? (std::string("ParseJson();") + std::string(commands)).c_str() : "ParseJson()"
    );
}

template void RCPClient::Send(char value, const char *substreamName, const char *commands);
template void RCPClient::Send(short value, const char *substreamName, const char *commands);
template void RCPClient::Send(int value, const char *substreamName, const char *commands);
template void RCPClient::Send(long value, const char *substreamName, const char *commands);
template void RCPClient::Send(long long value, const char *substreamName, const char *commands);

template void RCPClient::Send(unsigned char value, const char *substreamName, const char *commands);
template void RCPClient::Send(unsigned short value, const char *substreamName, const char *commands);
template void RCPClient::Send(unsigned int value, const char *substreamName, const char *commands);
template void RCPClient::Send(unsigned long value, const char *substreamName, const char *commands);
template void RCPClient::Send(unsigned long long value, const char *substreamName, const char *commands);

template void RCPClient::Send(float value, const char *substreamName, const char *commands);
template void RCPClient::Send(double value, const char *substreamName, const char *commands);



template <class T> void RCPClient::Send(std::vector<T> values, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
    std::ostringstream valueStream;
    valueStream << "{\"Value\":[";
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            valueStream << ",";
        valueStream << *it;
    }
    valueStream << "]}";
    RCPClient::Send(
        valueStream.str().c_str(),
        substreamName,
        commands ? (std::string("ParseJson();") + std::string(commands)).c_str() : "ParseJson()"
    );
}

template void RCPClient::Send(std::vector<int> values, const char *substreamName, const char *commands);

template void RCPClient::Send(std::vector<char> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<short> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<int> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<long> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<long> values , const char *substreamName, const char *commands);

template void RCPClient::Send(std::vector<unsigned char> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<unsigned short> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<unsigned int> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<unsigned long> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<unsigned long long> values, const char *substreamName, const char *commands);

template void RCPClient::Send(std::vector<float> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::vector<double> values, const char *substreamName, const char *commands);



template <class T> void RCPClient::Send(std::list<T> values, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
    std::ostringstream valueStream;
    valueStream << "{\"Value\":[";
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            valueStream << ",";
        valueStream << *it;
    }
    valueStream << "]}";
    RCPClient::Send(
        valueStream.str().c_str(),
        substreamName,
        commands ? (std::string("ParseJson();") + std::string(commands)).c_str() : "ParseJson()"
    );
}

template void RCPClient::Send(std::list<int> values, const char *substreamName, const char *commands);

template void RCPClient::Send(std::list<char> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<short> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<int> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<long> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<long> values , const char *substreamName, const char *commands);

template void RCPClient::Send(std::list<unsigned char> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<unsigned short> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<unsigned int> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<unsigned long> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<unsigned long long> values, const char *substreamName, const char *commands);

template void RCPClient::Send(std::list<float> values, const char *substreamName, const char *commands);
template void RCPClient::Send(std::list<double> values, const char *substreamName, const char *commands);
