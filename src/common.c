#include "common.h"
#include "glcommon.h"

/* Function:    GLClearError
   Description: Clears current opengl error
   Parameters:  None
   Returns:     None 
 */
void GLClearError()
{
  while(glGetError() != GL_NO_ERROR);
}

/* Function:    GLLogCall
   Description: Stores opengl error to output file when opengl complains about misuse
                of functions
                Use of function is to wrap around opengl call ex.
                GLLogCall(glDrawArrays())
   Parameters:  char* - Function name where error occurred
                char* - File name where error occurred
                int   - Line number where error occurred
   Returns:     bool  - Error detected
 */
bool GLLogCall(const char* function, const char *file, int line)
{
  std::ofstream fp("errorLog.txt");
  
  if(GLenum error = glGetError())
  {
    fp << "[OpenGL Error] (" << error << ") In " << function << " located in " << file << " on line number " << line << std::endl;
    fp.close();
    return 0;
  }
  
  fp.close();
  return 1;
}