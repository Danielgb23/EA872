
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>

#include "INIReader.h"

using boost::asio::ip::udp;
class net {

	public:
		net();
		void send(std::string str);
		std::string get();

	private:
		boost::asio::io_service io_service;
		udp::socket my_socket;
		udp::endpoint local_endpoint;
		udp::endpoint remote_endpoint; 
  		boost::asio::ip::address ip_remoto;

};
