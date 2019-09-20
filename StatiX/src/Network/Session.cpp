#include "Session.h"

net::Session::Session(boost::asio::io_service& io_service)
	: socket_(io_service)
	, date_("Wed, 21 Oct 2015 07:28:00 GMT")
	, isDir_(false)
{}

tcp::socket& net::Session::Socket()
{
	return socket_;
}

std::string net::Session::Read()
{
	boost::asio::streambuf buffer;
	boost::system::error_code error;
	size_t length = boost::asio::read_until(socket_, buffer, HeaderEnd, error);
	if (error) {
		throw boost::system::system_error(error); // Some other error.
	}
	auto data = buffer.data();
	return std::string(boost::asio::buffers_begin(data), boost::asio::buffers_begin(data) + length);
}

void net::Session::Send405()
{
	socket_.write_some(boost::asio::buffer(GetHeader405_(date_)));
}

void net::Session::SendFile(std::shared_ptr<files::CacheFile> file)
{
	if (!file) {
		if (isDir_) {
			socket_.write_some(boost::asio::buffer(GetHeader403_(date_)));
		}
		else {
			socket_.write_some(boost::asio::buffer(GetHeader404_(date_)));
		}
		return;
	}
	socket_.write_some(boost::asio::buffer(GetHeader200_(date_, file->type, file->length)));
	if (method_ == "GET") {
		socket_.write_some(boost::asio::buffer(file->data));
	}
}

void net::Session::SetIdDir(bool isDir)
{
	isDir_ = isDir;
}

void net::Session::SetMethod(std::string const& method)
{
	method_ = method;
}

std::string net::GetHeader403_(std::string const& date)
{
	return "HTTP/1.0 403 Forbidden\r\n"
		+ StaticResponceHeader
		+ "Date: " + date
		+ "\r\n\r\n";
}

std::string net::GetHeader404_(std::string const& date)
{
	return "HTTP/1.0 404 Not Found\r\n"
		+ StaticResponceHeader
		+ "Date: " + date
		+ "\r\n\r\n";
}

std::string net::GetHeader405_(std::string const& date)
{
	return "HTTP/1.0 405 Method Not Allowed\r\n"
		+ StaticResponceHeader
		+ "Date: " + date
		+ "\r\n\r\n";
}

std::string net::GetHeader200_(std::string const& date, std::string const& type, std::string const& length)
{
	return "HTTP/1.0 200 OK\r\n"
		+ StaticResponceHeader
		+ "Date: " + date
		+ "\r\nContent-Length: " + length 
		+ "\r\nContent-Type: " + type
		+ "\r\n\r\n";
}
