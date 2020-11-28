#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/Util.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include <iostream>



NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Particle NGL");

}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  m_project = ngl::perspective(45.0f, static_cast<float>(_w)/_h, 0.1f,600.0f );
}


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  m_view = ngl::lookAt({0.0f,5.0f,3.0f},{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f});
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  ngl::VAOPrimitives::createTrianglePlane("ground",4,4,1,1,ngl::Vec3::up());

  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::ShaderLib::setUniform("Colour",0.6f,0.6f,0.6f,1.0f);

  ngl::ShaderLib::loadShader("ParticleShader","shaders/ParticleVertex.glsl",
  "shaders/ParticleFragment.glsl");


 // m_emitter = std::make_unique<Emitter>(1000, ngl::Vec3(0.0f,0.0f,0.0f));
  //m1_emitter = std::make_unique<Emitter>(1000, ngl::Vec3(3.0f, 0.0f, 0.0f));

  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.181636f, -0.809017f, -0.559017f) ,  -( 5 * (ngl::Vec3(0.181636f, -0.809017f, -0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.475528f, -0.809017f, -0.345492f) , -( 5 *(ngl::Vec3(-0.475528f, -0.809017f, -0.345492f)))));

  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.475528f, -0.809017f, 0.345491f) , -( 5 *(ngl::Vec3(-0.475528f, -0.809017f, 0.345491f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.181636f, -0.809017f, 0.559017f) , -( 5 *(ngl::Vec3(0.181636f, -0.809017f, 0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.587785f, -0.809017f, 0.000000f) , -( 5 *(ngl::Vec3(0.587785f, -0.809017f, 0.000000f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.293893f, -0.309017f, -0.904509f) , -( 5 *(ngl::Vec3(0.293893f, -0.309017f, -0.904509f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.769421f, -0.309017f, -0.559017f) , -( 5 *(ngl::Vec3(-0.769421f, -0.309017f, -0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.769421f, -0.309017f, 0.559017f) , -( 5 *(ngl::Vec3(-0.769421f, -0.309017f, 0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.293893f, -0.309017f, 0.904509f) , -( 5 *(ngl::Vec3(0.293893f, -0.309017f, 0.904509f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.951057f, -0.309017f, 0.000000f) , -( 5 *(ngl::Vec3(0.951057f, -0.309017f, 0.000000f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.293893f, 0.309017f, -0.904509f) , -( 5 *(ngl::Vec3(0.293893f, 0.309017f, -0.904509f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.769421f, 0.309017f, -0.559017f) , -( 5 *(ngl::Vec3(-0.769421f, 0.309017f, -0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.769421f, 0.309017f, 0.559017f) , -( 5 *(ngl::Vec3(-0.769421f, 0.309017f, 0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.293893f, 0.309017f, 0.904509f) , -( 5 *(ngl::Vec3(0.293893f, 0.309017f, 0.904509f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.951057f, 0.309017f, 0.000000f) , -( 5 *(ngl::Vec3(0.951057f, 0.309017f, 0.000000f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.181636f, 0.809017f, -0.559017f) , -( 5 *(ngl::Vec3(0.181636f, 0.809017f, -0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.475528f, 0.809017f, -0.345492f) ,  -( 5 *(ngl::Vec3(-0.475528f, 0.809017f, -0.345492f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(-0.475528f, 0.809017f, 0.345491f) , -( 5 *(ngl::Vec3(-0.475528f, 0.809017f, 0.345491f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.181636f, 0.809017f, 0.559017f) , -( 5 *(ngl::Vec3(0.181636f, 0.809017f, 0.559017f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.587785f, 0.809017f, 0.000000f) , -( 5 *(ngl::Vec3(0.587785f, 0.809017f, 0.000000f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.000000f, -1.000000f, 0.000000f) , -( 5 *(ngl::Vec3(0.000000f, -1.000000f, 0.000000f)))));
  emitters.emplace_back(std::make_unique<Emitter>(100, ngl::Vec3(0.000000f, 1.000000f, 0.000000f) , -( 5 *(ngl::Vec3(0.000000f, 1.000000f, 0.000000f)))));


  startTimer(0);
  m_previousTime = std::chrono::high_resolution_clock::now();
  glPointSize(5);
}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  ngl::Mat4 xrot;
  ngl::Mat4 yrot;
  xrot.rotateX(m_win.spinXFace);
  yrot.rotateY(m_win.spinYFace);
  m_globalMouseTX = xrot * yrot;
  m_globalMouseTX.m_m[3][0] = m_modelPos.m_x;
  m_globalMouseTX.m_m[3][1] = m_modelPos.m_y;
  m_globalMouseTX.m_m[3][2] = m_modelPos.m_z;


  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::ShaderLib::setUniform("MVP",m_project*m_view * m_globalMouseTX);
  ngl::VAOPrimitives::draw("ground");
  ngl::ShaderLib::use("ParticleShader");
  ngl::ShaderLib::setUniform("MVP",m_project*m_view * m_globalMouseTX);

 // m_emitter->draw();
  //m1_emitter->draw();

  for (auto& b : emitters)
  {
      b->draw();
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}


void NGLScene::timerEvent(QTimerEvent *)
{

  auto currentTime = std::chrono::high_resolution_clock::now();
  auto delta = std::chrono::duration<float,std::chrono::seconds::period>(currentTime-m_previousTime).count();
  //std::cout<<"delta "<<delta<<'\n';
 //m_emitter->update(delta);
  //m1_emitter->update(delta);

  for (auto& b : emitters)
  {
      b->update(delta);
  }
  update();
  m_previousTime=currentTime;
}


