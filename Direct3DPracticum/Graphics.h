#pragma once
#include "WindowsFrameWork.h"
#include "d3d11.h" /// хэдер библиотеки DirectX11
#pragma comment(lib,"d3d11.lib") ///загружает библиотеку непосредственно в исходный код (крч нужно чтобы небыло ошибок при инициализации d3d11)

class Graphics
{
public:
	Graphics(HWND hWnd)
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

		/// Создает устройство, представляющее видеоадаптер и цепочку буферов, используемую для отрисовки
		D3D11CreateDeviceAndSwapChain( ///
			nullptr, /// видео аддаптер по умолчанию
			D3D_DRIVER_TYPE_HARDWARE, /// Драйвер оборудования, который реализует функции Direct3D в оборудовании
			nullptr, /// Дескриптор библиотеки DLL, реализующий программный растеризатор
			0, ///Уровни среды выполнения для включения (базовый)
			nullptr, ///базовые уровни набора функций, предназначенных для устройства Direct3D
			0, /// Количество элементов в pFeatureLevels.^^^^
			D3D11_SDK_VERSION, /// Версия пакета SDK;
			&sd, /// дискриптор DXGI_SWAP_CHAIN_DESC
			&pSwap, /// IDXGISwapChain
			&pDevice, /// ID3D11Device
			nullptr, /// Укажите значение NULL в качестве входных данных, если вам не нужно определять, какой уровень компонентов поддерживается
			&pContext); /// ID3D11DeviceContext

		ID3D11Resource* pBackBuffer = nullptr; // уникальный код COM
		pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer)); ///Этот метод возвращает буфер текущего при помощи COM
		pDevice->CreateRenderTargetView( /// Создает рендер-целевой вид для доступа к данным ресурсов
			pBackBuffer, /// указатель на ресурс
			nullptr, /// получает доступ ко всем субресурсам на уровне mipmap 0
			&pTarget /// ID3D11RenderTargetView
		);
		pBackBuffer->Release();
	};
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

	Graphics(const Graphics&) = delete;	
	Graphics* operator=(const Graphics&) = delete;

	void EndFrame()
	{
		pSwap->Present(1u, 0u);
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