#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <signal.h>

int main()
{
	//try	{
	//	boost::asio::io_service io_service;

	//	

	//	// Wait for signals indicating time to shut down.
	//	boost::asio::signal_set signals(io_service);
	//	signals.add(SIGINT);
	//	signals.add(SIGTERM);
	//	#if defined(SIGQUIT)
	//		signals.add(SIGQUIT);
	//	#endif // defined(SIGQUIT)
	//	signals.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service));

	//	// Run the server.
	//	io_service.run();
	//}
	//catch (std::exception& e) {
	//	std::cerr << "Unknown exception: " << e.what() << "\n";
	//}



	return 0;
}