#include "Scene.h"

Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	rotation = 0;
	speed = 1;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);	
	glClearStencil(0);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	
	// Load models
	desk.load("models/table.obj", "models/table.jpg");
	podracer.load("models/spaceship.obj", "models/spaceship.jpg");

	// Initialise variables
	rotation = 0;
	shininess[0] = 50;

	//Initialise Textures
	skybox = SOIL_load_OGL_texture
		(
			"gfx/Skybox.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	nightbox = SOIL_load_OGL_texture
		(
			"gfx/nightbox.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	shadowImposter = SOIL_load_OGL_texture
		(
			"gfx/imposter.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	blueWall = SOIL_load_OGL_texture
		(
			"gfx/Room/blueWall.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	greyWall = SOIL_load_OGL_texture
		(
			"gfx/Room/greyWall.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	ceiling = SOIL_load_OGL_texture
		(
			"gfx/Room/ceiling.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	carpet = SOIL_load_OGL_texture
		(
			"gfx/Room/carpet.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
}

void Scene::update(float dt)
{
	// Handle user input
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	//Activate wireframe mode
	if (input->isKeyDown('r') || input->isKeyDown('R'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	//Camera controls
	if (fixed == false && input->isKeyDown('w') || input->isKeyDown('W'))
	{
		mainCamera.moveForward((speed * dt));
	}

	if (fixed == false && input->isKeyDown('s') || input->isKeyDown('S'))
	{
		mainCamera.moveForward((-speed * dt));
	}

	if (fixed == false && input->isKeyDown('d') || input->isKeyDown('D'))
	{
		mainCamera.moveRight((speed * dt));
	}

	if (fixed == false && input->isKeyDown('a') || input->isKeyDown('A'))
	{
		mainCamera.moveRight((-speed * dt));
	}

	if (fixed == false && input->isKeyDown('i') || input->isKeyDown('I'))
	{
		mainCamera.rotateUp(1);
	}

	if (fixed == false && input->isKeyDown('k') || input->isKeyDown('K'))
	{
		mainCamera.rotateUp(-1);
	}

	if (fixed == false && input->isKeyDown('l') || input->isKeyDown('L'))
	{
		mainCamera.rotateRight(1);
	}

	if (fixed == false && input->isKeyDown('j') || input->isKeyDown('J'))
	{
		mainCamera.rotateRight(-1);
	}
	//This is to increase and decrease the resolution of the disc
	if (input->isKeyDown('q') || input->isKeyDown('Q'))
	{
		res -= 1;
		if (res <= 0)
		{
			res = 5;
		}
	}

	if (input->isKeyDown('e') || input->isKeyDown('E'))
	{
		res += 1;
		if (res >= 20)
		{
			res = 20;
		}
	}
	//Toggle between cameras
	if (input->isKeyDown('c') || input->isKeyDown('C'))
	{
		input->SetKeyUp('c');
		if (fixed == true)
		{
			fixed = false;
		}
		else if (fixed == false)
		{
			fixed = true;
		}
	}
	//Switch between day and night
	if (input->isKeyDown('n') || input->isKeyDown('N'))
	{
		input->SetKeyUp('n');
		if (lightOn == true)
		{
			lightOn = false;
			day = false;
		}
		else if (lightOn == false)
		{
			lightOn = true;
			day = true;
		}
	}
	//Mouse controls
	if (fixed == false)
	{
		mainCamera.RotateYaw(400 - input->getMouseX(), dt, -0.5);
		mainCamera.RotatePitch(300 - input->getMouseY(), dt, 0.5);
	}

	glutWarpPointer(400, 300);

	// Calculate FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
	rotation = rotation + 1;
}

void Scene::drawSkybox()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
		//Move skybox to the location of the second camera
		if (fixed == true)
		{
			glTranslatef(10,5,10);
		}
		//Move the skybox to the camera
		if (fixed == false)
		{
			glTranslatef(mainCamera.GetX(), mainCamera.GetY(), mainCamera.GetZ());
		}
		glScalef(1, 1, 1);
		if (day == true)
		{
			glBindTexture(GL_TEXTURE_2D, skybox);
		}
		if (day == false)
		{
			glBindTexture(GL_TEXTURE_2D, nightbox);
		}
		glDisable(GL_DEPTH_TEST);
		glBegin(GL_QUADS);

		// front face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.25f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	
		// back face
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.75f, 0.25f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.75f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.25f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		// right face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.25f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		// left face
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		// bottom face
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.75f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.75f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		// top face
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glEnd();
		glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Scene::drawMirror()
{
	//Make a Square for where the mirror is
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glScalef(20, 10, 20);
	glBegin(GL_QUADS);
	// back face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}

void Scene::drawBuilding() 
{
	//Draw three walls and a floor
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(0, 5, 0);
	glScalef(20, 10, 20);
	glBindTexture(GL_TEXTURE_2D, blueWall);
		glBegin(GL_QUADS);
		// front face
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
	glBindTexture(GL_TEXTURE_2D, greyWall);
	glBegin(GL_QUADS);
		// right face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		// left face
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D, carpet);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glPushMatrix();
		glScalef(0.1f, 0.1f, 0.1f);
		glTranslatef(0, -5, 0);
		Shape1.drawSquare();
	glPopMatrix();
	glPopMatrix();
}

void Scene::drawShadow()
{
	//Draw the shadows underneath the pod racers
	glBindTexture(GL_TEXTURE_2D, shadowImposter);
	glPushMatrix();
	glTranslatef(0, -1.9, 0);
	glScalef(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//Bottom
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, -0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.0f, -0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.5f);

	glEnd();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Scene::renderScene() 
{
	glEnable(GL_DEPTH_TEST);
	drawBuilding();
	glPushMatrix();
		//Render the desk in the middle of the room
		glRotatef(90, 0, 1, 0);
		glScalef(0.03f, 0.03f, 0.03f);
		glEnable(GL_TEXTURE_2D);
		desk.render();
		glPushMatrix();
			//Draw a rotated podracer and draw a shadow under it
			glScalef(50, 50, 50);
			glRotatef(-rotation, 0, 1, 0);
			glTranslatef(2, 2, 0);
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
			drawShadow();
			glDisable(GL_BLEND);
			glEnable(GL_LIGHTING);
			podracer.render();
			glPushMatrix();
				//Another podracer with a shadow underneath but this one rotates the first podracer
				glRotatef((-rotation)-2, 0, 1, 0);
				glTranslatef(2, 0, 0);
				glDisable(GL_LIGHTING);
				glEnable(GL_BLEND);
				drawShadow();
				glDisable(GL_BLEND);
				glEnable(GL_LIGHTING);
				podracer.render();
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void Scene::render()
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	if (fixed == false)
	{
		gluLookAt(mainCamera.GetX(), mainCamera.GetY(), mainCamera.GetZ(), mainCamera.GetLookX(), mainCamera.GetLookY(), mainCamera.GetLookZ(), mainCamera.GetUpX(), mainCamera.GetUpY(), mainCamera.GetUpZ());
	}

	if (fixed == true)
	{
		gluLookAt(10, 5, 10, fixedCamera.GetLookX(), fixedCamera.GetLookY(), fixedCamera.GetLookZ(), fixedCamera.GetUpX(), fixedCamera.GetUpY(), fixedCamera.GetUpZ());
	}


	//Set up light variables
	GLfloat Light_Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };
	GLfloat Light_Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat Light_Ambient1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat Light_Diffuse1[] = { 1.0f, 0.3f, 0.0f, 1.0f };
	GLfloat Light_Position1[] = { 1.0f, 1.0f, 0.0f, 0.0f };
	GLfloat spot_Direction1[] = { 0.0f, -1.0f, 0.0f };
	GLfloat Light_Specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_colour[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 50 };
	GLfloat high_shininess[] = { 100 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
	GLfloat high_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat no_spec[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);

	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular1);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.125);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	//Enable lights
	glEnable(GL_LIGHT0);
	//Depending on the lightOn variable the light will turn on and off
	if (lightOn == true) 
	{
		glEnable(GL_LIGHT1);
	}
	if (lightOn == false)
	{
		glDisable(GL_LIGHT1);
	}
	glEnable(GL_NORMALIZE);
	drawSkybox();

	// Render geometry here -------------------------------------
	//Set up the stencil buffer with the mirror
	/////////////////
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glDisable(GL_DEPTH_TEST);
		drawMirror();
	glEnable(GL_DEPTH_TEST);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//Draw the reflected room
	glPushMatrix();
		glScalef(1.0f, 1.0f, -1.0f);
		glTranslatef(0, 0, -20);
		renderScene();
	glPopMatrix();

	//////////////////////
	//Draw the transparent mirror
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);

	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);

	drawMirror();

	glDisable(GL_BLEND);
	//Draw the normal scene
	renderScene();

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}