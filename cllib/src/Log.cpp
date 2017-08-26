#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdarg>
#include <assert.h>
#include "Log.h"

//初始化静态变量
Log::SYNCSET Log::m_logSyncSet = LL_UNSYNC;
Log::SYNCLIST * Log::m_syncInfoList = nullptr;
int Log::m_syncInfoNumber = 0;
std::mutex Log::MUTEX;
bool Log::m_b_FirstTime = true;
std::string Log::m_s_LogFilePrev;
bool Log::m_openSuccess = false;
bool Log::m_isOpen = false;
bool Log::m_totWrite = false;
std::fstream Log::m_logFile;
std::fstream Log::m_totLogFile;

Log::Log(const int level, const char * format, ...) : m_localTime(nullptr)
{
  va_list args;
  char tempString[2048] = { 0 };  // 格式化字符串最大支持2048个字节
  va_start(args, format);

  vsnprintf_s(tempString, sizeof(tempString), format, args);
  std::string info(tempString);
  std::string logFlag;
  std::string logText;
  std::stringstream timeStream;

  if (LL_ERROR == level) {
#if (defined _DEBUG) || (defined DEBUG)
	 assert(false);
#else
	 logFlag = "[ERROR]";
#endif
  }
  else if (LL_WARNING == level) {
	 logFlag = "[WARNING]";
  }
  else if (LL_INFORMATION == level) {
	 logFlag = "[INFORMATION]";
  }
  else {
	 error();
  }

  if (nullptr == m_localTime) {
	 //如果构造时获取时间出错， 重新获取时间 
	 if (!getTime()) {
		//获取时间出错
		m_localTime = nullptr;
	 }
  }

  if (nullptr == m_localTime) {
	 //无法获取时间时直接写入日志信息
	 logText = logFlag + info + "\n";
  }
  else {
	 timeStream.fill('0');
	 timeStream << "[" << std::setw(4) << m_localTime->tm_year << "/" << std::setw(2) << m_localTime->tm_mon << "/"
		<< std::setw(2) << m_localTime->tm_mday << " " << std::setw(2) << m_localTime->tm_hour << ":"
		<< std::setw(2) << m_localTime->tm_min << ":" << std::setw(2) << m_localTime->tm_sec << "]";
	 logText = logFlag + timeStream.str() + info + "\n";
  }


  if (readyEnviron(level)) {
	 MUTEX.lock();
	 writeLogFile(logText);
	 MUTEX.unlock();
  }
}

bool Log::readyEnviron(const int level)
{
  m_level = level;
  if (!m_localTime && !getTime()) {
	 //获取日志时间出错
	 m_localTime = nullptr;
  }

  if (level == LL_ERROR) {
	 openLogFile(level, errorPosition);

  }
  else if (level == LL_WARNING) {
	 openLogFile(level, waringPosition);
  }
  else if (level == LL_INFORMATION && m_logSyncSet == LL_UNSYNC) {
	 openLogFile(level, informationPosition);
  }
  else if (level == LL_INFORMATION && m_logSyncSet == LL_SYNC) {
	 m_totWrite = false;
	 return true;
  }
  else {
	 error();
	 return false;
  }

  return true;
}

//打开日志文件
void Log::openLogFile(const int level, const char * file)
{
  MUTEX.lock();

  if (m_isOpen) {
	 m_logFile.close();
	 m_totLogFile.close();
	 m_isOpen = false;
  }

  if (m_b_FirstTime) {
	 m_logFile.open(informationPosition, std::ios::out | std::ios::trunc);
	 m_logFile.close();
	 m_logFile.open(waringPosition, std::ios::out | std::ios::trunc);
	 m_logFile.close();
	 m_logFile.open(errorPosition, std::ios::out | std::ios::trunc);
	 m_logFile.close();
	 m_b_FirstTime = false;
  }

  if (level == LL_ERROR || level == LL_WARNING || level == LL_INFORMATION) {
	 m_logFile.open(file, std::ios::out | std::ios::app);
	 if (m_logFile.is_open()) {
		m_openSuccess = true;
		m_level = level;
		m_isOpen = true;
	 }
	 else {
		error();
	 }
  }

  m_totLogFile.open((totPosition + m_s_LogFilePrev + totFileName).c_str(), std::ios::out | std::ios::app);
  if (m_totLogFile.is_open()) {
	 m_totWrite = true;
  }
}

