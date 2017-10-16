/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "Application.h"
#include "GameManager.h"
#include "../2d/Graphics.h"
#include "../input/Input.h"
#include "../audio/Audio.h"

NAMESPACE_ALA
{
// ==================================================
// Basic
// ==================================================
ALA_CLASS_SOURCE_2(Application, ala::Initializable, ala::Releasable)

Application::Application() :
  _title( "Aladdin Game" ),
  _screenWidth( 800 ),
  _screenHeight( 600 ),
  _frameCount( 0 ),
  _logger( "ala::Application" ),
  _logStream( 0 ),
  _exiting( false ),
  _hInstance( NULL ),
  _hWnd( NULL ) {
  // check initial state
  setFps( 60 );
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
}

Application::~Application() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }

  // memory debug
  _logger.info( "Total Resources Created: %ld", GameResource::TOTAL_RESOURCES_CREATED );
  _logger.info( "Total Resources Deleted: %ld", GameResource::TOTAL_RESOURCES_DELETED );
  _logger.info( "Total Resource Initializers Created: %ld", ResourceInitializer::TOTAL_RESOURCE_INITIALIZERS_CREATED );
  _logger.info( "Total Resource Initializers Deleted: %ld", ResourceInitializer::TOTAL_RESOURCE_INITIALIZERS_DELETED );
  _logger.info( "Total Scenes Created: %ld", Scene::TOTAL_SCENES_CREATED );
  _logger.info( "Total Scenes Deleted: %ld", Scene::TOTAL_SCENES_DELETED );
  _logger.info( "Total Objects Created: %ld", Node::TOTAL_NODES_CREATED );
  _logger.info( "Total Objects Deleted: %ld", Node::TOTAL_NODES_DELETED );
  _logger.info( "Total Loggers Created: %ld", Logger::TOTAL_LOGGERS_CREATED );
  _logger.info( "Total Loggers Deleted: %ld", Logger::TOTAL_LOGGERS_DELETED + 1 );
  _logger.info( "Total Messengers Created: %ld", Messenger::TOTAL_MESSENGERS_CREATED );
  _logger.info( "Total Messengers Deleted: %ld", Messenger::TOTAL_MESSENGERS_DELETED );

  //average fps
  QueryPerformanceCounter( &_currentTimestamp );
  auto interval = (float( _currentTimestamp.QuadPart - _startTimestamp.QuadPart )) / _freq.QuadPart;
  const auto fps = static_cast<int>(roundf( (_frameCount) / interval ));
  _logger.info( "Average FPS: %d", fps );
}

