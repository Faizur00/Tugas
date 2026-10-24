#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "3dtransform.h"

// cosf and sinf take radians. The input code counts degrees.
#define DEG_TO_RAD 0.01745329252f

#define CUBE_VERTEX_COUNT 36
#define CUBE_FLOATS_PER_VERTEX 6

typedef struct{
    GLuint vao;
    GLuint vbo;
} Cube;

static Cube CreateCube(float* vertices, size_t sizeInBytes);
static GLuint CreateVertexShader(void);
static GLuint CreateFragmentShader(void);

// 12 triangles, 2 per face, side length 1, centered at the origin
static const float cube_vertices[] = {
    // front +z
    -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
    // back -z
     0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
    // left -x
    -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f,
    // right +x
     0.5f, -0.5f,  0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,   0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
    // top +y
    -0.5f,  0.5f,  0.5f,   0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
    // bottom -y
    -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f
};

// one color per face
static const float cube_colors[] = {
    1.0f, 0.2f, 0.2f,  1.0f, 0.2f, 0.2f,  1.0f, 0.2f, 0.2f,
    1.0f, 0.2f, 0.2f,  1.0f, 0.2f, 0.2f,  1.0f, 0.2f, 0.2f,

    0.2f, 0.8f, 0.2f,  0.2f, 0.8f, 0.2f,  0.2f, 0.8f, 0.2f,
    0.2f, 0.8f, 0.2f,  0.2f, 0.8f, 0.2f,  0.2f, 0.8f, 0.2f,

    0.2f, 0.4f, 1.0f,  0.2f, 0.4f, 1.0f,  0.2f, 0.4f, 1.0f,
    0.2f, 0.4f, 1.0f,  0.2f, 0.4f, 1.0f,  0.2f, 0.4f, 1.0f,

    1.0f, 0.9f, 0.2f,  1.0f, 0.9f, 0.2f,  1.0f, 0.9f, 0.2f,
    1.0f, 0.9f, 0.2f,  1.0f, 0.9f, 0.2f,  1.0f, 0.9f, 0.2f,

    1.0f, 0.3f, 0.9f,  1.0f, 0.3f, 0.9f,  1.0f, 0.3f, 0.9f,
    1.0f, 0.3f, 0.9f,  1.0f, 0.3f, 0.9f,  1.0f, 0.3f, 0.9f,

    0.2f, 1.0f, 1.0f,  0.2f, 1.0f, 1.0f,  0.2f, 1.0f, 1.0f,
    0.2f, 1.0f, 1.0f,  0.2f, 1.0f, 1.0f,  0.2f, 1.0f, 1.0f
};



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
            "OpenGL 3D Test", // window title
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

    // interleaved: x, y, z, r, g, b
    float vertices[ CUBE_VERTEX_COUNT * CUBE_FLOATS_PER_VERTEX ];
    float projected[ CUBE_VERTEX_COUNT * 3 ];

    GLuint program = glCreateProgram();
    GLuint vs = CreateVertexShader();
    GLuint fs = CreateFragmentShader();

    //Linking shader
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);


    glDeleteShader(vs);
    glDeleteShader(fs);

    // fill the color part once, the position part changes every frame
    for (int i = 0; i < CUBE_VERTEX_COUNT; i++){
        for (int c = 0; c < 3; c++){
            vertices[i * CUBE_FLOATS_PER_VERTEX + 3 + c] =
                cube_colors[i * 3 + c];
        }
    }

    Cube cube = CreateCube(vertices, sizeof(vertices));

    // transformation variable
    float tx = 0.0f;
    float ty = 0.0f;
    float tz = -2.5f; // push the cube in front of the camera
    float angle_x = 0.0f;
    float angle_y = 0.0f;
    float angle_z = 0.0f;
    float sx = 1.0f;
    float sy = 1.0f;
    float sz = 1.0f;

    // 3d needs a depth test, or the far faces draw over the near faces
    glEnable(GL_DEPTH_TEST);

    // main applicaiton window loop
    // so this thing kinda like the loopthing on iot and game dev
    while(!glfwWindowShouldClose(window)){
         // process keyboard/mouse and window events
         glfwPollEvents();

         // input listener for transformation variable
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            tx -= 0.02f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            tx += 0.02f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            ty += 0.02f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            ty -= 0.02f;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
            tz -= 0.02f;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            tz += 0.02f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
            glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS){
                sx -= 0.01f;
                sy -= 0.01f;
                sz -= 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
            glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS){
                sx += 0.01f;
                sy += 0.01f;
                sz += 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            angle_y += 2.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
            angle_x += 2.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS){
            angle_z += 2.0f;
        }

        // the projection needs the real pixel ratio, or the cube is stretched
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

        float aspect = 1.0f;

        if (framebufferHeight != 0){
            aspect = (float) framebufferWidth / (float) framebufferHeight;
        }

        Mat4 projection = mat4_perspective(
            60.0f * DEG_TO_RAD,
            aspect,
            0.1f,
            100.0f
        );

        Mat4 translation = mat4_translate(tx, ty, tz);
        Mat4 scaling = mat4_scale(sx, sy, sz);

        Mat4 rotating =
            mat4_mul(
                mat4_rotate_z(angle_z * DEG_TO_RAD),
                mat4_mul(
                    mat4_rotate_y(angle_y * DEG_TO_RAD),
                    mat4_rotate_x(angle_x * DEG_TO_RAD)
                )
            );

        // projection * translation * rotation * scale
        Mat4 transform_mat =
            mat4_mul(
                projection,
                mat4_mul(
                    translation,
                    mat4_mul(rotating, scaling)
                )
            );

        transform_vertices_3d(
            cube_vertices,
            projected,
            CUBE_VERTEX_COUNT,
            transform_mat
        );

        // interleave the projected positions with the colors
        for (int i = 0; i < CUBE_VERTEX_COUNT; i++){
            vertices[i * CUBE_FLOATS_PER_VERTEX + 0] = projected[i * 3 + 0];
            vertices[i * CUBE_FLOATS_PER_VERTEX + 1] = projected[i * 3 + 1];
            vertices[i * CUBE_FLOATS_PER_VERTEX + 2] = projected[i * 3 + 2];
        }

        glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(vertices),
            vertices
        );

        
        // viewport on wayland
        // get the real pixel size of the drawable, then map NDC onto it
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
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         //program here
         glUseProgram(program);
         glBindVertexArray(cube.vao);
         glDrawArrays(GL_TRIANGLES, 0, CUBE_VERTEX_COUNT);


         // show whatever rendered
         glfwSwapBuffers(window);
    }

    // destroy window
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static Cube CreateCube(float* vertices, size_t sizeInBytes){
    Cube cube;
    
    //  creating vbo (vertex buffer object)
    glGenBuffers(1, &cube.vbo);

    // bind the buffer to the current GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);

    // copy the size of our vertices to the buffer, so later we can allocated it ig?
    glBufferData(
        GL_ARRAY_BUFFER, //the buffer target
        sizeInBytes,
        vertices,
        GL_DYNAMIC_DRAW
    );

   // create the Vertex Array Object (VAO)
   glGenVertexArrays(1, &cube.vao);
   glBindVertexArray(cube.vao);

   // position, 3 floats at the start of each vertex
   glVertexAttribPointer(
       0, //idx
       3, //size
       GL_FLOAT, //type
       GL_FALSE, //normalized
       CUBE_FLOATS_PER_VERTEX * sizeof(float), //stride
       (void *)0 //pointer start offset
   );

   glEnableVertexAttribArray(0);

   // color, 3 floats after the position
   glVertexAttribPointer(
       1, //idx
       3, //size
       GL_FLOAT, //type
       GL_FALSE, //normalized
       CUBE_FLOATS_PER_VERTEX * sizeof(float), //stride
       (void *)(3 * sizeof(float)) //pointer start offset
   );

   glEnableVertexAttribArray(1);

   return cube;
}


static GLuint CreateVertexShader(void){
    //the vertex shaders sources
    const char* vertex_sources =
        "#version 460 core\n"
        "\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec3 vertex_color;\n"
        "\n"
        "out vec3 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vertex_color;\n"
        "   gl_Position = vec4(position, 1.0);\n"
        "}\n";

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
        "in vec3 color;\n"
        "out vec4 frag_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    frag_color = vec4(color, 1.0);\n"
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
