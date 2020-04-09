// Ainoda
// 2020-04-08

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "BBScreenCapture.h"
#include <fstream> 
#include <chrono>
#include <iostream>
#include <windows.h>

BBScreenCapture::BBScreenCapture()
	: ScreenCapture()
	, m_initialized(false)
	, m_isEnabeld(false)
	, m_bgraPtr(nullptr)
	, m_bgraSize(0)
{
}

BBScreenCapture::~BBScreenCapture()
{

}

int BBScreenCapture::init(int displayIndex)
{
	if (m_initialized)
	{
		return -1;
	}

	m_hwnd = ::GetDesktopWindow();
	m_hdc1 = ::GetWindowDC(m_hwnd);
	m_hdc2 = ::CreateCompatibleDC(m_hdc1);

	::GetWindowRect(m_hwnd, &rect);

	m_width = rect.right - rect.left;
	m_height = rect.bottom - rect.top;
	std::cout << m_width << ", " << m_height << std::endl;

	m_bitmap = ::CreateCompatibleBitmap(m_hdc1, m_width, m_height);
	::SelectObject(m_hdc2, m_bitmap);

	m_bitmapInfo = { { sizeof(BITMAPINFOHEADER), m_width, m_height, 1, 24, 0, 0, 0, 0, 0, 0 }, {} };

	m_bgraSize = m_width * m_height * 3;
	m_bgraPtr.reset(new uint8_t[m_bgraSize]);
	memset(m_bgraPtr.get(), 0, m_bgraSize);

	m_initialized = true;
	return 0;
}

int BBScreenCapture::exit()
{
	return 0;
}

int BBScreenCapture::start()
{
	if (!m_initialized)
	{
		return -1;
	}

	if (m_isEnabeld)
	{
		return 0;
	}

	m_isEnabeld = true;
	aquireFrame();
	m_threadPtr.reset(new std::thread([this] {
		while (m_isEnabeld)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(15));
			aquireFrame();
		}
	}));

	return 0;
}

int BBScreenCapture::stop()
{
	m_isEnabeld = false;

	if (m_threadPtr != nullptr)
	{
		m_threadPtr->join();
		m_threadPtr = nullptr;
	}

	return 0;
}

int BBScreenCapture::aquireFrame()
{
	std::lock_guard<std::mutex> locker(m_mutex);
	::BitBlt(m_hdc2, 0, 0, m_width, m_height, m_hdc1, 0, 0, SRCCOPY);
	::GetDIBits(m_hdc2, m_bitmap, 0, m_height, m_bgraPtr.get(), &m_bitmapInfo, DIB_RGB_COLORS);
	return 0;
}

int BBScreenCapture::captureFrame(std::shared_ptr<uint8_t>& bgraPtr, uint32_t& size)
{
	std::lock_guard<std::mutex> locker(m_mutex);

	if (!m_isEnabeld)
	{
		return -1;
	}

	if (m_bgraPtr == nullptr || m_bgraSize == 0)
	{
		return -1;
	}

	bgraPtr = m_bgraPtr;
	size = m_bgraSize;
	return 0;
}