// Ainoda
// 2020-04-08

#ifndef BB_SCREEN_CAPTURE_H
#define BB_SCREEN_CAPTURE_H

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

#include "ScreenCapture.h"

class BBScreenCapture : public ScreenCapture
{
public:
	BBScreenCapture();
	virtual ~BBScreenCapture();
	BBScreenCapture &operator=(const BBScreenCapture &) = delete;
	BBScreenCapture(const BBScreenCapture &) = delete;

	virtual int init(int displayIndex = 0) override;
	virtual int exit() override;
	virtual int start() override;
	virtual int stop() override;

	inline int getWidth()  { return m_width; }
	inline int getHeight() { return m_height; }

	virtual int captureFrame(std::shared_ptr<uint8_t>& bgraPtr, uint32_t& size) override;
	virtual int getTextureHandle(HANDLE* handle, int* lockKey, int* unlockKey) override { return -1; }
	virtual int captureImage(std::string pathname) override { return -1; }

	virtual bool isCapturing() const override
	{ return m_isEnabeld; }

private:
	int aquireFrame();

	HWND m_hwnd = 0;
	HDC m_hdc1 = 0;
	HDC m_hdc2 = 0;

	bool m_initialized;
	bool m_isEnabeld;
	RECT rect;
	int m_width = 1920;
	int m_height = 1080;
	std::mutex m_mutex;
	HBITMAP m_bitmap = 0;
	BITMAPINFO m_bitmapInfo;
	std::shared_ptr<std::thread> m_threadPtr;
	std::shared_ptr<uint8_t> m_bgraPtr;
	uint32_t m_bgraSize;
};

#endif