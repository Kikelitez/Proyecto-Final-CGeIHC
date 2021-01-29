/*---------------------------------------------------------*/
/* ----------------   Proyecto Final --------------------------*/
/*-----------------    2021-1   ---------------------------*/
/*-----------------    Integrantes   ---------------------------*/
/*------------- Méndez Cabrera Ana Belem ---------------*/
/*---------------------------------------------------------*/

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include<time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>

#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 90.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, -4.0f, -10.0f);

glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movPuerta1=-8.1f, 
		movPuerta2=-9.6f,
		movPuerta3=-11.1f;
//Texture
unsigned int	ventanas;
bool	afuera = true,
		entrada = false,
		sala = false,
		cochera = false,
		lavado = false,
		cocina = false,
		cuartoB = false,
		banio = false,
		balcon = false,
		escaleras = false,
		estanciaP1 = false,
		cuartoFD = false,
		cuartoFI = false,
		jardín = false,
		alberca = false,
		puertaGa = false,
		direccionB = false,
		dirMan = false,
		maxMovPos=false,
		tope1=false,
		tope2=false,
		Flotador=false, 
		DN = false,
		aerea=false,
		caeCoco1=true,
		caeCoco2=false,
		lightState = false;

float	savePoint=0,
		movB,
		movZB,
		movPalmZ, 
		movGotasY=1.8f,
		movGotasZ=-7.7f,
		movPatoZ=30.0f,
		rotPato=180.0f,
		movPatoX,
		movPatoY=0.3f,
		movAgua,
		movFlotador,
		rotFlotador, 
		DNmode, 
		movCocoZ,
		movCoco1Y,
		movCoco2Y,
		lightC;

