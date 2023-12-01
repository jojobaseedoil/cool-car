#pragma once

#include "../component.h"

const glm::vec3 RED   = glm::vec3(1,0,0);
const glm::vec3 GREEN = glm::vec3(0,1,0);
const glm::vec3 BLUE  = glm::vec3(0,0,1);

class Actor;

class DrawComponent : public Component{

public:
	/* Constructors and Destructor */
	DrawComponent(Actor *owner, GLfloat vertices[], GLuint indexes[], GLint nVertices, GLint nIndexes, GLint DrawOrder);
	DrawComponent(Actor *owner, const std::string filename);
	DrawComponent(const DrawComponent&);
	DrawComponent();
	DrawComponent &operator=(const DrawComponent&);
	virtual ~DrawComponent();
	
	/* Public Methods */
	void Draw();

	/* Getters */
	const GLfloat *GetColor() const;
	const glm::mat4 &GetModel() const;
	const GLenum GetDrawMode() const;
	const GLint GetDrawOrder() const;
	/* Setters */
	void SetColor(const glm::vec3&color);
	void SetModel(const glm::mat4&model);
	void SetDrawMode(const GLenum mode);
	void SetWireFrame(bool mode);

	/* Load .obj from blender */
	void LoadDrawable(const std::string &filename); 

protected:
	/* Protected attributes */
	GLint mDrawOrder;
	GLenum mMode;
	
	GLint mNumberOfIndexes;
	GLint mNumberOfVertices;

	GLuint *mIndexes;
	GLfloat mColor[3];
	GLfloat *mVertices;
	
	GLuint mVBO, mVAO, mEBO;

private:
	void CreateDrawable();
	void DestroyDrawable();
}; 