#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "transform.h"

typedef struct{
    GLuint vao;
    GLuint vbo;
} Triangle;

static Triangle CreateTriangle(int idx, float* vertices, size_t sizeInBytes);
static GLuint CreateVertexShader(void);
static GLuint CreateFragmentShader(void);




int main(void){
    // GLFW Initialize
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    if (!glfwInit()){
        return -1;
    }
    
    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        4
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        6
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window =
        glfwCreateWindow(
            1280, // resolution
            720,
            "OpenGL Test", // window title
            NULL, // monitor
            NULL // window hints
        );

    if (window == NULL){
        fprintf(stderr, "failed to create window\n");
        glfwTerminate();
        return -1;
    }


    // make this window current  context
    glfwMakeContextCurrent(window);

    GLenum glew_status = glewInit();

    if (glew_status != GLEW_OK) {
        fprintf(
            stderr,
            "Failed to initialize GLEW: %s\n",
            glewGetErrorString(glew_status)
        );

        glfwDestroyWindow(window);
        glfwTerminate();

        return EXIT_FAILURE;
    }


    int framebufferWidth;
    int framebufferHeight;
    float vertices1[] = {
        0.025f,0.25f, 0.025f,-0.25f, 0.25f, -0.25f
    };
    
    float vertices2[6];  
    
    GLuint program = glCreateProgram();
    GLuint vs = CreateVertexShader();
    GLuint fs = CreateFragmentShader();

    //Linking shader
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);


    glDeleteShader(vs);
    glDeleteShader(fs);

    Triangle triangleData = CreateTriangle(0, vertices2, sizeof(vertices2));

    // transformation variable
    float tx = 0.0f;
    float ty = 0.0f;
    float angle = 0.0f;
    float sx = 1.0f;
    float sy = 1.0f;

    // main applicaiton window loop
    // so this thing kinda like the loopthing on iot and game dev
    while(!glfwWindowShouldClose(window)){
         // process keyboard/mouse and window events
         glfwPollEvents();

         // input listener for transformation variable
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            tx -= 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            tx += 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            ty += 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
             ty -= 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            angle = angle + 30.0;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
            glfwGetKey(window, GLFW_KEY_MINUS)){
                sx = sx - 0.01f;
                sy = sx - 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
            glfwGetKey(window, GLFW_KEY_EQUAL)){
                sx = sx + 0.01f;
                sy = sx + 0.01f;
        }

         Mat3 scaling = scale(sx, sy);
         Mat3 rotating = rotate(angle);
         Mat3 translation = translate(tx, ty);

         Mat3 transform_mat = 
             mat3_mul(
                 translation,
                 mat3_mul(
                     rotating, scaling
                 )
             );
        
        transform_vertices(vertices1, vertices2, 3, transform_mat);
        glBindBuffer(GL_ARRAY_BUFFER, triangleData.vbo);
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(vertices2),
            vertices2
        );

        
        // viewport on wayland
        // get the real pixel size of the drawable, then map NDC onto it
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);

        // choose color for clearing frame buffer
         glClearColor(
             0.1f,
             0.1f,
             0.1f,
             1.0f
        );

         // clearing the buffer
         // rendering process here
         glClear(GL_COLOR_BUFFER_BIT);

         //program here
         glUseProgram(program);
         glBindVertexArray(triangleData.vao);
         glDrawArrays(GL_TRIANGLES, 0, 3);


         // show whatever rendered
         glfwSwapBuffers(window);
    }

    // destroy window
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static Triangle CreateTriangle(int idx, float* vertices, size_t sizeInBytes){
   Triangle triangle;
    
    //  creating vbo (vertex buffer object)
    GLuint vbo;
    // bind vbo to an indentifier
    glGenBuffers(1, &triangle.vbo);

    // bind the buffer to the current GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);

    // copy the size of our vertices to the buffer, so later we can allocated it ig?
    glBufferData(
        GL_ARRAY_BUFFER, //the buffer target
        sizeInBytes,
        vertices,
        GL_STATIC_DRAW
    );

    



   // create the Vertex Array Object (VAO)
   GLuint vao;
   glGenVertexArrays(1, &triangle.vao);
   glBindVertexArray(triangle.vao);

   glVertexAttribPointer(
       0, //idx
       2, //size
       GL_FLOAT, //type
       GL_FALSE, //normalized
       2 * sizeof(float), //stride
       (void *)0 //pointer start offset
   );

   // enable array at idx 0
   glEnableVertexAttribArray(0);

   return triangle;
}


static GLuint CreateVertexShader(void){
    //the vertex shaders sources
    const char* vertex_sources =
        "#version 460 core\n"
        "\n"
        "layout (location = 0) in vec2 position;\n" //creating vec2 var in loc = 0 named positon
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 0.0, 1.0);\n"
        "}\n;";

    // creating the shaders
    GLuint VertexShaders = glCreateShader(GL_VERTEX_SHADER);

    // binding the shaders to the sources
    glShaderSource(
        VertexShaders, // the shaders
        1, // count
        &vertex_sources, // the sources
        NULL // length
    );

    // compiling
    glCompileShader(VertexShaders);
    // error catch
    GLint Success = 0;
    glGetShaderiv(VertexShaders, GL_COMPILE_STATUS, &Success);

    if (!Success){
        fprintf(stderr, "Vertex Shader compilation failed:\n");
        exit(EXIT_FAILURE);
    }

    return VertexShaders;
}

static GLuint CreateFragmentShader(void){
    //the Fragment shaders sources
    const char* FragmentSources =
        "#version 460 core\n"
        "\n"
        "out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    color = vec4(1.0, 0.2, 0.2, 1.0);\n"
        "}\n";

    // creating the shaders
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // binding the shaders to the sources
    glShaderSource(
        FragmentShader, // the shaders
        1, // count
        &FragmentSources, // the sources
        NULL // length
    );

    // compiling
    glCompileShader(FragmentShader);
    // error catch
    GLint Success = 0;
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);

    if (!Success){
        fprintf(stderr, "Fragment Shader compilation failed:\n");
        exit(EXIT_FAILURE);
    }

return FragmentShader;
}
