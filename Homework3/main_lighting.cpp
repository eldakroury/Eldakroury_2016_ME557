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
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "GLSphere.h"


using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;



int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);
    
    //////////Mohamed Eldakroury
	// Create Appearnces for every sphere
	GLAppearance*appearance_1 = new GLAppearance(vs_string_simple_shader_410,fs_string_simple_shader_410);
	GLAppearance*appearance_2 = new GLAppearance();
	GLAppearance*appearance_3 = new GLAppearance();
	GLAppearance*appearance_4 = new GLAppearance();

	//Create Light SOURCES
	GLSpotLightSource light_Source1;
	light_Source1._lightPos = glm::vec4(10, 10, 0.0, 1);
	light_Source1._ambient_intensity = 0.1;
	light_Source1._specular_intensity = 9.0;
	light_Source1._diffuse_intensity = 4.0;
	light_Source1._attenuation_coeff = 0.02;
	light_Source1._cone_angle = 30.0;
	light_Source1._cone_direction = glm::vec3(-2.0, -1.0, 0.0);

	GLSpotLightSource light_Source2;
	light_Source2._lightPos = glm::vec4(10, 10, 0.0, 1);
	light_Source2._ambient_intensity = 0.1;
	light_Source2._specular_intensity = 9.0;
	light_Source2._diffuse_intensity = 4.0;
	light_Source2._attenuation_coeff = 0.02;
	light_Source2._cone_angle = 30.0;
	light_Source2._cone_direction = glm::vec3(-2.0, -1.0, 0.0);

	GLDirectLightSource light_Source3;
	light_Source3._lightPos = glm::vec4(20.0, 0.0, 0.0, 0.0);
	light_Source3._ambient_intensity = 0.1;
	light_Source3._specular_intensity = 5.5;
	light_Source3._diffuse_intensity = 1.0;
	light_Source3._attenuation_coeff = 0.02;

	//Add Lightsources to Appearences
	appearance_1->addLightSource(light_Source3);
	appearance_2->addLightSource(light_Source3);
	appearance_3->addLightSource(light_Source1);
	appearance_4->addLightSource(light_Source2);

	
	//Create Materials
	GLMaterial material_1;
	material_1._diffuse_material = glm::vec3(1.0, 1.0, 0.0);
	material_1._ambient_material = glm::vec3(1.0, 1.0, 0.0);
	material_1._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_1._shininess = 8.0;
	
	GLMaterial material_2;
	material_2._diffuse_material = glm::vec3(20.0, 1.0, 0.0);
	material_2._ambient_material = glm::vec3(0.60, 0.30, 0.0);
	material_2._specular_material = glm::vec3(0.8, 1.0, 1.0);
	material_2._shininess = 500.0;

	GLMaterial material_3;
	material_3._diffuse_material = glm::vec3(1.0, 1.0, 0.0);
	material_3._ambient_material = glm::vec3(1.0, 1.0, 0.0);
	material_3._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_3._shininess = 8.0;

	GLMaterial material_4;
	material_4._diffuse_material = glm::vec3(1.0, 1.0, 0.0);
	material_4._ambient_material = glm::vec3(1.0, 1.0, 0.0);
	material_4._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_4._shininess = 8.0;

	//Add Materials to Appearences
	appearance_1->setMaterial(material_1);
	appearance_1->setMaterial(material_2);
	appearance_1->setMaterial(material_3);
	appearance_1->setMaterial(material_4);

	// Finalize
	void finalize(void);

	//Create Spheres
    
	GLSphere* sphere_1 = new GLSphere(0.0, 0.0, 0.0, 10.0, 40, 20);
	sphere_1->setApperance(*appearance_1);
	//sphere_1->init();
	GLSphere* sphere_2 = new GLSphere(30.0, 0.0, 0.0, 10.0, 40, 20);
	sphere_2->setApperance(*appearance_2);
	//sphere_2->init();
	GLSphere* sphere_3 = new GLSphere(60.0, 0.0, 0.0, 10.0, 40, 20);
	sphere_3->setApperance(*appearance_3);
	//sphere_3->init();
	GLSphere* sphere_4 = new GLSphere(90.0, 0.0, 0.0, 10.0, 40, 20);
	sphere_4->setApperance(*appearance_4);
	//sphere_4->init();

	
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(80.0f, 80.0f, 3.0f), glm::vec3(10.0, 10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    //sphere->enableNormalVectorRenderer();
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
    
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());
        // Mohamed Eldakroury Editions

        // draw the objects
        cs->draw();
        
        sphere_1->draw();
		sphere_2->draw();
		sphere_3->draw();
		sphere_4->draw();
        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

