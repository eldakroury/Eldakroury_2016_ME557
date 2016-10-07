//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
	float *svertices = new float[123]; //  Dakrory: vertices for triangular strip
	float *scolors = new float[123]; //Dakrory :Colors
	// Strip 1
	svertices[1] = 1; svertices[2] =0 ; svertices[3] =2 ; 
	svertices[4] = 1; svertices[5] = 1; svertices[6] = 2;
	svertices[7] = 1; svertices[8] = 0; svertices[9] = 0;
	svertices[10] = 1; svertices[11] = 1; svertices[12] = 0;
	svertices[13] = 0; svertices[14] = 0; svertices[15] = 0;
	svertices[16] = 0; svertices[17] = 1; svertices[18] = 0;
	svertices[19] = 0; svertices[20] = 0; svertices[21] = 2;
	svertices[22] = 0; svertices[23] = 1; svertices[24] = 2;
	svertices[25] = 1; svertices[26] = 0; svertices[27] = 2;

	scolors[1] = 1; scolors[2] = 1; scolors[3] = 1;
	scolors[4] = 1; scolors[5] = 1; scolors[6] = 1;
	scolors[7] = 1; scolors[8] = 1; scolors[9] = 1;
	scolors[10] = 1; scolors[11] = 1; scolors[12] = 1;
	scolors[13] = 1; scolors[14] = 1; scolors[15] = 1;
	scolors[16] = 1; scolors[17] = 1; scolors[18] = 1;
	scolors[19] = 1; scolors[20] = 1; scolors[21] = 1;
	scolors[22] = 1; scolors[23] = 1; scolors[24] = 1;
	scolors[25] = 1; scolors[26] = 1; scolors[27] = 1;


	//Strip 2
	svertices[28] = 1; svertices[29] =1 ; svertices[30] =0 ;
	svertices[31] = 0; svertices[32] =1 ; svertices[33] = 0;
	svertices[34] = 1; svertices[35] =1 ; svertices[36] = 2;
	svertices[37] = 0; svertices[38] = 1; svertices[39] = 2;

	scolors[28] = 1; scolors[29] = 1; scolors[30] = 1;
	scolors[31] = 1; scolors[32] = 1; scolors[33] = 1;
	scolors[34] = 1; scolors[35] = 1; scolors[36] = 1;
	scolors[37] = 1; scolors[38] = 1; scolors[39] = 1;


	//Strip 3
	svertices[40] = 1; svertices[41] = 0; svertices[42] =0 ;
	svertices[43] = 0; svertices[44] = 0; svertices[45] = 0;
	svertices[46] = 1; svertices[47] = 0; svertices[48] = 2;
	svertices[49] = 0; svertices[50] = 0; svertices[51] = 2;

	scolors[40] = 1; scolors[41] = 1; scolors[42] = 1;
	scolors[43] = 1; scolors[44] = 1; scolors[45] = 1;
	scolors[46] = 1; scolors[47] = 1; scolors[48] = 1;
	scolors[49] = 1; scolors[50] = 1; scolors[51] = 1;
	//Strip 4 
	svertices[52] = 3; svertices[53] = 0; svertices[54] = 2;
	svertices[55] = 3; svertices[56] = 1; svertices[57] = 2;
	svertices[58] = 1; svertices[59] = 0; svertices[60] = 2;
	svertices[61] = 1; svertices[62] = 2; svertices[63] = 2;
	svertices[64] = 0; svertices[65] = 1; svertices[66] = 2;
	svertices[67] = 0; svertices[68] = 2; svertices[69] = 2;

	scolors[52] = 1; scolors[53] = 1; scolors[54] = 1;
	scolors[55] = 1; scolors[56] = 1; scolors[57] = 1;
	scolors[58] = 1; scolors[59] = 1; scolors[60] = 1;
	scolors[61] = 1; scolors[62] = 1; scolors[63] = 1;
	scolors[64] = 1; scolors[65] = 1; scolors[66] = 1;
	scolors[67] = 1; scolors[68] = 1; scolors[69] = 1;
	//Strip 5
	svertices[70] = 3; svertices[71] = 0; svertices[72] =2 ;
	svertices[73] = 3; svertices[74] = 1; svertices[75] =3 ;
	svertices[76] = 3; svertices[77] = 0; svertices[78] =3 ;
	svertices[79] = 3; svertices[80] = 1; svertices[81] =3 ;
	svertices[82] = 1; svertices[83] = 2; svertices[84] =2 ;
	svertices[85] = 1; svertices[86] = 2; svertices[87] = 3;
	svertices[88] = 0; svertices[89] = 2; svertices[90] = 2;
	svertices[91] = 0; svertices[92] = 2; svertices[93] = 3;

	scolors[70] = 1; scolors[71] = 1; scolors[72] = 1;
	scolors[73] = 1; scolors[74] = 1; scolors[75] = 1;
	scolors[76] = 1; scolors[77] = 1; scolors[78] = 1;
	scolors[79] = 1; scolors[80] = 1; scolors[81] = 1;
	scolors[82] = 1; scolors[83] = 1; scolors[84] = 1;
	scolors[85] = 1; scolors[86] = 1; scolors[87] = 1;
	scolors[88] = 1; scolors[89] = 1; scolors[90] = 1;
	scolors[91] = 1; scolors[92] = 1; scolors[93] = 1;
	// Strip 6	
	svertices[94] = 3; svertices[95] = 0; svertices[96] = 2;
	svertices[97] = 3; svertices[98] = 0; svertices[99] = 3;
	svertices[100] = 0; svertices[101] = 0; svertices[102] = 2;
	svertices[103] = 0; svertices[104] = 0; svertices[105] = 3;

	scolors[94] = 1; scolors[95] = 1; scolors[96] = 1;
	scolors[97] = 1; scolors[98] = 1; scolors[99] = 1;
	scolors[100] = 1; scolors[101] = 1; scolors[102 = 1;
	scolors[103] = 1; scolors[104] = 1; scolors[105] = 1;
	//Strip 7
	svertices[106] = 3; svertices[107] =0 ; svertices[108] = 3;
	svertices[109] = 3; svertices[110] = 1; svertices[111] = 3;
	svertices[112] = 1; svertices[113] = 0; svertices[114] = 3;
	svertices[115] = 1; svertices[116] = 2; svertices[117] = 3;
	svertices[118] = 0; svertices[119] = 0; svertices[120] = 3;
	svertices[121] = 0; svertices[122] = 2; svertices[123] = 3;

	scolors[106] = 1; scolors[107] = 1; scolors[108] = 1;
	scolors[109] = 1; scolors[110] = 1; scolors[111] = 1;
	scolors[112] = 1; scolors[113] = 1; scolors[114] = 1;
	scolors[115] = 1; scolors[116] = 1; scolors[117] = 1;
	scolors[118] = 1; scolors[119] = 1; scolors[120] = 1;
	scolors[121] = 1; scolors[122] = 1; scolors[123] = 1;
	
	 
    // use the vertex array object vaoID[0] for this model representation
    
    



    //TODO:
	glGenVertexArrays(1, &vaoID[0]); // dakrory; Create our Vertex Array Object 
									 // Bind the buffer and switch it to an active buffer
	glBindVertexArray(vaoID[0]);
	glGenBuffers(2, vboID); // dakrory: use our VBO

	// dakrory: Vertices data bind vertex buffer and add values to it
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 123 * sizeof(GLfloat), svertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object

	

	//dakrory: colors 
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 123 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

	glEnableVertexAttribArray(1); // Enable the second vertex attribute array

	


	

	//dakrory Colors
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createPolygonModel(void)
{
    // use the vertex array object vaoID[1] for this model representation
  
    //TODO:
    vaoID[1];
    
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

    
        
	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
	glBindVertexArrays(vaoID[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0,9);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 13, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 17, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 23, 8);
	glDrawArrays(GL_TRIANGLE_STRIP, 31, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 35, 6);
	



    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
    renderTriangleStripModel();
    
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        

		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
		// This line renders your Ppolygon model
        renderPolygonModel();
        
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

