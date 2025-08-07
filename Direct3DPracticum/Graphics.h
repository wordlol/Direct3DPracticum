#pragma once
#include "WindowsFrameWork.h"
#include "d3d11.h"
#pragma comment(lib,"d3d11.lib")

class Graphics
{
public:
	Graphics( HWND hWnd) 
	{
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = hWnd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;


		D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext);

		ID3D11Resource* pBackBuffer = nullptr;
		pSwap->GetBuffer(0,__uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
		pDevice->CreateRenderTargetView(
			pBackBuffer,
			nullptr,
			&pTarget
		);
		pBackBuffer->Release();
	};

	Graphics(const Graphics&) = delete;
	Graphics* operator=(const Graphics&) = delete;
	~Graphics()
	{
		if (pDevice != nullptr)
		{
			pDevice->Release();
		}
		if (pSwap != nullptr)
		{
			pSwap->Release();
		}
		if (pContext != nullptr)
		{
			pContext->Release();
		}
		if (pTarget != nullptr)
		{
			pTarget->Release();
		}
	}

	void EndFrame()
	{
		pSwap->Present(1u,0u);
	};
	void ClearBuffer(float red, float green, float blue)
	{
		const float color[] = { red,green,blue,1.0f };
		pContext->ClearRenderTargetView(pTarget, color);
	}
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};