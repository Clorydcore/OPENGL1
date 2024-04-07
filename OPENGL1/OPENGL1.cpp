#include "includes.h"

float x = 0.0f, y = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
 
void processInput(GLFWwindow* window, GLint location)
{
    vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    mat4 trans;
    vec = trans * vec;
   
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {

        //Beep(1400, 300);
        
        trans = translate(trans, vec3(0.0f, 0.0f, 0.0f)); 
        /*glUniform2f(location,vec.x += 0.04f, y);*/
       
    }


    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {

        /*  Beep(1400, 300);*/

        translate(mat4(1.0f), vec3(x, y, 0.0f));
        x += 0.04f;
  /*      glUniform2f(location, x += 0.04f, y);*/
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        translate(mat4(1.0f), vec3(x, y, 0.0f));
        x -= 0.04f;
     /*   glUniform2f(location, x -= 0.04f, y);*/

    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        translate(mat4(1.0f), vec3(x, y, 0.0f));
        x -= 0.04f;
       /* glUniform2f(location, x -= 0.04f, y);*/

    }

    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(trans));

}
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

class Cord
{

public:

    double x0 = -0.5f, x1 = -0.5f,  x2 = 0.5f,  x3 =  0.5f;
    double y0 = -0.5f, y1 =  0.5f,  y2 = 0.5f,  y3 = -0.5f;
    double tx0 = 0.0f, tx1 = 0.0f, tx2 = 1.0f,  tx3 = 1.0f;
    double ty0 = 1.0f, ty1 = 0.0f, ty2 = 0.0f,  ty3 = 1.0f;

};

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"

"layout (location = 2) in vec2 aTexCoord;\n"
"uniform mat4 transform ;\n"

"out vec2 TexCoord;\n"
"void main()\n"
"{\n"

//"   gl_Position =  vec4(aPos.x + translation.x ,aPos.y + translation.y ,aPos.z ,1.0);\n"
"   gl_Position = transform * vec4(aPos,1.0f);\n"
"   TexCoord = aTexCoord;\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"

"in vec2 TexCoord;\n"
"\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"   FragColor = texture(ourTexture,TexCoord);\n"
"}\n\0";


int main()
{
    Cord cord;


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }




    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
  
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint location = glGetUniformLocation(shaderProgram, "transform");
  
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    // ”казание вершин (и буфера(ов)) и настройка вершинных атрибутов
    float vertices[] = {
        // координаты                    // текстурные координаты
        cord.x0, cord.y0, 0.0f,    cord.tx0, cord.ty0, // верхн€€ права€ вершина
        cord.x1, cord.y1, 0.0f,    cord.tx1, cord.ty1, // нижн€€ права€ вершина
        cord.x2, cord.y2, 0.0f,    cord.tx2, cord.ty2, // нижн€€ лева€ вершина
        cord.x3, cord.y3, 0.0f,    cord.tx3, cord.ty3 // верхн€€ лева€ вершина 
    };
    unsigned int indices[] = {
        0, 1, 2, // первый треугольник
        0, 2, 3  // второй треугольник
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    //  оординатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   

    // јтрибуты текстурных координат
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
    glBindVertexArray(0);

    unsigned int texture;

    
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

   
    /*stbi_set_flip_vertically_on_load(true);*/

    unsigned char* data = stbi_load("portal.png", &width, &height, &nrChannels, 0); 
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (data)
    {
       
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture!!\n";
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    

    while (!glfwWindowShouldClose(window))
    {
       
        processInput(window,location);

       
        glClearColor(1.0f, 0.0f, 0.5f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

      
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    /*    glBindVertexArray(0);*/
       /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*///каркас
        glUniform2f(location, x, y);

   

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return 0;
}





void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
 
    glViewport(0, 0, width, height);
}