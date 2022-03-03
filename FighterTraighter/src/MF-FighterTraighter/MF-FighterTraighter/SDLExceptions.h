#pragma once
#include <stdexcept>

namespace SDLExceptions 
{
	//SDL exceptions
	class SDLException : public std::logic_error 
	{
	public:
		SDLException(const std::string& what) : logic_error("SDL error: " + what) {}
		SDLException(const char* what) : logic_error("SDL error: " + std::string(what)) {}
	};

	//TTF exceptions
	class TTFException : public std::logic_error
	{
	public:
		TTFException(const std::string& what) : logic_error("TTF error: " + what) {}
		TTFException(const char* what) : logic_error("TTF error: " + std::string(what)) {}
	};
	

}