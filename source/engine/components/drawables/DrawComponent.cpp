#include "DrawComponent.h"
#include "../../actors/actor.h"

DrawComponent::DrawComponent(Actor *owner, GLfloat vertices[], GLuint indexes[], GLint nVertices, GLint nIndexes, GLint DrawOrder):
    Component(owner),
    mMode(GL_TRIANGLES),
    mDrawOrder(DrawOrder),
    mNumberOfIndexes(nIndexes),
    mNumberOfVertices(nVertices)
{
    mVertices = new GLfloat[mNumberOfVertices*3];
    mIndexes = new GLuint[mNumberOfIndexes];
    for(int i=0; i<mNumberOfVertices*3; i++)
        mVertices[i] = vertices[i];
    for(int i=0; i<mNumberOfIndexes; i++)
        mIndexes[i] = indexes[i];

    /* Set standard color */
    auto scene = mOwner->GetScene();
    scene->AddDrawable(this);
    SetColor(GREEN + RED);
    Shader program = scene->GetProgram();

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

DrawComponent::DrawComponent(Actor *owner, const std::string filename):
    Component(owner)
{
    
    CreateDrawable();
    this->LoadDrawable(filename);
}

DrawComponent::DrawComponent(const DrawComponent &other){
    CreateDrawable();
    *this = other;
}

DrawComponent::DrawComponent(){
    CreateDrawable();
}

DrawComponent &DrawComponent::operator=(const DrawComponent &other){
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

    mVBO = other.mVBO;
    mVAO = other.mVAO;
    mEBO = other.mEBO;

    return *this;
}

void DrawComponent::CreateDrawable(){
    mIndexes = nullptr;
    mVertices = nullptr;
}

void DrawComponent::DestroyDrawable(){
    delete[] mIndexes;
    delete[] mVertices;
}

DrawComponent::~DrawComponent(){
    DestroyDrawable();
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

void DrawComponent::Draw(){
    
    InterfaceScene *scene = mOwner->GetScene();
    Shader program = scene->GetProgram();

    /* Set up Matrices */
    program.SetColor("Color", mColor);
    program.SetModel("Model", mOwner->GetModel());
    program.SetView("View", scene->GetView());
    program.SetProjection("Projection", scene->GetProjection());

    /* Actually drawing */
    program.use();
    glBindVertexArray(mVAO);
    glDrawElements(mMode, mNumberOfIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(Location::POSITION);    
}

void DrawComponent::SetColor(const glm::vec3&color){
    mColor[0] = (GLfloat)color[0];
    mColor[1] = (GLfloat)color[1];
    mColor[2] = (GLfloat)color[2];
}

void DrawComponent::SetDrawMode(const GLenum mode){
    mMode = mode;
}

void DrawComponent::SetWireFrame(bool WireFrameMode){
    if(WireFrameMode){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
}

const GLfloat *DrawComponent::GetColor() const{
    return mColor;
}

const GLenum DrawComponent::GetDrawMode() const{
    return mMode;
}

const GLint DrawComponent::GetDrawOrder() const{
    return mDrawOrder;
}

void DrawComponent::LoadDrawable(const std::string &filename){
    
    std::filebuf fb;
    if(!fb.open(filename, std::ios::in)){
        std::cerr << "In void DrawComponent::LoadDrawable(const std::string &filename)\n";
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
    DrawComponent *drawable = new DrawComponent(
        mOwner, vertices.data(), indexes.data(), 
        vertices.size()/3, indexes.size(), 0
    );
    
    *this = *drawable;
}
