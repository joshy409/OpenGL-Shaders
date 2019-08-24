#include "context.h"
#include "render.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "tiny_obj_loader.h"

#include "Windows.h"
#include "algorithm"
#include <vector>
#include <iostream>


#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc


float randFloat();
vertex* convertVertices(std::vector<tinyobj::real_t> verticies);
unsigned int* convertIndices(std::vector<tinyobj::index_t> indices);

int main() {
	context game;
	game.init(640, 480, "Source3");

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif

	//std::string inputfile = "cube.obj";
	//tinyobj::attrib_t attrib;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;

	//std::string warn;
	//std::string err;

	//bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	//if (!warn.empty()) {
	//	std::cout << warn << std::endl;
	//}

	//if (!err.empty()) {
	//	std::cerr << err << std::endl;
	//}

	//if (!ret) {
	//	exit(1);
	//}

	//std::vector<vertex> objVerts;
	//std::vector<unsigned int> objIndices;

	//// Loop over shapes
	//for (size_t s = 0; s < shapes.size(); s++) {


	//	// Loop over faces(polygon)
	//	size_t index_offset = 0;
	//	for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
	//		int fv = shapes[s].mesh.num_face_vertices[f];

	//		// Loop over vertices in the face.
	//		for (size_t v = 0; v < fv; v++) {
	//			// access to vertex
	//			tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
	//			tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
	//			tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
	//			tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
	//			tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
	//			tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
	//			tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
	//			tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
	//			tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

	//			objVerts.emplace_back(vertex{ {vx, vy, vz, 1.f} });
	//			objIndices.emplace_back((unsigned int)idx.vertex_index);

	//			// Optional: vertex colors
	//			// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
	//			// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
	//			// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
	//		}
	//		index_offset += fv;

	//		// per-face material
	//		shapes[s].mesh.material_ids[f];
	//	}
	//}

	//std::cout << attrib.vertices.size() << std::endl; //24
	//std::cout << shapes[0].mesh.indices.size() << std::endl; //36
	//
	///*for (size_t i = 0; i < attrib.vertices.size(); i++)
	//{
	//	std::cout << attrib.vertices[i] << std::endl;
	//}*/
	//vertex* a = convertVertices(attrib.vertices);
	//unsigned int* b = convertIndices(shapes[0].mesh.indices);
	////geometry cube = makeGeometry(convertVertices(attrib.vertices), attrib.vertices.size() / 3, (unsigned int *)shapes[0].mesh.indices.data(), shapes[0].mesh.indices.size());
	//geometry cube = makeGeometry(objVerts.data(), objVerts.size(), objIndices.data(), objIndices.size());
	//delete[] a;


	vertex triVerts[] =
	{
		{{-.5f,-.5f,0,1},{ 1.0, 0.0, 0.0, 1}, {0.f,0.f}},
		{{.5f,-.5f,0,1},{ 0.0, 1.0, 0.0, 1}, {1.f,0.f}},
		{{0,.5f,0,1},{ 0, 0.0, 1.0, 1}, {.5f,.1f}}
	};



	unsigned int triIndices[] = { 0,1,2 };

	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);

	texture texture = loadTexture("soulspear_diffuse.tga");

	/*vertex quadVerts[] =
	{
		{{-1.0f,-1.0f,0,1},{ 1.0, 0.0, 0.0, 1}},
		{{-1.0f,1.0f,0,1 },{ 0.0, 1.0, 0.0, 1}},
		{{1.0f,1.0f,0,1},{ 0, 0.0, 1.0, 1}},
		{{1.0f,-1.0f,0,1},{0, .5f, 0, 1}}
	};

	unsigned int quadIndicies[] = { 0,1,2,0,2,3 };

	geometry quad = makeGeometry(quadVerts, 4, quadIndicies, 6);*/

	const char * basicVert =
		"#version 430\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec4 vertColor;\n"
		"layout (location = 2) in vec2 uv;\n"
		"layout (location = 0) uniform mat4 proj;\n"
		"layout (location = 1) uniform mat4 view;\n"
		"layout (location = 2) uniform mat4 model;\n"
		"out vec4 vColor;\n"
		"void main() {gl_Position = proj * view * model * position; vColor = vertColor;}";

	const char * basicFrag =
		"#version 330\n"
		"in vec4 vColor;\n"
		"out vec4 fragColor;\n"
		"void main() {fragColor = vec4(1.0, 0.0, 0.0, 1.0);}";

	shader basicShader = makeShader(basicVert, basicFrag);

	glm::mat4 triModel = glm::identity<glm::mat4>();
	glm::mat4 quadModel = glm::identity<glm::mat4>();
	glm::mat4 camProj = glm::perspective(glm::radians(45.f), 640.f / 480.f, 0.1f, 100.f);
	glm::mat4 camView = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	setUniform(basicShader, 0, camProj);
	setUniform(basicShader, 1, camView);
	setUniform(basicShader, 2, triModel);

	int i = 0;
	while (!game.shouldClose()) {
		game.tick();
		game.clear();

		assert(glGetError() == GL_NO_ERROR);

		//triModel = glm::rotate(triModel, glm::radians(5.f), glm::vec3(0, 1, 0));
		//setUniform(basicShader, 2, triModel);


		/*if (i > 50) {
			for (auto &vert : triVerts)
			{
				vert.color = { randFloat(), randFloat(), randFloat(), 1 };
			}
			i = 0;
		}

		geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);

		//triModel = glm::rotate(triModel, glm::radians(5.f), glm::vec3(0, 1, 0));
		
		if (GetKeyState('W') & 0x8000) {
			triModel = glm::translate(triModel, glm::vec3(0, .01f, 0));
		}

		if (GetKeyState('S') & 0x8000) {
			triModel = glm::translate(triModel, glm::vec3(0,-.01f, 0));
		}

		if (GetKeyState('A') & 0x8000) {
			triModel = glm::translate(triModel, glm::vec3(0.01f, 0,0));
		}

		if (GetKeyState('D') & 0x8000) {
			triModel = glm::translate(triModel, glm::vec3( -.01f, 0,0));
		}
		
		if (GetKeyState('I') & 0x8000) {
			camView = glm::translate(camView, glm::vec3(0, .01f, 0));
		}

		if (GetKeyState('K') & 0x8000) {
			camView = glm::translate(camView, glm::vec3(0, -.01f, 0));
		}

		if (GetKeyState('J') & 0x8000) {
			camView = glm::translate(camView, glm::vec3(0.01f, 0, 0));
		}

		if (GetKeyState('L') & 0x8000) {
			camView = glm::translate(camView, glm::vec3(-.01f, 0, 0));
		}
		
		setUniform(basicShader, 1, camView);

		setUniform(basicShader, 2, quadModel);
		draw(basicShader,quad);
		setUniform(basicShader, 2, triModel);
		draw(basicShader, triangle);

		i++;
		freeGeometry(triangle);

	*/	

		draw(basicShader, triangle);
	}
	game.term();
	return 0;
}

float randFloat() {
	return ((float)rand()) / (float)RAND_MAX;
	
}

vertex* convertVertices(std::vector<tinyobj::real_t> vertices)
{	
	int n = vertices.size();
	int count = 0;
	vertex * b = new vertex[n];
	for (size_t i = 0; i < n; i+=3)
	{
		vertex a = { {vertices[i],vertices[i+1],vertices[i+2],1.f} };
		b[count] = a;
		count++;
	}
	return b;
}

unsigned int* convertIndices(std::vector<tinyobj::index_t> indices)
{
	int n = indices.size();
	int count = 0;
	unsigned int b[100];
	for (size_t i = 0; i < n; i++)
	{
		b[i] = indices[i].vertex_index;
	}
	return b;
}
