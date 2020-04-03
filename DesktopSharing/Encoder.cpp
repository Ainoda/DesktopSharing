#include "Encoder.h"

extern "C"
{
#include <libavutil/error.h>
}
#include "net/log.h"

#pragma comment(lib,"avutil.lib")

Encoder::Encoder()
{
}


Encoder::~Encoder()
{
}

void Encoder::printError(int err_code)
{
	const auto errbuf_size = 1024;
	char errbuf[errbuf_size] = { 0 };
	av_strerror(err_code, errbuf, errbuf_size);
	LOG("%s", errbuf);
}
