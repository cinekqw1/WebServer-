#pragma once

#include <mutex>
#include <condition_variable>

class Application
{
public:
  Application() = default;
  bool isXmlReady();
  void processXml();
  void mainTask();
  bool run();
private:
  std::mutex m_mutex;
  std::condition_variable m_condVar;

  bool m_isXmlReady{false};
};