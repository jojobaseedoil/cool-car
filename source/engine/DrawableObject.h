#pragma once

#include "InterfaceObject.h"

const glm::vec3 RED   = glm::vec3(1,0,0);
const glm::vec3 GREEN = glm::vec3(0,1,0);
const glm::vec3 BLUE  = glm::vec3(0,0,1);

class DrawableObject : public InterfaceObject{

public:
	/* Constructors and Destructor */
	DrawableObject(InterfaceScene *owner, GLfloat vertices[], GLuint indexes[], GLint nVertices, GLint nIndexes, GLint DrawOrder);
	DrawableObject(InterfaceScene *owner, const std::string filename);
	DrawableObject(const DrawableObject&);
	DrawableObject();
	DrawableObject &operator=(const DrawableObject&);
	virtual ~DrawableObject();
	
	/* Public Methods */
	/* Drawable specific */	
	virtual void Draw();
	virtual void Update(float DeltaTime) override;
	virtual void ProcessInput(GLFWwindow *window) override;

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
	InterfaceScene *mOwner;
	GLint mDrawOrder;
	GLenum mMode;
	
	GLint mNumberOfIndexes;
	GLint mNumberOfVertices;

	GLuint *mIndexes;
	GLfloat mColor[3];
	GLfloat *mVertices;

	glm::mat4 mModelMatrix;
	
	GLuint mVBO, mVAO, mEBO;

private:
	void CreateDrawable();
	void DestroyDrawable();
}; 