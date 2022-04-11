#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std::placeholders;

class Application
{
  std::mutex m_mutex;
  std::condition_variable m_condVar;
  bool m_bDataLoaded{false};
  bool m_isXmlRdy{false};
public:
  Application(){}
  
  void loadData()
  {
   // Make This Thread sleep for 1 Second
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::cout<<"Loading Data from XML"<<std::endl;
   // Lock The Data structure
   std::lock_guard<std::mutex> guard(m_mutex);
   // Set the flag to true, means data is loaded
   m_bDataLoaded = true;
   // Notify the condition variable
   m_condVar.notify_one();
  }
  
  bool isDataLoaded()
  {
    return m_bDataLoaded;
  }
  
  bool isXmlRdy()
  {
      return m_isXmlRdy;
  }
  
  void loadXml()
  {
      // Make This Thread sleep for 1 Second
   std::this_thread::sleep_for(std::chrono::milliseconds(5000));
   std::cout<<"load xml..."<<std::endl;
   std::lock_guard<std::mutex> guard(m_mutex);
   
   m_isXmlRdy = true;
   m_condVar.notify_one();
  }
  void mainTask()
  {
    std::cout<<"Do Some Handshaking"<<std::endl;
    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);
    std::cout<<"Waiting for the components"<<std::endl;
    m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
    m_condVar.wait(mlock, std::bind(&Application::isXmlRdy, this));
    std::cout<<"Components ready"<<std::endl;
  }
};
int main()
{
   Application app;
   std::thread thread_1(&Application::mainTask, &app);
   std::thread thread_2(&Application::loadData, &app);
   std::thread thread_3(&Application::loadXml, &app);
   thread_3.join();
   thread_2.join();
   thread_1.join();
   return 0;
}