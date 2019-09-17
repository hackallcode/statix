#include "Session.h"

net::Session::Session(boost::asio::io_service& io_service, net::Parser const& parser)
	: socket_(io_service)
	, data_()
	, parser_(parser)
{}

tcp::socket& net::Session::Socket()
{
	return socket_;
}

void net::Session::Start()
{
	socket_.async_read_some(
		boost::asio::buffer(data_, RECEIVER_BUFFER_LENGTH),
		boost::bind(
			&Session::OnRead_, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void net::Session::Write(std::shared_ptr<std::vector<uint8_t>> data)
{
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(*data),
		boost::bind(
			&Session::OnWrite_, this, 
			boost::asio::placeholders::error
		)
	);
}

void net::Session::OnRead_(const boost::system::error_code& error, size_t bytesTransferred)
{
	if (!error || error == boost::asio::error::eof) {
		if (bytesTransferred != 0) {
			input_ += std::string(data_, bytesTransferred);
		}
		if (bytesTransferred == 0 || error == boost::asio::error::eof) {
			parser_.Parse(input_);
			return;
		}
		socket_.async_read_some(
			boost::asio::buffer(data_, RECEIVER_BUFFER_LENGTH),
			boost::bind(
				&Session::OnRead_, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}
	else {
		delete this;
	}
}

void net::Session::OnWrite_(const boost::system::error_code& error)
{
	delete this;
}

