#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
    CameraPersp         camera; // ������
    Quatf sceneRotation; // ������� ������
    Vec3f eyePosition; // �������� ������
    float cameraDistance; // ���������� �� ������ �� ����

    Vec3f objectPosition;
	Vec3f sx;
	Vec3f sy;

 params::InterfaceGl cameraParams; // ���������������� ��������� ��� ������ � �������
  public:
    void setup() { // ��������� ��� ������� ����������
		sx.x=1;
		sy.y=1;
        objectPosition =  Vec3f::zero();
        cameraDistance = 500; // �������� �������� �� ��������� �� ������ �� ����
        camera.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f ); // �������� ����������� ������

        cameraParams = params::InterfaceGl( "Camera Settings", Vec2i( 225, 200 ) ); // �������� ���� ���������� (��������, ������)
        cameraParams.addParam( "Scene Rotation", &sceneRotation ); // ���� ����� ��������� ��������� �����
        cameraParams.addParam( "Eye Distance", &cameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" ); // ���� ����� ��������� ����������� �� ���� ��� ������ �� ���� ���� ��� ������� (��������� � ���������� http://anttweakbar.sourceforge.net/doc/tools%3aanttweakbar%3avarparamsyntax)
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

    void update() { // ���� ������ ���������� ������ ���������� ���������� � ����� � ������������ ������ �����. ��������� ������ ����
        eyePosition = Vec3f( 0.0f, 0.0f, cameraDistance ); // ����������������� �������� ��������� ������ �� ����� (x, y, ���������� �� ������ �� ����)
        camera.lookAt( eyePosition, Vec3f::zero(), Vec3f::yAxis() ); // ������� (������ �������, �� ��� ��� ���� ���������, ����� ������� ����)
        gl::setMatrices( camera ); // ���������� �������� ����������� � ��� ��� ���������� ��� (��������� ������)

        gl::rotate( sceneRotation ); // ��������� ������� ����� 
    }

    void draw() { // ���� ������ ���������� ������ ����������� ���������� � ����� � ������������ ������ �����. ��������� ������ ����
        gl::clear( Color( 0.1f, 0.5f, 0.5f)); // ������ ��� ��� ����������� �� �����
		glColor3f(1.0f,0.3f,0.7f);
        gl::drawSphere(objectPosition , 25);  // ���������� ��������������
		gl::drawCube(objectPosition + 5*(sy) - 15*(sx), Vec3f( 10.0f, 45.0f, 2.0f ) );
		gl::drawCube(objectPosition + 10*(sy) + 25*(sx), Vec3f( 20.0f, 10.0f, 2.0f ) );
		gl::drawCube(objectPosition + 40*(sy) - 30*(sx), Vec3f( 15.0f, 10.0f, 2.0f ) );
		gl::drawSphere(objectPosition + 40*(sy) - 15*(sx), 15);  // ���������� ��������������
        cameraParams.draw(); // ���������� ���� ����������
    }
};

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )