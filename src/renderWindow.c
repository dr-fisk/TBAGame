#include "renderWindow.h"

/* TODO: Abstract shaders */
const char *vertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

/* Function:    RenderWindow
   Description: Initializes opengl window, shaders (until abstraction) and
                VAO, VBO, and IBO
   Parameters:  uint32_t - Window width
                uint32_t - Window height
                char*    - Window title
   Returns:     None 
 */
RenderWindow::RenderWindow(uint32_t wWidth, uint32_t wHeight, const char *title) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(!glfwInit()) {
    std::cout << "Failed to open window" << std::endl;
    exit(0);
  }

  this->wWidth = wWidth;
  this->wHeight = wHeight;
  this->title = title;
  this->window = glfwCreateWindow(wWidth, wHeight, title, NULL, NULL);
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  if (!window) {
    std::cout << "Error opening window" << std::endl;
    glfwTerminate();
    exit(0);
  }

  /* inits the shaders */
  uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertexShader, NULL);
  glCompileShader(vs);
  uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragmentShader, NULL);
  glCompileShader(fs);
  this->shader = glCreateProgram();
  glAttachShader(shader, vs);
  glAttachShader(shader, fs);
  glLinkProgram(shader);

  glDeleteShader(vs);
  glDeleteShader(fs);

  /* init vao and vbo must be after glewInit*/
  vao = new VertexArray(1);
  Vector2f vc[4] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};
  uint32_t indeces [] = {0,1,2,2,3,0};
  vbo = new VertexBuffer(vc, SQUARE_BYTE_SIZE);
  ib = new IndexBuffer(indeces, 6);
  VertexBufferLayout layout;
  layout.push(2);
  vao->addBuffer(vbo, layout);

  glClearColor(0.0, 0.0, 0.0, 1.0);
}

/* Function:    ~RenderWindow
   Description: Cleans up Window memory and terminates opengl
   Parameters:  None
   Returns:     None 
 */
RenderWindow::~RenderWindow(){
  if (vao != NULL)
    delete vao;
  
  if (vbo != NULL)
    delete vbo;

  if (ib != NULL)
    delete ib;

  glfwDestroyWindow(window);
  glfwTerminate();
}

/* Function:    clear
   Description: Sets window to background color
   Parameters:  None
   Returns:     None 
 */
void RenderWindow::clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

/* Function:    display
   Description: Handles displaying data stored in all buffers
   Parameters:  None
   Returns:     None 
 */
void RenderWindow::display() {
    GLCall(glfwSwapBuffers(window));
    GLCall(glfwPollEvents());
    GLCall(glFlush());
}

/* Function:    getVao
   Description: Returns the VAO associated to window
   Parameters:  None
   Returns:     VertexArray* - Window VAO 
 */
VertexArray* RenderWindow::getVao() {
    return vao;
}

/* Function:    draw
   Description: Handles rendering all buffers to be displayed on window
                Calls should look like clear()->render()->display() then loop
   Parameters:  None
   Returns:     None 
 */

/* TODO: Handle drawing shapes */
void RenderWindow::draw(Rect shape) {
    glUseProgram(shader);
    vao->bind();
    ib->bind();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    ib->unbind();
    vao->unbind();
}

/* Function:    getWindowWidth
   Description: Gets window width
   Parameters:  None
   Returns:     uint32_t - Window width 
 */
uint32_t RenderWindow::getWindowWidth() {
    return wWidth;
}

/* Function:    getWindowHeight
   Description: Gets window height
   Parameters:  None
   Returns:     uint32_t - Window height
 */
uint32_t RenderWindow::getWindowHeight() {
    return wHeight;
}

/* Function:    getWindowWidth
   Description: Checks whether window has been closed
   Parameters:  None
   Returns:     bool - Window open 
 */
bool RenderWindow::isOpen(){
    return !glfwWindowShouldClose(window);
}

void RenderWindow::pollEvent() {
}