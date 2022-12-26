#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/map.hpp>
#include "../Client/Client.h"
#include "../Banque/Banque.h"
#include "../Compte/Compte.h"
#include "../Json/load_save_Json.h"

using namespace std;
using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

std::string to_string(boost::asio::streambuf& buffer)
{
    boost::asio::streambuf::const_buffers_type data = buffer.data();
    return { boost::asio::buffers_begin(data), boost::asio::buffers_end(data) };
}

template <typename _Data_type>
_Data_type get_data_from_string(const char* s)
{
    _Data_type data;
    boost::asio::streambuf buf;
    std::ostream output(&buf);
    output << s;
    std::istream is(&buf);
    boost::archive::text_iarchive ia(is);
    ia >> data;
    return std::move(data);
}

template <typename _Data_type>
std::string get_string_from_data(const _Data_type& data)
{
    boost::asio::streambuf buf;
    std::ostream os(&buf);
    boost::archive::text_oarchive ar(os);
    ar << data;
    auto s = to_string(buf);
    return std::move(s);
}