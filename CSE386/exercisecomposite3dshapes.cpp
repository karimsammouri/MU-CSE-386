/****************************************************
 * 2016-2021 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <ctime>
#include "defs.h"
#include "io.h"
#include "ishape.h"
#include "framebuffer.h"
#include "raytracer.h"
#include "iscene.h"
#include "light.h"
#include "image.h"
#include "camera.h"
#include "rasterization.h"

double z = 0.0;
double inc = 0.2;

dvec3 cameraPos(0, 10, 10);
dvec3 cameraFocus(0, 5, 0);
dvec3 cameraUp = Y_AXIS;
double cameraFOV = PI_2;
PositionalLight posLight(dvec3(10, 10, 10), white);

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(lightGray);
PerspectiveCamera pCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, WINDOW_WIDTH, WINDOW_HEIGHT);
IScene scene;

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
	rayTrace.raytraceScene(frameBuffer, 0, scene, 3);

	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;
	cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

IPlane* plane = new IPlane(dvec3(0, -2, 0), Y_AXIS);
ICylinderY* cylinderY = new ICylinderY(dvec3(2, 6, 0), 5.0, 3.0);
ISphere* sphere = new ISphere(dvec3(12.0, 0.0, 4.0), 3.0);
IEllipsoid* ellipsoide = new IEllipsoid(dvec3(-20.0, 7, -10.0), dvec3(5.0, 10.0, 5.0));
IClosedCylinderY* closedCylinder = new IClosedCylinderY(dvec3(2.0, 5, 0.0), 7, 4);
//IPlane* plane2 = new IPlane(dvec3(0, 0, 5), Z_AXIS);
ICylinderZ* cylinderZ = new ICylinderZ(dvec3(-8, 6, 5), 5.0, 3);
IPlane* plane1 = new IPlane(dvec3(0,0,0), dvec3(0,1,0));
IPlane* plane2 = new IPlane(dvec3(0,3,0), dvec3(0,-1,0));
IConeY* cone = new IConeY(dvec3(25, 15, -10), 5.0, 10.0);

void buildScene() {
    scene.addOpaqueObject(new VisibleIShape(cone, greenPlastic));
	scene.addOpaqueObject(new VisibleIShape(plane, whitePlastic));
	scene.addOpaqueObject(new VisibleIShape(cylinderY, gold));
	scene.addOpaqueObject(new VisibleIShape(sphere, copper));
	scene.addOpaqueObject(new VisibleIShape(ellipsoide, silver));
   //scene.addTransparentObject(new TransparentIShape(plane2, blue, 0.5));
	scene.addLight(&posLight);
  scene.addOpaqueObject(new VisibleIShape(cylinderZ, redPlastic));
//  scene.addOpaqueObject(new VisibleIShape(plane1, gold));
  //  scene.addOpaqueObject(new VisibleIShape(closedCylinder, gold));
}

int main(int argc, char* argv[]) {
	graphicsInit(argc, argv, __FILE__);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboardUtility);
	glutMouseFunc(mouseUtility);
	buildScene();

	rayTrace.defaultColor = gray;
	glutMainLoop();

	return 0;
}
