#include "ImageDoctor.h"
USING_NS_CC;

bool ImageDoctor::ifSupport(std::string filePath)
{
	if (!FileUtils::getInstance()->isFileExist(filePath))
	{
		return false;
	}
	Data data = FileUtils::getInstance()->getDataFromFile(filePath);
	if (data.isNull())
	{
		return false;
	}
	Format fileType  = detectFormat(data.getBytes(), data.getSize());
	if (fileType == Format::UNKNOWN)
	{
		return false;
	}
	return true;
}

ImageDoctor::Format ImageDoctor::detectFormat(const unsigned char * data, ssize_t dataLen)
{
	if (isPng(data, dataLen))
	{
		return Format::PNG;
	}
	else if (isJpg(data, dataLen))
	{
		return Format::JPG;
	}
	else if (isTiff(data, dataLen))
	{
		return Format::TIFF;
	}
	else if (isWebp(data, dataLen))
	{
		return Format::WEBP;
	}
	else
	{
		return Format::UNKNOWN;
	}
}

bool ImageDoctor::isPng(const unsigned char * data, ssize_t dataLen)
{
	if (dataLen <= 8)
	{
		return false;
	}

	static const unsigned char PNG_SIGNATURE[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

	return memcmp(PNG_SIGNATURE, data, sizeof(PNG_SIGNATURE)) == 0;
}

bool ImageDoctor::isJpg(const unsigned char * data, ssize_t dataLen)
{
	if (dataLen <= 4)
	{
		return false;
	}

	static const unsigned char JPG_SOI[] = { 0xFF, 0xD8 };

	return memcmp(data, JPG_SOI, 2) == 0;
}

bool ImageDoctor::isTiff(const unsigned char * data, ssize_t dataLen)
{
	if (dataLen <= 4)
	{
		return false;
	}

	static const char* TIFF_II = "II";
	static const char* TIFF_MM = "MM";

	return (memcmp(data, TIFF_II, 2) == 0 && *(static_cast<const unsigned char*>(data)+2) == 42 && *(static_cast<const unsigned char*>(data)+3) == 0) ||
		(memcmp(data, TIFF_MM, 2) == 0 && *(static_cast<const unsigned char*>(data)+2) == 0 && *(static_cast<const unsigned char*>(data)+3) == 42);
}

bool ImageDoctor::isWebp(const unsigned char * data, ssize_t dataLen)
{
	if (dataLen <= 12)
	{
		return false;
	}

	static const char* WEBP_RIFF = "RIFF";
	static const char* WEBP_WEBP = "WEBP";

	return memcmp(data, WEBP_RIFF, 4) == 0
		&& memcmp(static_cast<const unsigned char*>(data)+8, WEBP_WEBP, 4) == 0;
}