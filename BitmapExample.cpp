#include "BitmapExample.h"

HRESULT BitmapExample::CreateDeviceResources()
{
    HRESULT hr = mspRenderTarget->CreateBitmap(
        D2D1::SizeU(BITMAP_
            D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
            mspFrameBuffer.ReleaseAndGetAddressOf()
    );
    ThrowIfFailed(hr);

    return S_OK;
}

HRESULT BitmapExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
    D2DFramework::Initialize(hInstance, title, w, h);

    mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH * BITMAP_HEIGHT * BITMAP_BYTECOUNT);

    UINT8* p = &mspBackBuffer[0];
    for (int i = 0; i < BITMAP_WIDTH * BITMAP_HEIGHT; i++)
    {
        *p++ == 255;
        *p++ == 255;
        *p++ == 255;
        *p++ == 255;
    }

    return S_OK;
}

void BitmapExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));



    PresentBuffer();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));


    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void BitmapExample::PresentBuffer()
{
    mspFrameBuffer->CopyFromMemory(nullptr, &mspBackBuffer[0], BITMAP_WIDTH * BITMAP_BYTECOUNT);
}
