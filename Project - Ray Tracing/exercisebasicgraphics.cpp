/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "rasterization.h"
#include "io.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void render() {
	frameBuffer.clearColorBuffer();
	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, blue);
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
//	graphicsInit(argc, argv, __FILE__);
//
//	glutDisplayFunc(render);
//	glutReshapeFunc(resize);
//	glutKeyboardFunc(keyboardUtility);
//	glutMouseFunc(mouseUtility);
//
//	frameBuffer.setClearColor(paleGreen);
//
//	glutMainLoop();
    dvec3 pt1(1.0,1.0,1.0);
    dvec3 pt2(2.0,2.4142135624,2.0);
    cout << pointingVector(pt1,pt2) << endl;
}

/** @test    distanceBetween(0, 0, 1, 1) --> 1.41421356237309514547
 * @test    distanceBetween(1, 1, 0, 0) --> 1.41421356237309514547
 * @test    distanceBetween(10, 10, 11, 11) --> 1.41421356237309514547
 * @test    distanceBetween(100, 100, 99, 99) --> 1.41421356237309514547
 * @test    distanceBetween(54, 1, -34, -99) --> 133.2066064427737*/
