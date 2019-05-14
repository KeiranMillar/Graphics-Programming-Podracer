// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include <SOIL.h>
#include "Vector3.h"
#include "camera.h"
#include "Shape.h"
#include "Model.h"
// Further includes should go here:


class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	float speed, rotation, rotation2, rotation3, rotation4;
	float res = 20;
	bool fixed = false, lightOn = false, day = false;
	GLfloat shininess[1];
	camera mainCamera, fixedCamera;
	Shape Shape1;
	Model desk, podracer;
	GLfloat shadowMatrix[16];


protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void drawSkybox();
	void drawBuilding();
	void drawShadow();
	void renderScene();
	void drawMirror();
	GLuint skybox, nightbox, blueWall, greyWall, ceiling, carpet, shadowImposter;


	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[12];
	char mouseText[20];
};

#endif