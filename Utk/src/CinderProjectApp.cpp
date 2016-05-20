#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
    CameraPersp         camera; // Камера
    Quatf sceneRotation; // поворот камеры
    Vec3f eyePosition; // ползиция камеры
    float cameraDistance; // расстояние от камеры до цели

    Vec3f objectPosition;
	Vec3f sx;
	Vec3f sy;

 params::InterfaceGl cameraParams; // Пользовательский интерфейс для работы с камерой
  public:
    void setup() { // вызавется при запуске приложения
		sx.x=1;
		sy.y=1;
        objectPosition =  Vec3f::zero();
        cameraDistance = 500; // выставим значение по умолчанию от камеры до цели
        camera.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f ); // настроим преспективу камеры

        cameraParams = params::InterfaceGl( "Camera Settings", Vec2i( 225, 200 ) ); // создадим окно интерфейса (название, размер)
        cameraParams.addParam( "Scene Rotation", &sceneRotation ); // окно может управлять вращением сцены
        cameraParams.addParam( "Eye Distance", &cameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" ); // окно может управлять расстоянием от того гда камера до того куда она смотрит (подробнее о параметрах http://anttweakbar.sourceforge.net/doc/tools%3aanttweakbar%3avarparamsyntax)
    }

    void keyDown( KeyEvent event ) {
        if( event.getCode() == KeyEvent::KEY_UP) {
            objectPosition.y += 10;
        }
        if( event.getCode() == KeyEvent::KEY_DOWN) {
            objectPosition.y -= 10;
        }
        if( event.getCode() == KeyEvent::KEY_LEFT) {
            objectPosition.x -= 10;
        }
        if( event.getCode() == KeyEvent::KEY_RIGHT) {
            objectPosition.x += 10;
        }
    }

    void update() { // сюда должно разместить логику обновления приложения в связи с наступлением нового кадра. вызывется каждый кадр
        eyePosition = Vec3f( 0.0f, 0.0f, cameraDistance ); // проинициализируем значение рассояния камеры до сцены (x, y, расстояние от камеры до цели)
        camera.lookAt( eyePosition, Vec3f::zero(), Vec3f::yAxis() ); // зададим (откуда смотрим, на что наш взор направлен, какая сторона верх)
        gl::setMatrices( camera ); // рассказали средству отображения о том как отображать мир (выставили камеру)

        gl::rotate( sceneRotation ); // настроили поворот сцены 
    }

    void draw() { // сюда должно разместить логику перересовки приложения в связи с наступлением нового кадра. вызывется каждый кадр
        gl::clear( Color( 0.1f, 0.5f, 0.5f)); // стееть все что нарисованно на сцене
		glColor3f(1.0f,0.3f,0.7f);
        gl::drawSphere(objectPosition , 25);  // нарисовать параленнипипед
		gl::drawCube(objectPosition + 5*(sy) - 15*(sx), Vec3f( 10.0f, 45.0f, 2.0f ) );
		gl::drawCube(objectPosition + 10*(sy) + 25*(sx), Vec3f( 20.0f, 10.0f, 2.0f ) );
		gl::drawCube(objectPosition + 40*(sy) - 30*(sx), Vec3f( 15.0f, 10.0f, 2.0f ) );
		gl::drawSphere(objectPosition + 40*(sy) - 15*(sx), 15);  // нарисовать параленнипипед
        cameraParams.draw(); // нарисовать окно параметров
    }
};

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )