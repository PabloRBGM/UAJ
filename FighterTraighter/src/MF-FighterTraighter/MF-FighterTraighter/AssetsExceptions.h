#pragma once
#include <stdexcept>

namespace AssetsExceptions
{
	//image excepcion class
	class TextureException : public std::runtime_error 
	{
	public:
		TextureException(const std::string& what, const std::string& textureFile) : runtime_error("Texture error: " + what + textureFile) {}
		TextureException(const char* what, const char* textureFile) : runtime_error("Texture error: " + std::string(what) + textureFile) {}
	};
	
	//font excepcion class
	class FontException : public std::runtime_error 
	{
	public:
		FontException(const std::string& what, const std::string& fontFile) : runtime_error("Font error: " + what + fontFile) {}
		FontException(const char* what, const char* fontFile) : runtime_error("Font error: " + std::string(what) + std::string(fontFile)) {}
	};

	//sound exception class
	class SoundException : public std::runtime_error
	{
		SoundException(const std::string& what, const std::string& soundfile) : runtime_error("Sound error: " + what + soundfile) {}
		SoundException(const char* what, const char* soundFile) : runtime_error("Sound error: " + std::string(what) + std::string(soundFile)) {}
	};

	//sound effects exception class
	class SoundEffectsException : public std::runtime_error
	{
		SoundEffectsException(const std::string& what, const std::string& soundfile) : runtime_error("SFX error: " + what + soundfile) {}
		SoundEffectsException(const char* what, const char* soundFile) : runtime_error("SFX error: " + std::string(what) + std::string(soundFile)) {}
	};
};

