#pragma once

#include "../component.h"
#include "../../components/texture.h"
#include "../../utils/libs.h"

struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

const glm::vec3 RED   = glm::vec3(1,0,0);
const glm::vec3 GREEN = glm::vec3(0,1,0);
const glm::vec3 BLUE  = glm::vec3(0,0,1);

class Actor;

class DrawComponent : public Component{

public:
	/* Constructors and Destructor */
	DrawComponent(Actor *owner, const Vertex *vertices, const GLuint *indices, const GLuint nVertices, const GLuint nIndices, GLint DrawOrder=10);
	DrawComponent(Actor *owner, const std::string &filename, const int DrawOrder=10);
	virtual ~DrawComponent();
	
	/* Public Methods */
	void Draw();

	/* Getters */
	const glm::mat4 &GetModel() const;
	const GLenum GetDrawMode() const;
	const GLint GetDrawOrder() const;
	/* Setters */
	void SetModel(const glm::mat4&model);
	void SetDrawMode(const GLenum mode);
	void SetWireFrame(bool mode);
	/* Load .obj from blender */

protected:
	void CreateBuffers(const Vertex *vertices, const GLuint *indices, const GLuint nVertices, const GLuint nIndices);
	
	/* Protected attributes */
	GLint mDrawOrder;
	GLenum mMode;
	
	GLuint mNumIndices;
	GLuint mNumVertices;

	GLuint mVBO, mVAO, mEBO;
}; 