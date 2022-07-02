#include "Application.hpp"

#include <iostream>
#include <functional>
#include <thread>

bool Application::run()
{
  std::thread thread_1(&Application::mainTask, this);
  std::thread thread_2(&Application::processXml, this);
  
  thread_2.join();
  thread_1.join();
  return 0;
}

void Application::processXml()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  std::cout<<"Loading Data from XML"<<std::endl;
  std::lock_guard<std::mutex> guard(m_mutex);
  m_isXmlReady = true;
  m_condVar.notify_one();
}

bool Application::isXmlReady()
{
  return m_isXmlReady;
}

void Application::mainTask()
{
  std::cout<<"Do Some Handshaking"<<std::endl;  
  std::unique_lock<std::mutex> mlock(m_mutex);
  
  m_condVar.wait(mlock, [this](){return this->isXmlReady();});
  std::cout<<"All components ready"<<std::endl;
}