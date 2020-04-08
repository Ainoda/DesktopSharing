// PHZ
// 2019-7-22

#ifndef DXGI_SCREEN_CAPTURE_H
#define DXGI_SCREEN_CAPTURE_H

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

class DXGIScreenCapture : public ScreenCapture
{
public:
	DXGIScreenCapture();
	virtual ~DXGIScreenCapture();
	DXGIScreenCapture &operator=(const DXGIScreenCapture &) = delete;
	DXGIScreenCapture(const DXGIScreenCapture &) = delete;

	virtual int init(int displayIndex = 0) override;
	virtual int exit() override;
	virtual int start() override;
	virtual int stop() override;

	inline int getWidth()  { return m_dxgiDesc.ModeDesc.Width; }
	inline int getHeight() { return m_dxgiDesc.ModeDesc.Height; }

	virtual int captureFrame(std::shared_ptr<uint8_t>& bgraPtr, uint32_t& size) override;
	virtual int getTextureHandle(HANDLE* handle, int* lockKey, int* unlockKey) override;
	virtual int captureImage(std::string pathname); override;
	
	inline ID3D11Device* getID3D11Device() { return m_d3d11device.Get(); }
	inline ID3D11DeviceContext* getID3D11DeviceContext() { return m_d3d11DeviceContext.Get(); }

	virtual bool isCapturing() const override
	{ return m_isEnabeld; }

private:
	int createSharedTexture();
	int aquireFrame();

	bool m_initialized;
	bool m_isEnabeld;
	std::mutex m_mutex;
	std::shared_ptr<std::thread> m_threadPtr;
	std::shared_ptr<uint8_t> m_bgraPtr;
	uint32_t m_bgraSize;
	DXGI_OUTDUPL_DESC m_dxgiDesc;
	HANDLE m_textureHandle;
	int m_key;
	Microsoft::WRL::ComPtr<ID3D11Device> m_d3d11device;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_sharedTexture;
	Microsoft::WRL::ComPtr<IDXGIKeyedMutex> m_keyedMutex;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_rgbaTexture;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_gdiTexture;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3d11DeviceContext;
	Microsoft::WRL::ComPtr<IDXGIOutputDuplication> m_dxgi0utputDuplication;
};

#endif