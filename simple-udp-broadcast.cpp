#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>

using namespace std;
namespace ba = boost::asio;
namespace po = boost::program_options;


int broadcast_message(std::string ip_address, int port, std::string message)
{
    boost::asio::io_service io_service;
    ba::ip::udp::socket socket(io_service);

    socket.open(ba::ip::udp::v4());
    socket.set_option(ba::socket_base::broadcast(true));

    ba::ip::udp::endpoint senderEndpoint(boost::asio::ip::address::from_string(ip_address), port);

    try
    {
        socket.send_to(boost::asio::buffer(message), senderEndpoint);
        socket.close();
        printf("Broadcast sent to %s\n" , ip_address.c_str());

    } catch(exception e)
    {
        printf("Cannot broadcast message to %s \n" , ip_address.c_str());
    }   

    return 0;   
}

int main(int argc, const char *argv[])
{
    std::string ip_address;
    int port;
    std::string message; 

    po::options_description desc("All options");
    po::variables_map vm;
    desc.add_options()
        ("help,h", "produce help message")
        ("server,s" , po::value<std::string>(), "server" )
        ("port,p" ,  po::value<int>(), "port")
        ("message,m",  po::value<std::string>(), "message")
    ;
    po::store(parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help") || vm.count("h"))
    {
        std::cout << desc << std::endl;
        exit(0);
    }

    if (vm.count("server")) 
        ip_address = vm["server"].as<std::string>();
    else if (vm.count("s"))
        ip_address = vm["s"].as<std::string>();
    else 
        ip_address = "10.0.0.178";

    if (vm.count("port"))
        port = vm["port"].as<int>();
    else if (vm.count("p"))
        port = vm["p"].as<int>();
    else 
        port = 0;

    if (vm.count("message")) 
        message = vm["message"].as<std::string>();
    else if (vm.count("m"))
        message = vm["m"].as<std::string>();
    else 
        message = "Broadcast message";

    broadcast_message(ip_address , port , message);

    return 0;
}