/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Application.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Application, "ala::Application")
// ==================================================
// Basic
// ==================================================

Application::Application() :
  _inited( false ),
  _released( false ),
  _title( "Aladdin Game" ),
  _screenWidth( 0 ),
  _screenHeight( 0 ),
  _loopInterval( 1000.0f / 30 ),
  _sceneToStart( NULL ),
  _logStream( 0 ),
  _exiting( false ),
  _hInstance( NULL ),
  _hWnd( NULL ),
  _directX( NULL ),
  _directXDevice( NULL ),
  _directXSprite( NULL ),
  _lastTimestamp( 0 ) {}

Application::~Application() {
  if ( _inited ) {
    ALA_ASSERT(_released);
  }
}

void Application::setScreenSize( int width, int height ) {
  // can only be set before init process
  ALA_ASSERT((!_inited) && (!_released));
  _screenWidth = width;
  _screenHeight = height;
}

int Application::getScreenWidth() const {
  return _screenWidth;
}

int Application::getScreenHeight() const {
  return _screenHeight;
}

void Application::setTitle( const std::string& title ) {
  // can only be set before init process
  ALA_ASSERT((!_inited) && (!_released));
  _title = title;
}

const std::string& Application::getTitle() const {
  return _title;
}

void Application::setLoopInterval( float millis ) {
  // can only be set before init process
  ALA_ASSERT((!_inited) && (!_released));
  _loopInterval = millis;
}

float Application::getLoopInterval() const {
  return _loopInterval;
}

void Application::startWithScene( Scene* scene ) {
  // can only be set before init process
  ALA_ASSERT((!_inited) && (!_released));
  _sceneToStart = scene;
}

void Application::initComponents() {
  ALA_ASSERT(_screenWidth > 0);
  ALA_ASSERT(_screenHeight > 0);
  ALA_ASSERT(!_title.empty());
  ALA_ASSERT(_loopInterval >= (1000.0f / 61));

  // windows components
  initWindowHandle();

  initDirectX();

  // game singleton components
  GameManager::get()->replaceScene( _sceneToStart );

  // seed random
  srand( static_cast<unsigned int>(time( 0 )) );
}

void Application::releaseComponents() {
  // running scene
  Scene* scene = GameManager::get()->getRunningScene();
  SAFE_DELETE(scene)

  // game singleton components
  GameManager* gameManager = GameManager::get();
  SAFE_DELETE(gameManager);

  // windows components
  releaseDirectX();
}

void Application::onUpdate( float delta ) {
  Scene* runningScene = GameManager::get()->getRunningScene();
  if ( runningScene ) {
    if ( !runningScene->isInited() ) {
      runningScene->init();
    }
    else {
      runningScene->update( delta );
    }
  }
}

void Application::onRender() {
  Scene* runningScene = GameManager::get()->getRunningScene();
  if ( runningScene ) {
    runningScene->render();
  }
}

// ===================================================
// Platform specific
// ===================================================
void Application::run( HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPSTR lpCmdLine,
                       int nCmdShow,
                       int logStream ) {
  // make sure that application can only init once
  ALA_ASSERT(!_inited);

  // get run arguments
  _hInstance = hInstance;
  _logStream = logStream;

  // client application init
  init();

  // init components
  initComponents();

  _inited = true;

  // make sure that application is already inited before looping
  ALA_ASSERT(_inited);

  // platform specific game loop
  gameLoop();

  // make sure that application can only release once
  ALA_ASSERT(!_released);

  // client application release
  release();

  // release components
  releaseComponents();

  _released = true;

  // make sure that application is already released before exit
  ALA_ASSERT(_released);
}

