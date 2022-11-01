#pragma once

namespace wl
{

	class ImageBuffer
	{
	public:
		ImageBuffer() = default;
		ImageBuffer(const char *filename);
		void Load(const char *filename);
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