//写日志
bool Log::writeLogFile(std::string & logText)
{
  if (!m_isOpen && (m_logSyncSet == LL_UNSYNC && m_level == LL_INFORMATION)) {
	 error();
	 return false;
  }

  if (m_logSyncSet == LL_UNSYNC || m_level != LL_INFORMATION) {
	 // 非异步写入
	 m_logFile.write(logText.c_str(), logText.size());

	 if (m_totWrite) {
		m_totLogFile.write(logText.c_str(), logText.size());
	 }
  }
  else if (m_logSyncSet == LL_SYNC && m_level == LL_INFORMATION) {
	 if (!addSyncNode(logText)) {
		error();
		return false;
	 }
  }
  else {
	 error();
	 return false;
  }

  delete m_localTime;
  m_localTime = nullptr;
  return true;
}

//获取日志时间
bool Log::getTime()
{
  errno_t err;
  time_t nowTime = time(NULL);

  try {
	 m_localTime = new tm;
  }
  catch (std::bad_alloc) {
	 return false;
  }

  if (err = localtime_s(m_localTime, &nowTime)) {
	 // 获取时间出错
	 return false;
  }

  m_localTime->tm_mon += 1;
  m_localTime->tm_year += 1900;

  if (m_b_FirstTime) {
	 std::stringstream temp;
	 temp << m_localTime->tm_year << m_localTime->tm_mon << m_localTime->tm_mday << m_localTime->tm_hour << m_localTime->tm_min << m_localTime->tm_sec;
	 temp >> m_s_LogFilePrev;
  }
  return true;
}

//日志系统错误处理
void Log::error()
{
  if (!m_totWrite) {
	 return;
  }

  std::string logText;
  std::stringstream timeStream;

  if (nullptr == m_localTime) {
	 //如果构造时获取时间出错， 重新获取时间 
	 if (!getTime()) {
		//获取时间出错
		m_localTime = nullptr;
	 }
  }

  if (nullptr == m_localTime) {
	 //无法获取时间时直接写入日志信息
	 logText = "[ERROR]" + std::string("LogSystemError") + "\n";
  }
  else {
	 timeStream.fill('0');
	 timeStream << "[" << std::setw(4) << m_localTime->tm_year << "/" << std::setw(2) << m_localTime->tm_mon << "/"
		<< std::setw(2) << m_localTime->tm_mday << " " << std::setw(2) << m_localTime->tm_hour << ":"
		<< std::setw(2) << m_localTime->tm_min << ":" << std::setw(2) << m_localTime->tm_sec << "]";
	 logText = "[ERROR]" + timeStream.str() + "LogSystemError" + "\n";
  }

  m_totLogFile.write(logText.c_str(), logText.size());

}

//添加异步节点
bool Log::addSyncNode(std::string & info)
{
  if (!m_syncInfoList) {
	 try {
		m_syncInfoNumber++;
		m_syncInfoList = new SYNCLIST(info);
	 }
	 catch (std::bad_alloc) {
		m_syncInfoNumber--;
		m_syncInfoList = nullptr;
		error();
		return false;
	 }
  }
  else {
	 SYNCLIST * node = m_syncInfoList;
	 while (node->next) {
		node = node->next;
	 }
	 try {
		m_syncInfoNumber++;
		node->next = new SYNCLIST(info);
	 }
	 catch (std::bad_alloc) {
		m_syncInfoNumber--;
		node = nullptr;
		error();
		return false;
	 }
  }
  return true;
}

//异步写处理
bool Log::syncWrite()
{
  // 异步消息数20写一次
  if (m_syncInfoNumber >= 20) {
	 SYNCSET oldSet = m_logSyncSet;
	 m_logSyncSet = LL_UNSYNC;
	 if (readyEnviron(LL_INFORMATION)) {

		MUTEX.lock();
		while (m_syncInfoList && m_syncInfoNumber--) {
		  if (writeLogFile(m_syncInfoList->_logInfo)) {
			 SYNCLIST * node = m_syncInfoList;
			 m_syncInfoList = m_syncInfoList->next;
			 delete node;
		  }
		  else {
			 // 写入出错停止继续写入
			 m_syncInfoNumber++;
			 m_logSyncSet = oldSet;
			 return false;
		  }
		}
		MUTEX.unlock();
	 }
	 m_logSyncSet = oldSet;
  }
  return true;
}

//设置SYNC
void Log::setSYNC(SYNCSET set)
{
  if (set == LL_SYNC || set == LL_UNSYNC)
	 m_logSyncSet = set;
}

//异步流清理
void Log::cleanSYNC()
{
  SYNCLIST * node = m_syncInfoList;
  while (m_syncInfoList) {
	 m_syncInfoList = m_syncInfoList->next;
	 delete node;
	 node = m_syncInfoList;
  }
}

Log::~Log()
{
  syncWrite(); // 调用异步写入
  if (m_localTime != nullptr)
	 delete m_localTime;
  if (m_isOpen) {
	 m_logFile.flush();
	 m_logFile.close();
	 m_totLogFile.flush();
	 m_totLogFile.close();
	 m_isOpen = false;
  }
}