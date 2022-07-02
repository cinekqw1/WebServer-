#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>

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

  std::atomic<bool> m_isXmlReady{false};
};