#include "shape.h"


extern GLubyte indices[]=	{0,	1,	2,	//front
							0,	2,	3,
							4,	5,	6,	//Right
							4,	6,	7, 
							8,	9,	10,	//Back
							8,	10,	11,
							12,	13,	14,	//Left
							12,	14,	15,
							16,	17,	18,	//Top
							16,	18,	19,
							20,	21,	22,	//Bottom
							20,	22,	23
							};
													// Front
extern float verts[] = {	-1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
													// Right
							1.0, 1.0, 1.0,			// Vertex #4
							1.0, -1.0, 1.0,			// Vertex #5
							1.0, -1.0, -1.0,		// Vertex #6
							1.0, 1.0, -1.0,			// Vertex #7
													// Back
							1.0, 1.0, -1.0,			// Vertex #8
							1.0, -1.0, -1.0,		// Vertex #9
							-1.0, -1.0, -1.0,		// Vertex #10
							-1.0, 1.0, -1.0,		// Vertex #11
													// Left
							-1.0, 1.0, -1.0,			// Vertex #12
							-1.0, -1.0, -1.0,		// Vertex #13
							-1.0, -1.0, 1.0,		// Vertex #14
							-1.0, 1.0, 1.0,			// Vertex #15
													// Top
							-1.0, 1.0, -1.0,		// Vertex #16
							-1.0, 1.0, 1.0,			// Vertex #17
							1.0, 1.0, 1.0,			// Vertex #18
							1.0, 1.0, -1.0,			// Vertex #19
													// Bottom
							-1.0, -1.0, -1.0,		// Vertex #20
							-1.0, -1.0, 1.0,		// Vertex #21
							1.0,  -1.0, 1.0,		// Vertex #22
							1.0, -1.0, -1.0			// Vertex #23
						};

extern float verts2[] = { -1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							-1.0, 1.0, 1.0,			// Vertex #0
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
						};

extern float norms[] = {0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
 						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
						1.0, 0.0, 0.0,		//4
						1.0, 0.0, 0.0,		//5
						1.0, 0.0, 0.0,		//6
						1.0, 0.0, 0.0,		//7
						0.0, 0.0, -1.0,		//8
						0.0, 0.0, -1.0,		//9
						0.0, 0.0, -1.0,		//10
						0.0, 0.0, -1.0,		//11
						-1.0, 0.0, 0.0,		//12
						-1.0, 0.0, 0.0,		//13
						-1.0, 0.0, 0.0,		//14
						-1.0, 0.0, 0.0,		//15
						0.0, 1.0, 0.0,		//16
						0.0, 1.0, 0.0,		//17
						0.0, 1.0, 0.0,		//18
						0.0, 1.0, 0.0,		//19
						0.0, -1.0, 0.0,		//20
						0.0, -1.0, 0.0,		//21
						0.0, -1.0, 0.0,		//22
						0.0, -1.0, 0.0		//23
						};

extern float norms2[] = { 0.0, 0.0, 1.0,	//0
						0.0, 0.0, 1.0,		//1
						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
						0.0, 0.0, 1.0,		//4
						0.0, 0.0, 1.0,		//5
						};

extern float texcoords[]= {	0.0, 0.0, 		//0
							0.0, 1.0, 		//1
 							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							0.0, 0.0, 		//4
							0.0, 1.0, 		//5
							1.0, 1.0, 		//6
							1.0, 0.0, 		//7
							0.0, 0.0, 		//8
							0.0, 1.0, 		//9
							1.0, 1.0, 		//10
							1.0, 0.0, 		//11
							0.0, 0.0, 		//12
							0.0, 1.0, 		//13
							1.0, 1.0, 		//14
							1.0, 0.0, 		//15
							0.0, 0.0, 		//16
							0.0, 1.0, 		//17
							1.0, 1.0, 		//18
							1.0, 0.0, 		//19
							0.0, 0.0, 		//20
							0.0, 1.0, 		//21
							1.0, 1.0, 		//22
							1.0, 0.0		//23
							};

extern float texcoords2[] = { 0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							0.0, 0.0, 		//0
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							};

void Shape::render1()
{
	// add code to render the cube (above) using method 1
	// glArrayElement()

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);


	glBegin(GL_TRIANGLES);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(0);
	glArrayElement(2);
	glArrayElement(3);
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void Shape::render2()
{
	// add code to render the cube (above) using method 2
	// glDrawArrays()
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts2);
	glNormalPointer(GL_FLOAT, 0, norms2);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords2);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void Shape::render3()
{
	// add code to render the cube (above) using method 3
	// glDrawElements()
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glEnable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glDisable(GL_DEPTH_TEST);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);

}