void animate(void)
{

	/*

	SoundDevice * mysounddevice = SoundDevice::get();

	uint32_t /*ALuint*/ /*sound1 = SoundBuffer::get()->addSoundEffect("../res/spellsounds/spell.ogg");
	/*uint32_t /*ALuint*/ /*sound2 = SoundBuffer::get()->addSoundEffect("../res/spellsounds/magicfail.ogg");

	SoundSource mySpeaker;

	mySpeaker.Play(sound1);*/

	/*Animacion Ballena*/
	if (360 > movB) {
		movB += 0.5f;
	}
	else {
		movB = 0.0f;
	}

	if (direccionB == false) {
		if (20 < movZB) {
			direccionB = true;
		}
		movZB += 0.1f;
	}
	else {
		if (0 > movZB) {
			direccionB = false;
		}
		movZB -= 0.1f;
	}


	/*Animación Palmera*/
	if (maxMovPos==false) {
		if (movPalmZ > 0.25f) {
			maxMovPos = true;
		}
		movPalmZ += 0.05;
	}
	else {

		if (movPalmZ < -0.25f) {
			maxMovPos = false;
		}
		movPalmZ -= 0.05;
	}

	//Cocos
	if (caeCoco1 == false) {
		movCocoZ = movPalmZ;
	}
	else {

		if (movCoco1Y <= -12.0f) {
			movCoco2Y = 0.0f;
			caeCoco2 = true;
			caeCoco1 = false;
		}
		movCoco1Y -= 0.5;
	}

	if (caeCoco2 == false) {
		movCocoZ = movPalmZ;
	}
	else {

		if (movCoco2Y <= -12.0f) {
			movCoco1Y = 0.0f;
			caeCoco1 = true;
			caeCoco2 = false;
		}
		movCoco2Y -= 0.5;
	}

	/*Animación Puerta*/
	if (puertaGa == true) {

		if (movPuerta3 < -6.6) {


			movPuerta3 += 0.1f;

			if (movPuerta3 > -9.60f) {
				movPuerta2 += 0.1f;
			}
			if (movPuerta3 > -8.10f) {
				movPuerta1 += 0.1f;
			}
		}
	}
	else {
		if (movPuerta3 > -11.1) {
			movPuerta3 -= 0.1f;

			if (movPuerta3 > -9.7f) {
				movPuerta2 -= 0.1f;
			}
			if (movPuerta3 > -8.2f) {
				movPuerta1 -= 0.1f;
			}
		}
	}

	/*Animación Regadera*/

	if (dirMan == true) {

		if (movGotasY > -15.8f) {
			movGotasY -= 2.0f;
			movGotasZ += 2.0f;
		}

		else
		{
			movGotasY = 1.8f;
			movGotasZ = -7.7f;

		}


	}
	else {
		movGotasY = 1.8f;
		movGotasZ = -7.7f;
	}

	
	/*Mov agua*/

	if (tope1) {

		if (movAgua < -0.09f) {

			tope2 = true;
			tope1 = false;

		}
		movAgua -= 0.001f;
	}
	else {

		if (movAgua > 0.0f) {
			tope2 = false;
			tope1 = true;
		}

		movAgua += 0.001;
	}

	if (Flotador) {
		if (movFlotador < 0.0f) {

			Flotador = false;
		}
		movFlotador -= 0.01;
	}
	else
	{
		if (movFlotador > 3.3f) {

			Flotador = true;
		}
		movFlotador += 0.01;
	}


	/*Movimiento Pato*/
	if (rotPato > 360) {
		rotPato += 0.5f;
	}
	else {
		rotPato = 0.0f;
	}

	/*Day Night Mode*/
	if (DN == false) {
		if (DNmode < 0.1f) {
			DN = true;
		}
		DNmode -= 0.001f;
	}
	else {
		if (DNmode > 0.7f) {
			DN = false;
		}
		DNmode += 0.001f;
	}


	

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Final", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	//Shader staticShader("Shaders/lightVertex.vs", "Shaders/lightFragment.fs");
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader staticShaderIn("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	//Sha

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------

	Model piso("resources/objects/casa/Desierto.obj");
	//Model casa("resources/objects/casa/Casa.obj");
	Model outside("resources/objects/casa/outside.obj");
	Model Inside("resources/objects/casa/inside.obj");
	
	Model puertaG("resources/objects/Animaciones/Puerta/Puerta Garage.obj");
	Model puertaG1("resources/objects/Animaciones/Puerta/Puerta Garage.obj");
	Model puertaG2("resources/objects/Animaciones/Puerta/Puerta Garage.obj");
	Model puertaG3("resources/objects/Animaciones/Puerta/Puerta Garage.obj");

	Model BaseNubes("resources/objects/Animaciones/Nubes/Nubes Base.obj");
	Model Ballena("resources/objects/Animaciones/Nubes/Ballena.obj");

	Model Pato("resources/objects/Animaciones/Pato/Pato.obj");
	Model PataD("resources/objects/Animaciones/Pato/Pata Der.obj");
	Model PataI("resources/objects/Animaciones/Pato/Pata Izq.obj");

	Model PalmeraB1("resources/objects/Animaciones/Palmera/Palmera Bottom 1.obj");
	Model PalmeraM1("resources/objects/Animaciones/Palmera/Palmera Mid 1.obj");
	Model Palmera1("resources/objects/Animaciones/Palmera/Palmera Top 1.obj");

	Model Coco11("resources/objects/Animaciones/Palmera/Coco1.obj");
	Model Coco12("resources/objects/Animaciones/Palmera/Coco2.obj");


	Model PalmeraB2("resources/objects/Animaciones/Palmera/Palmera Bottom.obj");
	Model PalmeraM2("resources/objects/Animaciones/Palmera/Palmera Mid.obj");
	Model Palmera2("resources/objects/Animaciones/Palmera/Palmera Top.obj");

	Model BaseAlberca("resources/objects/Animaciones/Alberca/Base Alberca.obj");
	Model Agua("resources/objects/Animaciones/Alberca/Agua Alberca.obj");
	Model Flotador("resources/objects/Animaciones/Alberca/Flotador.obj");

	Model BaseManija("resources/objects/Animaciones/Regadera/Base Manija.obj");
	Model Manija("resources/objects/Animaciones/Regadera/Manija.obj");
	Model Regadera("resources/objects/Animaciones/Regadera/Regadera.obj");
	Model Gotas("resources/objects/Animaciones/Regadera/Gotas.obj");

	//camera initial position
	camera.Position.x = -61.1234f;
	camera.Position.y = 11.984f;
	camera.Position.z = -70.0876f;
	
	glEnable(GL_DEPTH_TEST);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(DNmode, DNmode, DNmode));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(DNmode, DNmode, DNmode));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(1.0f - DNmode, 1.0f - DNmode, 1.0f - DNmode));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShader.setFloat("pointLight[0].constant", 0.8);
		staticShader.setFloat("pointLight[0].linear", 0.0f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);


		lightPosition.x = 0.0f;
		lightPosition.y = -4.0f;
		lightPosition.z = -30.0f;

		staticShader.setVec3("pointLight[1].position", lightPosition);
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(1.0f - DNmode, 1.0f - DNmode, 1.0f - DNmode));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.6f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		//casa.Draw(staticShader);
		outside.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.6f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		puertaG.Draw(staticShader);


		tmp = model = glm::rotate(glm::mat4(1.0f), glm::radians(movB), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		BaseNubes.Draw(staticShader);

		model = glm::rotate(tmp, glm::radians(movZB), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		Ballena.Draw(staticShader);

		/*Puerta Garage*/
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, movPuerta1, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);

		puertaG1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, movPuerta2, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);

		puertaG2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, movPuerta3, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);

		puertaG3.Draw(staticShader);

		/*Piso (Desierto)*/
		model = glm::mat4(1.0f);
		tmp = model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);

		piso.Draw(staticShader);

		/*Agregamos la alberca*/
		BaseAlberca.Draw(staticShader);

		tmp = model = glm::translate(model, glm::vec3(0.0f, movAgua, 0.0f));
		staticShader.setMat4("model", model);
		Agua.Draw(staticShader);

		model = glm::translate(model, glm::vec3(0.0f, movAgua, movFlotador));
		staticShader.setMat4("model", model);
		Flotador.Draw(staticShader);


		/*Palmera*/

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);

		PalmeraB1.Draw(staticShader);
		PalmeraB2.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -movPalmZ));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		PalmeraM1.Draw(staticShader);
		PalmeraM2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, movPalmZ));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		Palmera1.Draw(staticShader);
		Palmera2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, movCoco1Y, movCocoZ));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		Coco11.Draw(staticShader);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, movCoco2Y, movCocoZ));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		Coco12.Draw(staticShader);

		/*Pato*/
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 20.0f));
		tmp = model = glm::rotate(model, glm::radians(rotPato), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);


		PataD.Draw(staticShader);
		PataI.Draw(staticShader);

		Pato.Draw(staticShader);

		//*Shader 2 */
		staticShaderIn.use();
		//Setup Advanced Lights
		staticShaderIn.setVec3("viewPos", camera.Position);
		staticShaderIn.setVec3("dirLight.direction", lightDirection);
		staticShaderIn.setVec3("dirLight.ambient", glm::vec3(lightC, lightC, lightC));
		staticShaderIn.setVec3("dirLight.diffuse", glm::vec3(lightC, lightC, lightC));
		staticShaderIn.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

		lightPosition.x = 0.0f;
		lightPosition.y = -4.0f;
		lightPosition.z = -50.0f;

		staticShaderIn.setVec3("pointLight[0].position", lightPosition);
		staticShaderIn.setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShaderIn.setVec3("pointLight[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShaderIn.setVec3("pointLight[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShaderIn.setFloat("pointLight[0].constant", 0.8);
		staticShaderIn.setFloat("pointLight[0].linear", 0.0f);
		staticShaderIn.setFloat("pointLight[0].quadratic", 0.032f);

		lightPosition.x = 0.0f;
		lightPosition.y = -4.0f;
		lightPosition.z = -10.0f;

		staticShaderIn.setVec3("pointLight[1].position", glm::vec3(0.0f, -4.0f, -30.0f));
		staticShaderIn.setVec3("pointLight[1].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShaderIn.setVec3("pointLight[1].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShaderIn.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShaderIn.setFloat("pointLight[1].constant", 1.0f);
		staticShaderIn.setFloat("pointLight[1].linear", 0.009f);
		staticShaderIn.setFloat("pointLight[1].quadratic", 0.032f);

		staticShaderIn.setFloat("material_shininess", 32.0f);

		model = glm::mat4(1.0f);
		staticShaderIn.setMat4("projection", projection);
		staticShaderIn.setMat4("view", view);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.6f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		Inside.Draw(staticShaderIn);

		BaseManija.Draw(staticShaderIn);
		Regadera.Draw(staticShaderIn);
		Manija.Draw(staticShaderIn);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.5f, movGotasY, movGotasZ));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		Gotas.Draw(staticShaderIn);


		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

void manage(int opc) {

	if (opc != 14) {
		savePoint = opc;
	}

	switch (opc) {
	
	case 0: 	
		camera.Position.x = -61.1234f;
		camera.Position.y = 11.984f;
		camera.Position.z = -70.0876f;
		break;
	
	case 1:
		camera.Position.x = -3.35105f;
		camera.Position.y = 3.39027f;
		camera.Position.z = -57.9338f;
		break;

	case 2:
		camera.Position.x = -0.056394f;
		camera.Position.y = 6.32688f;
		camera.Position.z = -13.7465f;
		break;
	case 3:
		camera.Position.x = -16.7037f;
		camera.Position.y = 3.65226f;
		camera.Position.z = 0.0953793f;
		break;
	case 4:
		camera.Position.x = -17.282f;
		camera.Position.y = 4.79778f;
		camera.Position.z = -13.6028f;
		break;
	case 5:
		camera.Position.x = -18.082f;
		camera.Position.y = 4.9519f;
		camera.Position.z = -31.7912f;
		break;
	case 6: 
		camera.Position.x = 14.6048f;
		camera.Position.y = 8.24899f;
		camera.Position.z = -37.7961f;
		break;
	case 7:
		camera.Position.x = 6.22753f;
		camera.Position.y = 12.5269f;
		camera.Position.z = -12.9561f;
		break;
	case 8:
		camera.Position.x = -7.99961f;
		camera.Position.y = 12.1573f;
		camera.Position.z = -26.1682f;
		break;
	case 9:
		camera.Position.x = -27.967f;
		camera.Position.y = 11.2607f;
		camera.Position.z = -42.4058f;
		break;
	case 10:
		camera.Position.x = -11.2814f;
		camera.Position.y = 12.1814f;
		camera.Position.z = -7.66068f;
		break;
	case 11:
		camera.Position.x = -16.3554f;
		camera.Position.y = 11.3066f;
		camera.Position.z = 2.24631f;
		break;
	case 12:
		camera.Position.x = 5.31822f;
		camera.Position.y = 11.8186f;
		camera.Position.z = 1.49801f;
		break;

	case 13 : 
		camera.Position.x = 8.73906f;
		camera.Position.y = 11.3195f;
		camera.Position.z = 34.4331f;
		break;

	default:
		camera.Position.x = 80.4996f;
		camera.Position.y = 95.152f;
		camera.Position.z = 68.129f;

	}
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		DNmode += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		DNmode -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (lightState) {
			lightState = false;
			lightC = DNmode/2;
		}
		else {
			lightState = true;
			lightC = 0.6f;

		}
	}

	
	if (aerea) {
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			aerea = false;
			manage(savePoint);
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			aerea = true;
			manage(14);
		}

		if (afuera) {
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				afuera = false;
				entrada = true;
				manage(1);

			}
		}
		else if (entrada) {

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				entrada = false;
				sala = true;
				manage(2);
			}

			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{

				entrada = false;
				afuera = true;
				manage(0);
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				alberca = true;
				entrada = false;
				manage(13);
			}

			if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			{
				if (puertaGa) {
					puertaGa = false;
				}
				else {
					puertaGa = true;
				}

			}

		}
		else if (sala) {

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				sala = false;
				cocina = true;
				manage(3);
			}
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				sala = false;
				lavado = true;
				manage(4);
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				sala = false;
				escaleras = true;
				manage(6);
			}

			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				sala = false;
				cochera = true;
				manage(5);
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				sala = false;
				entrada = true;
				manage(1);
			}

		}
		else if (cochera) {

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				cochera = false;
				sala = true;
				manage(2);
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				cochera = false;
				entrada = true;
				manage(1);
			}
			if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			{
				if (puertaGa) {
					puertaGa = false;
				}
				else {
					puertaGa = true;
				}
			}


		}
		else if (lavado) {
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				lavado = false;
				cocina = true;
				manage(3);
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				lavado = false;
				sala = true;
				manage(2);
			}
		}
		else if (cocina) {
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				cocina = false;
				lavado = true;
				manage(4);
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				cocina = false;
				sala = true;
				manage(2);
			}
		}
		else if (escaleras) {
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				escaleras = false;
				sala = true;
				manage(2);
			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				escaleras = false;
				estanciaP1 = true;
				manage(7);
			}
		}

		else if (estanciaP1) {
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{

				estanciaP1 = false;
				escaleras = true;
				manage(6);
			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				estanciaP1 = false;
				cuartoFD = true;
				manage(11);
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{

				estanciaP1 = false;
				cuartoFI = true;
				manage(12);
			}
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				estanciaP1 = false;
				banio = true;
				manage(10);
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				estanciaP1 = false;
				cuartoB = true;
				manage(8);
			}
		}

		else if (banio) {
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{

				banio = false;
				estanciaP1 = true;
				manage(7);
			}

			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			{

				if (dirMan == true) {
					dirMan = false;
				}
				else {
					dirMan = true;
				}

			}

		}
		else if (cuartoB) {
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{

				cuartoB = false;
				estanciaP1 = true;
				manage(7);
			}

			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{

				cuartoB = false;
				balcon = true;
				manage(9);
			}
		}
		else if (balcon) {
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{

				balcon = false;
				cuartoB = true;
				manage(8);
			}
		}
		else if (cuartoFD) {
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{

				cuartoFD = false;
				estanciaP1 = true;
				manage(7);
			}
		}
		else if (cuartoFI) {
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{

				cuartoFI = false;
				estanciaP1 = true;
				manage(7);
			}
		}

		else if (alberca) {
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{

				alberca = false;
				entrada = true;
				manage(1);
			}
		}

	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}