void Application::setScreenSize( int width, int height ) {
  // can only be set before init process
  ALA_ASSERT((!isInitializing()) && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
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
  ALA_ASSERT((!isInitializing()) && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  _title = title;
}

const std::string& Application::getTitle() const {
  return _title;
}

void Application::setAnimationInterval( float interval ) {
  // can only be set before init process
  ALA_ASSERT((!isInitializing()) && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  ALA_ASSERT(interval >= 1.f / 61);
  QueryPerformanceFrequency( &_freq );
  _animationInterval.QuadPart = LONGLONG( interval * _freq.QuadPart );
}

void Application::setFps( const int fps ) {
  setAnimationInterval( 1.0f / fps );
}

float Application::getAnimationInterval() const {
  return (float( _animationInterval.QuadPart )) / (_freq.QuadPart);
}

void Application::registerResourceInitializer( ResourceInitializer* initializer ) {
  // can only be set before init process
  ALA_ASSERT((!isInitializing()) && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  _resourceInitializers.push_back( initializer );
}

// ================================================
// Main Game Process
// ================================================

void Application::startWithScene( Scene* scene ) {
  // can only be set before init process
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));
  GameManager::get()->replaceScene( scene );
}

void Application::updateInput() {
  // update input
  Input::get()->update();
}

void Application::updateGame( const float delta ) {
  // update game manager
  GameManager::get()->update( delta );

  // update running scene
  auto runningScene = GameManager::get()->getRunningScene();
  if ( runningScene ) {
    runningScene->update( delta );
  }
}

void Application::renderGraphics() {
  if ( !Graphics::get()->beginRendering() ) return;

  // render running scene
  Scene* runningScene = GameManager::get()->getRunningScene();
  if ( runningScene ) {
    runningScene->render();
  }

  Graphics::get()->endRendering();
}

// ================================================
// Initializing & Releasing
// ================================================

void Application::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  // pre init for configuration
  onPreInitialize();

  setToInitializing();

  initComponents();

  initResources();

  setToInitialized();

  // post init for starting
  onPostInitialize();
}

void Application::release() {
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  releaseComponents();

  setToReleased();

  // destroy
  delete this;
}

void Application::initComponents() {
  // validate application properties
  ALA_ASSERT(_screenWidth > 0);
  ALA_ASSERT(_screenHeight > 0);
  ALA_ASSERT(!_title.empty());
  //ALA_ASSERT(_animationInterval >= (1000.0f / 61));

  // windows components
  initWindowHandle();

  // game singleton components
  Graphics* graphics = Graphics::get();
  graphics->_hInstance = _hInstance;
  graphics->_hWnd = _hWnd;
  graphics->_screenWidth = static_cast<UINT>(_screenWidth);
  graphics->_screenHeight = static_cast<UINT>(_screenHeight);
  graphics->initialize();

  Input* input = Input::get();
  input->_hInstance = _hInstance;
  input->_hWnd = _hWnd;
  input->initialize();

  Audio* audio = Audio::get();
  audio->_hWnd = _hWnd;
  audio->initialize();

  GameManager* gameManager = GameManager::get();
  gameManager->_screenWidth = static_cast<float>(_screenWidth);
  gameManager->_screenHeight = static_cast<float>(_screenHeight);

  // seed random
  srand( static_cast<unsigned int>(time( 0 )) );
}

void Application::initResources() {
  // run & release resource initializers
  for ( auto initializer : _resourceInitializers ) {
    if ( initializer ) {
      initializer->run();
    }
    delete initializer;
  }
  _resourceInitializers.clear();

  // load game scope resources
  for ( const auto it : GameManager::get()->_attachedResources ) {
    auto resource = it.second;
    if ( resource->isLoaded() ) continue;
    if ( resource->isGameScope() ) {
      resource->load();
    }
  }
}

void Application::releaseComponents() {
  // running scene
  auto scene = GameManager::get()->getRunningScene();
  scene->release();

  // left objects
  for ( auto node : GameManager::get()->getAllNodes() ) {
    node->release();
  }

  // left resources
  for ( auto resource : GameManager::get()->getAllResources() ) {
    resource->release();
  }

  // game singleton components
  auto gameManager = GameManager::get();
  gameManager->release();

  auto audio = Audio::get();
  audio->release();

  auto input = Input::get();
  input->release();

  auto graphics = Graphics::get();
  graphics->release();
}

// ===================================================
// Platform specific
// ===================================================
int (WINAPIV * __vsnprintf)( char*, size_t, const char*, va_list ) = _vsnprintf;

void Application::run( const HINSTANCE hInstance,
                       const HINSTANCE hPrevInstance,
                       const LPSTR lpCmdLine,
                       const int nCmdShow,
                       const int logStream ) {
  // make sure that application can only init once
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // get run arguments
  _hInstance = hInstance;
  _logStream = logStream;

  // init app
  initialize();

  // game loop
  gameLoop();
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

    _logger.debug( "Allocated Console Logger" );
  }
    break;
  case 2: {
    // ReSharper disable CppDeprecatedEntity
    freopen( "log.txt", "w", stdout );
    // ReSharper restore CppDeprecatedEntity

    _logger.debug( "Allocated File Logger. All your logging data will be store in file `log.txt`" );
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
  _logger.debug( "Created Windows" );

  // show windows
  ShowWindow( _hWnd, SW_SHOW );
  UpdateWindow( _hWnd );
}

void Application::gameLoop() {
  // initial timestamp
  QueryPerformanceCounter( &_startTimestamp );
  _lastTimestamp = _startTimestamp;
  _currentTimestamp = _lastTimestamp;

  LONGLONG interval = 0LL;
  LONGLONG waitMS = 0L;

  // main loop
  while ( !_exiting ) {
    QueryPerformanceCounter( &_currentTimestamp );
    interval = (_currentTimestamp.QuadPart - _lastTimestamp.QuadPart);

    if ( interval >= _animationInterval.QuadPart ) {
      _lastTimestamp.QuadPart = _currentTimestamp.QuadPart;
      _delta = (float( interval )) / _freq.QuadPart;

      //convert to ms
      //_delta *= 1000.f;

      _logger.debug( "dt: %f", _delta );

      _frameCount++;
      //if (_frameCount % 10 == 0) {
      //  auto x = float(_currentTimestamp.QuadPart - _startTimestamp.QuadPart);
      //  auto y = x / _freq.QuadPart;
      //  const int fps = static_cast<int>(roundf((1.0f * _frameCount) / y));
      //  _logger.debug("FPS: %d", fps);
      //}
      processMessage();

      // TODO: what if processMessage() delay a bit, _delta value will deviate from actual one, which decreases game responsiveness
      // TODO: consider move inverval process right before main game update

      processGame();
    }
    else {
      // The precision of timer on Windows is set to highest (1ms) by 'timeBeginPeriod' from above code,
      // but it's still not precise enough. For example, if the precision of timer is 1ms,
      // Sleep(3) may make a sleep of 2ms or 4ms. Therefore, we subtract 1ms here to make Sleep time shorter.
      // If 'waitMS' is equal or less than 1ms, don't sleep and run into next loop to
      // boost CPU to next frame accurately.
      waitMS = (_animationInterval.QuadPart - interval) * 1000L / _freq.QuadPart - 1L;
      if ( waitMS > 1L )
        Sleep( static_cast<DWORD>(waitMS) );
    }
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
  // update input
  updateInput();

  // update game
  updateGame( _delta );

  // render graphics
  renderGraphics();
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
