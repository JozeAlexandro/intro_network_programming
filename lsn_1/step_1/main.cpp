// C++ Standard
#include <iostream>
#include <string>
#include <utility> // forward
#include <functional>

// System
#include <unistd.h> // open / close 
#include <sys/socket.h> // Communication domains
#include <netinet/in.h> // sockaddr_in

template< typename Callable, typename... Args >
inline auto CallAndCheck( Callable&& foo, const char* errMsg, Args... args )
{
    const auto result{ foo( std::forward< Args >( args )... ) };
    if( result < 0 )
    {
        perror( errMsg );
        exit( EXIT_FAILURE );
    }

    return result;
}

int main()
{
    const int fdServer{ CallAndCheck( socket, "socket", AF_INET, SOCK_STREAM, 0 ) }; 

    sockaddr_in myAddr{};
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = htonl( INADDR_ANY );
    myAddr.sin_port = htons( 1234 );

    CallAndCheck( bind, "bind", fdServer, reinterpret_cast< sockaddr* >( &myAddr ), sizeof( myAddr ) ); 

    constexpr int maxConnectionsInLine{ 10 };
    CallAndCheck( listen, "listen", fdServer, maxConnectionsInLine );

    unsigned counter{ 1 };
    while( true )
    {
        const int fdClient{ CallAndCheck( accept, "accept", fdServer, nullptr, nullptr ) };

        std::string msg{ std::string{ "Oh! You're "} + std::to_string( counter++ ) };
 
        CallAndCheck( write, "write", fdClient, msg.c_str(), msg.size() );
        CallAndCheck( close, "close", fdClient );
    }

    return EXIT_SUCCESS;
}

