#pragma once

#include <string>
namespace wl
{

	class ImageBuffer
	{
	public:
		ImageBuffer() = default;
		ImageBuffer(std::string filename);
		void Load(std::string filename);
		const unsigned char *GetData() const;
		const int GetWidth() const;
		const int GetHeight() const;
		const int GetChannels() const;
	private:
		int m_width{};
		int m_height{};
		int m_channels{};
		unsigned char *m_data{};
		const char *m_filepath{};
	};

}