void Application::initWindowHandle() {
  // Logging
  switch ( _logStream ) {
  case 1: {
    AllocConsole();
    AttachConsole( GetCurrentProcessId() );
    // ReSharper disable CppDeprecatedEntity
    freopen( "CON", "w", stdout );
    // ReSharper restore CppDeprecatedEntity
  }
    break;
  case 2: {
    // ReSharper disable CppDeprecatedEntity
    freopen( "log.txt", "w", stdout );
    // ReSharper restore CppDeprecatedEntity
  }
    break;
  default:
    break;
  }

  // Windows
  WNDCLASSEX wndClassEx;
  ZeroMemory(&wndClassEx, sizeof(wndClassEx));
  wndClassEx.cbSize = sizeof(WNDCLASSEX);
  wndClassEx.hInstance = _hInstance; // bind with handle instance
  wndClassEx.lpfnWndProc = reinterpret_cast<WNDPROC>(wndProc); // register windows procedure
  wndClassEx.lpszClassName = _title.c_str(); // define class name
  ALA_ASSERT(RegisterClassEx(&wndClassEx) != 0);

  // create windows
  _hWnd = CreateWindow(
    wndClassEx.lpszClassName, // windows class name
    _title.c_str(), // windows title
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // windows style
    CW_USEDEFAULT, // windows start position
    CW_USEDEFAULT, // windows start position
    _screenWidth, // windows size
    _screenHeight, // windows size
    0,
    0,
    _hInstance, // handle instance
    0);
  ALA_ASSERT(_hWnd);

  // show windows
  ShowWindow( _hWnd, SW_SHOW );
  UpdateWindow( _hWnd );
}

void Application::initDirectX() {
  // init DirectX
  _directX = Direct3DCreate9( D3D_SDK_VERSION );
  ALA_ASSERT(!FAILED(_directX));

  // init DirectX device
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp, sizeof(d3dpp));
  d3dpp.BackBufferCount = 1;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  d3dpp.BackBufferWidth = static_cast<UINT>(_screenWidth);
  d3dpp.BackBufferHeight = static_cast<UINT>(_screenHeight);
  d3dpp.Windowed = true;
  d3dpp.hDeviceWindow = _hWnd;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  _directX->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    _hWnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &d3dpp,
    &_directXDevice );
  ALA_ASSERT(!FAILED(_directXDevice));

  // init DirectX Sprite
  HRESULT result;
  result = D3DXCreateSprite( _directXDevice, &_directXSprite );
  ALA_ASSERT(result == D3D_OK);
}

void Application::releaseDirectX() const {
  if ( _directXSprite ) {
    _directXSprite->Release();
  }
  if ( _directX ) {
    _directX->Release();
  }
  if ( _directXDevice ) {
    _directXDevice->Release();
  }
}

void Application::gameLoop() {
  // initial timestamp
  _lastTimestamp = GetTickCount();

  while ( !_exiting ) {
    processMessage();
    processGame();
  }
}

void Application::processMessage() {
  // read message from message queue
  if ( PeekMessage( &_msg, 0, 0, 0, PM_REMOVE ) ) {
    if ( _msg.message == WM_QUIT ) {
      // exit event
      _exiting = true;
      return;
    }

    // process message
    TranslateMessage( &_msg );
    DispatchMessage( &_msg );
  }
}

void Application::processGame() {
  const DWORD currentTimestamp = GetTickCount();
  // calculate delta
  const float delta = static_cast<float>(currentTimestamp - _lastTimestamp);

  // check interval
  if ( delta >= _loopInterval ) {
    // update timestamp
    _lastTimestamp = currentTimestamp;

    onUpdate( delta );
  }

  // clear screen
  _directXDevice->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );

  // start rendering
  if ( _directXDevice->BeginScene() ) {
    _directXSprite->Begin( D3DXSPRITE_ALPHABLEND );

    onRender();

    // stop rendering
    _directXSprite->End();
    _directXDevice->EndScene();
  }

  // display back buffer to screen
  _directXDevice->Present( 0, 0, 0, 0 );
}

LRESULT Application::wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
  // Process message sent to windows

  switch ( message ) {
  case WM_CLOSE: // Windows is about to be closed because user click Close button or press Alt + F4
    break;
  case WM_DESTROY: // Windows is already closed and is about to be destroyed
    PostQuitMessage( 0 ); // put quit message to message queue
    break;
  default:
    break;
  }

  // Default message behaviors
  return DefWindowProc( hWnd, message, wParam, lParam );
}
}
