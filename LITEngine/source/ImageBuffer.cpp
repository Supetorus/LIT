#include "ImageBuffer.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#include "stb_image.h"
#include "core.h"

namespace lit
{
	ImageBuffer::ImageBuffer(std::string path):
		m_filepath(path.c_str())
	{
		Load(path);
	}

	void ImageBuffer::Load(std::string path)
	{
		m_filepath = path.c_str();
		m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
		m_channels = 4;
		ASSERT(m_data != nullptr, std::string{ "Failed to load image: " }.append(path).c_str(), stbi_failure_reason());
		//std::cout << "Image Loaded.\n";
		//std::cout << "Width: " << m_width << '\n';
		//std::cout << "height: " << m_height << '\n';
		//std::cout << "channels: " << m_channels << '\n';
		//for (int i = 0; i < m_height; i++)
		//{
		//	for (int j = 0; j < m_width * m_channels; j++)
		//	{
		//		if (j % m_channels == 0) std::cout << '\t';
		//		std::cout << ' ';
		//		std::cout << std::hex;
		//		int p = i * (m_width * m_channels) + j;
		//		unsigned char value = m_data[p];
		//		std::cout << (int)value << ' ';
		//	}
		//	std::cout << '\n';
		//}
	}

	const int ImageBuffer::GetWidth() const
	{
		return m_width;
	}

	const int ImageBuffer::GetHeight() const
	{
		return m_height;
	}

	const int ImageBuffer::GetChannels() const
	{
		return m_channels;
	}

	const int ImageBuffer::GetPitch() const
	{
		return m_width * m_channels;
	}

	const unsigned char *ImageBuffer::GetData() const
	{
		return m_data;
	}
}