/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "MyApp.h"
#include "../scenes/IntroScene.h"
#include "MyResourceInitializer.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::onPreInitialize() {
  // configurations
  setScreenSize( 480, 360 );
  setTitle( "Aladdin" );
  setFps( 60 );
  Logger::setLogLevel( Logger::LOG_INFO );

  // resource initializers
  registerResourceInitializer( new MyResourceInitializer() );
}

void MyApp::onPostInitialize() {
  // starter scene
  startWithScene( new IntroScene() );
}