void Shape::drawDisc(float res)
{
	vertD.clear();

	float interval = (2 * pi) / res;
	float num = 0;

	for (int i = 0; i <= res; i++)
	{
		vertD.push_back(0.0f);
		vertD.push_back(0.0f);
		vertD.push_back(0.0f);

		vertD.push_back(cos(num));
		vertD.push_back(sin(num));
		vertD.push_back(0.0f);

		if (i == res)
		{
			vertD.push_back(0.0f);
			vertD.push_back(0.0f);
			vertD.push_back(0.0f);
		}
		else
		{
			vertD.push_back(cos(num + interval));
			vertD.push_back(sin(num + interval));
			vertD.push_back(0.0f);
		}
		num += interval;
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertD.data());
	glDrawArrays(GL_TRIANGLES, 0, res * 3);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Shape::drawSquare()
{
	float res = 15;
	float div = (10 / res);
	float total = (res * res * 4);
	std::vector<float> vertices;
	std::vector<float> norm;
	std::vector<float> textures;

	for (float i = -5; i < 5; i += div)
	{
		for (float j = -5; j < 5; j += div)
		{
			norm.push_back(0);
			norm.push_back(1);
			norm.push_back(0);
			vertices.push_back(i);
			vertices.push_back(0);
			vertices.push_back(j);

			norm.push_back(0);
			norm.push_back(1);
			norm.push_back(0);
			vertices.push_back(i);
			vertices.push_back(0);
			vertices.push_back(j + div);

			norm.push_back(0);
			norm.push_back(1);
			norm.push_back(0);
			vertices.push_back(i + div);
			vertices.push_back(0);
			vertices.push_back(j + div);

			norm.push_back(0);
			norm.push_back(1);
			norm.push_back(0);
			vertices.push_back(i + div);
			vertices.push_back(0);
			vertices.push_back(j);
		}
	}

	for (float i = 0; i < 10; i += div)
	{
		for (float j = 0; j < 10; j += div)
		{
			textures.push_back(i);
			textures.push_back(j);

			textures.push_back(i);
			textures.push_back(j + div);

			textures.push_back(i + div);
			textures.push_back(j + div);

			textures.push_back(i + div);
			textures.push_back(j);
		}
	}
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, textures.data());
	glNormalPointer(GL_FLOAT, 0, norm.data());
	glVertexPointer(3, GL_FLOAT, 0, vertices.data());

	glDrawArrays(GL_QUADS, 0, total);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	norm.clear();
	vertices.clear();
	textures.clear();

}

//Make a floor with many normals
void Shape::drawWall()
{
	float res = 15;
	float div = (10 / res);
	float total = (res * res * 4);
	std::vector<float> wallVertices;
	std::vector<float> wallNorm;
	std::vector<float> wallTextures;

	for (float i = -5; i < 5; i += div)
	{
		for (float j = -5; j < 5; j += div)
		{
			wallNorm.push_back(0);
			wallNorm.push_back(1);
			wallNorm.push_back(0);
			wallVertices.push_back(i);
			wallVertices.push_back(0);
			wallVertices.push_back(j);

			wallNorm.push_back(0);
			wallNorm.push_back(1);
			wallNorm.push_back(0);
			wallVertices.push_back(i);
			wallVertices.push_back(0);
			wallVertices.push_back(j + div);

			wallNorm.push_back(0);
			wallNorm.push_back(1);
			wallNorm.push_back(0);
			wallVertices.push_back(i + div);
			wallVertices.push_back(0);
			wallVertices.push_back(j + div);

			wallNorm.push_back(0);
			wallNorm.push_back(1);
			wallNorm.push_back(0);
			wallVertices.push_back(i + div);
			wallVertices.push_back(0);
			wallVertices.push_back(j);
		}
	}

	for (float i = 0; i < 10; i += div)
	{
		for (float j = 0; j < 10; j += div)
		{
			wallTextures.push_back(i);
			wallTextures.push_back(j);

			wallTextures.push_back(i);
			wallTextures.push_back(j + div);

			wallTextures.push_back(i + div);
			wallTextures.push_back(j + div);

			wallTextures.push_back(i + div);
			wallTextures.push_back(j);
		}
	}
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, wallTextures.data());
	glNormalPointer(GL_FLOAT, 0, wallNorm.data());
	glVertexPointer(3, GL_FLOAT, 0, wallVertices.data());

	glDrawArrays(GL_QUADS, 0, total);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	wallNorm.clear();
	wallVertices.clear();
	wallTextures.clear();

}