/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/
#include "raytracer.h"
#include "ishape.h"
#include "io.h"

 /**
  * @fn	RayTracer::RayTracer(const color &defa)
  * @brief	Constructs a raytracers.
  * @param	defa	The clear color.
  */

RayTracer::RayTracer(const color& defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer& frameBuffer, int depth,
	const IScene& theScene, int N) const {
	const RaytracingCamera& camera = *theScene.camera;
	const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs;
    const vector<TransparentIShapePtr>& objs2 = theScene.transparentObjs;
	const vector<LightSourcePtr>& lights = theScene.lights;
	
    frameBuffer.setClearColor(defaultColor);
    frameBuffer.clearColorBuffer();
    
    for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
        for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
            DEBUG_PIXEL = (x == xDebug && y == yDebug);
            if (DEBUG_PIXEL) {
                cout << "";
            }
            /* CSE 386 - todo  */
            OpaqueHitRecord opaqueHit;
            TransparentHitRecord transHit;
            color finalColor = black;
            dvec2 rayPositions[N * N];
            int index = 0;
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        rayPositions[index] = dvec2((1.0 / (2.0 * N)) + ((1.0 / N) * i),
                                                   (1.0 / (2.0 * N)) + ((1.0 / N) * j));
                        index++;
                    }
            }
            for (int i = 0; i < N * N; i++) {
                Ray ray = camera.getRay(x + rayPositions[i].x, y + rayPositions[i].y);
                VisibleIShape::findIntersection(ray, objs, opaqueHit);
                TransparentIShape::findIntersection(ray, objs2, transHit);
                if (glm::dot(ray.dir, opaqueHit.normal) > 0.0) {
                    opaqueHit.normal = -opaqueHit.normal;
                }
                dvec3 pt = IShape::movePointOffSurface(opaqueHit.interceptPt, opaqueHit.normal);
                for (unsigned int i = 0; i < lights.size(); i++) {
                    const LightSourcePtr L = lights[i];
                    bool shadow = L->pointIsInAShadow(pt, opaqueHit.normal, objs, camera.getFrame());
                    if (opaqueHit.t != FLT_MAX && transHit.t == FLT_MAX) {
                        finalColor += glm::clamp(L->illuminate(opaqueHit.interceptPt, opaqueHit.normal, opaqueHit.material, camera.getFrame(), shadow), 0.0, 1.0) / (double)(N * N);
                        if (opaqueHit.texture != nullptr) {
                            color texel = opaqueHit.texture->getPixelUV(opaqueHit.u, opaqueHit.v);
                            frameBuffer.setColor(x, y, finalColor * 0.5 + texel * 0.5);
                        } else {
                            frameBuffer.setColor(x, y, finalColor);
                        }
                    } else if (opaqueHit.t == FLT_MAX && transHit.t != FLT_MAX) {
                        finalColor += glm::clamp(((1 - transHit.alpha) * defaultColor) + (transHit.alpha * transHit.transColor), 0.0, 1.0) / ((double)lights.size() * (double)(N * N));
                        frameBuffer.setColor(x, y, finalColor);
                    } else if (opaqueHit.t != FLT_MAX && transHit.t != FLT_MAX) {
                        if (opaqueHit.t < transHit.t) {
                            finalColor += glm::clamp(L->illuminate(opaqueHit.interceptPt, opaqueHit.normal, opaqueHit.material, camera.getFrame(), shadow), 0.0, 1.0) / (double)(N * N);
                            if (opaqueHit.texture != nullptr) {
                                color texel = opaqueHit.texture->getPixelUV(opaqueHit.u, opaqueHit.v);
                                frameBuffer.setColor(x, y, finalColor * 0.5 + texel * 0.5);
                            } else {
                                frameBuffer.setColor(x, y, finalColor);
                            }
                        } else {
                            color source = transHit.transColor / (double)lights.size();
                            color destination = L->illuminate(opaqueHit.interceptPt, opaqueHit.normal, opaqueHit.material, camera.getFrame(), shadow);
                            finalColor += glm::clamp(((1 - transHit.alpha) * destination) + (transHit.alpha * source), 0.0, 1.0) / (double)(N * N);
                            if (opaqueHit.texture != nullptr) {
                                color texel = opaqueHit.texture->getPixelUV(opaqueHit.u, opaqueHit.v);
                                frameBuffer.setColor(x, y, finalColor * 0.5 + texel * 0.5);
                            } else {
                                frameBuffer.setColor(x, y, finalColor);
                            }
                        }
                    }
                }
                frameBuffer.showAxes(x, y, ray, 0.25);			// Displays R/x, G/y, B/z axes
            }
        }
    }
    frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray,
 *											const IScene &theScene,
 *											int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel) const {
	/* CSE 386 - todo  */
	// This might be a useful helper function.
	return black;
}
