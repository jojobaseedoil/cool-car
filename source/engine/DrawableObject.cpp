#include "DrawableObject.h"

DrawableObject::DrawableObject(InterfaceScene *owner, GLfloat vertices[], GLuint indexes[], GLint nVertices, GLint nIndexes, GLint DrawOrder):
    mOwner(owner),
    mMode(GL_TRIANGLES),
    mDrawOrder(DrawOrder),
    mNumberOfIndexes(nIndexes),
    mNumberOfVertices(nVertices),
    mModelMatrix(glm::mat4(1.0))
{
    mVertices = new GLfloat[mNumberOfVertices*3];
    mIndexes = new GLuint[mNumberOfIndexes];
    for(int i=0; i<mNumberOfVertices*3; i++)
        mVertices[i] = vertices[i];
    for(int i=0; i<mNumberOfIndexes; i++)
        mIndexes[i] = indexes[i];

    /* Set standard color */
    SetColor(GREEN + RED);

    Shader program = mOwner->GetProgram();

    /* Create buffers to store the vertices */
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    /* Bind Vertex Array Object */
    glBindVertexArray(mVAO);

    /* Copy our vertices array in a vertex buffer for OpenGL to use */
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mNumberOfVertices*3, mVertices, GL_STATIC_DRAW);
    
    /* copy our index array in a element buffer for OpenGL to use */  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mNumberOfIndexes, mIndexes, GL_STATIC_DRAW);
    
    /* Then set the vertex attributes pointers */  
    glVertexAttribPointer(Location::POSITION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(Location::POSITION);
}

DrawableObject::DrawableObject(InterfaceScene *owner, const std::string filename):
    mOwner(owner)
{
    CreateDrawable();
    this->LoadDrawable(filename);
}

DrawableObject::DrawableObject(const DrawableObject &other){
    CreateDrawable();
    *this = other; 
}

DrawableObject::DrawableObject(){
    CreateDrawable();
}

DrawableObject &DrawableObject::operator=(const DrawableObject &other){
    /* self copy */
    if(this == &other){
        return *this;
    }  

    DestroyDrawable();

    mOwner = other.mOwner;
    mDrawOrder = other.mDrawOrder;
    mMode = other.mMode;
    
    mNumberOfIndexes = other.mNumberOfIndexes;
    mNumberOfVertices = other.mNumberOfVertices;
    
    mColor[0] = other.mColor[0];
    mColor[1] = other.mColor[1];
    mColor[2] = other.mColor[2];

    mIndexes = new GLuint[mNumberOfIndexes];
    mVertices = new GLfloat[mNumberOfVertices*3];

    for(int i=0; i<mNumberOfIndexes; i++){
        mIndexes[i] = other.mIndexes[i];
    }

    for(int i=0; i<other.mNumberOfVertices*3; i++){
        mVertices[i] = other.mVertices[i];
    }

    mModelMatrix = other.mModelMatrix;

    mVBO = other.mVBO;
    mVAO = other.mVAO;
    mEBO = other.mEBO;

    return *this;
}

void DrawableObject::CreateDrawable(){
    mIndexes = nullptr;
    mVertices = nullptr;
}

void DrawableObject::DestroyDrawable(){
    delete[] mIndexes;
    delete[] mVertices;
}

DrawableObject::~DrawableObject(){
    DestroyDrawable();
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}


void DrawableObject::Update(float DeltaTime){
    Shader program = mOwner->GetProgram();

    /* Set up Matrices */
    program.SetColor("Color", mColor);
    program.SetModel("Model", mModelMatrix);
    program.SetView("View", mOwner->GetView());
    program.SetProjection("Projection", mOwner->GetProjection());
}
void DrawableObject::ProcessInput(GLFWwindow *window){
    /* Process your drawable object input here... */
}

void DrawableObject::Draw(){
    
    Shader program = mOwner->GetProgram();

    /* Actually drawing */
    program.use();
    glBindVertexArray(mVAO);
    glDrawElements(mMode, mNumberOfIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(program.GetLocation("Position"));    
}

void DrawableObject::SetColor(const glm::vec3&color){
    mColor[0] = (GLfloat)color[0];
    mColor[1] = (GLfloat)color[1];
    mColor[2] = (GLfloat)color[2];
}

void DrawableObject::SetModel(const glm::mat4&model){
    mModelMatrix = model;
}

void DrawableObject::SetDrawMode(const GLenum mode){
    mMode = mode;
}

void DrawableObject::SetWireFrame(bool WireFrameMode){
    if(WireFrameMode){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
}

const GLfloat *DrawableObject::GetColor() const{
    return mColor;
}

const glm::mat4 &DrawableObject::GetModel() const{
    return mModelMatrix;
}

const GLenum DrawableObject::GetDrawMode() const{
    return mMode;
}

const GLint DrawableObject::GetDrawOrder() const{
    return mDrawOrder;
}

void DrawableObject::LoadDrawable(const std::string &filename){
    
    std::filebuf fb;
    if(!fb.open(filename, std::ios::in)){
        std::cerr << "In void DrawableObject::LoadDrawable(const std::string &filename)\n";
        std::cerr << "Could not open file " << filename << "\n";
        exit(EXIT_FAILURE);
    }

    std::istream is(&fb);
    std::string token;
    std::string row;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indexes;

    /* READ DATA */
    while(std::getline(is, row)){    
        /* Get token - coordinate type */
        std::stringstream ss(row);
        ss >> token;

        if(token == "v"){ /* vertices */
            GLfloat x,y,z;
            ss >> x >> y >> z;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

        } else if(token == "f"){ /* indexes */
            for(int i=0; i<3; i++){

                GLuint index_v, index_u, index_n;
                ss >> index_v;
                ss.ignore(); // ignore '/'
                ss >> index_u;
                ss.ignore(); // ignore '/'
                ss >> index_n;
                ss.ignore(); // ignore '/'

                indexes.push_back(index_v-1);
            }
        }
    }
    fb.close();

    /* LOAD DATA INTO 'this' OBJECT */
    DrawableObject *drawable = new DrawableObject(
        mOwner, vertices.data(), indexes.data(), 
        vertices.size()/3, indexes.size(), 0
    );
    
    *this = *drawable;
}
