#include "../include/controller/net.hpp"

using boost::asio::ip::udp;

net::net()
	//all this stuff (socket and endpoints) is here because it causes a bug if it isn't
	: io_service(),
	remote_endpoint(),
local_endpoint(udp::v4(), 9001),
 my_socket(io_service){

	std::string ip;
	boost::system::error_code ec;

	my_socket.open(udp::v4(), ec);
	my_socket.bind(local_endpoint, ec);	

	INIReader reader("../config/ip_remoto.ini");
	if (reader.ParseError() < 0) {
		std::cout << "Can't load 'ip_remoto.ini'\n";
		exit( 1 );
	}
	ip=reader.Get("IPv4", "ip_remoto", "0.0.0.0");
	ip_remoto = boost::asio::ip::address::from_string(ip);


	remote_endpoint.address(ip_remoto);
	remote_endpoint.port(9001);
}

void net::send(std::string str){
	//this sends the string with a \0 trailing character so that the receiver will handle it properly
	char string[str.size()+1];
	strcpy(string, str.c_str());
	string[str.size()]='\0';

	my_socket.send_to(boost::asio::buffer(string, str.size()+1), remote_endpoint);
}

std::string net::get(){
	char recv[10000];
	udp::endpoint received_endpoint; 

	my_socket.receive_from(boost::asio::buffer(recv, 10000), received_endpoint);

	return recv;
}
