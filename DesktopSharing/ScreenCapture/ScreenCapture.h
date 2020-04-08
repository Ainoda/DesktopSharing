// Ainoda
// 2020-04-08

#ifndef SCREEN_CAPTURE_H
#define SCREEN_CAPTURE_H

#include <cstdio>
#include <cstdint>
#include <string>
#include <mutex>
#include <thread>
#include <memory>
#include <wrl.h>
#include <dxgi.h>
#include <d3d11.h>
#include <dxgi1_2.h>

class ScreenCapture
{
public:
	ScreenCapture();
	virtual ~ScreenCapture();
	ScreenCapture &operator=(const ScreenCapture &) = delete;
	ScreenCapture(const ScreenCapture &) = delete;

public:
	virtual int init(int displayIndex = 0) = 0;
	virtual int exit() = 0;
	virtual int start() = 0;
	virtual int stop() = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

	virtual int captureFrame(std::shared_ptr<uint8_t>& bgraPtr, uint32_t& size) = 0;
	virtual int getTextureHandle(HANDLE* handle, int* lockKey, int* unlockKey) = 0;
	virtual int captureImage(std::string pathname) = 0;

	virtual bool isCapturing() const = 0;
};

#endif