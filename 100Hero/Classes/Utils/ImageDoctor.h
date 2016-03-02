#ifndef __IMAGE_DOCTOR_H__
#define __IMAGE_DOCTOR_H__
#include "cocos2d.h"

class ImageDoctor
{
public:
	static bool ifSupport(std::string filePath);
private:
	enum class Format
	{
		JPG,
		PNG,
		TIFF,
		WEBP,
		UNKNOWN
	};

	ImageDoctor(){}
	~ImageDoctor(){}
	static Format detectFormat(const unsigned char * data, ssize_t dataLen);
	static bool isPng(const unsigned char * data, ssize_t dataLen);
	static bool isJpg(const unsigned char * data, ssize_t dataLen);
	static bool isTiff(const unsigned char * data, ssize_t dataLen);
	static bool isWebp(const unsigned char * data, ssize_t dataLen);
	//bool isPvr(const unsigned char * data, ssize_t dataLen);
	//bool isEtc(const unsigned char * data, ssize_t dataLen);
	//bool isS3TC(const unsigned char * data, ssize_t dataLen);
	//bool isATITC(const unsigned char *data, ssize_t dataLen);
};
#endif