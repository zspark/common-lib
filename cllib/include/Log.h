#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <mutex>

class Log{
public:
  enum{
    LL_ERROR=0,
    LL_WARNING=1,
    LL_INFORMATION=2
  };
  enum SYNCSET{
    LL_SYNC=0,
    LL_UNSYNC=1
  }; // 日志异步标志
  Log(const int Level,const char * logValue,...); // 入口
  bool writeLogFile(std::string & logInfo); // 写日志
  virtual ~Log();

  static void setSYNC(SYNCSET); // 设置SYNC
  static void cleanSYNC(); // 异步流清理
public:
  static SYNCSET m_logSyncSet; // 日志异步设置
private:
  bool readyEnviron(const int level); // 日志环境准备
  void openLogFile(const int level,const char * file); // 打开日志文件
  bool getTime(); // 获取日志时间
  void error(); // 日志系统错误处理
  bool addSyncNode(std::string &); // 添加异步节点
  bool syncWrite(); // 异步写处理
  std::string getPath(); // 获取我的文档目录
private:
  static int m_syncInfoNumber; // 异步消息数
  //日志文件目录
  const char * errorPosition="log/ERROR.log";  // 错误日志文件
  const char * waringPosition="log/WARING.log";  // 警告日志文件
  const char * informationPosition="log/INFORMATION.log";  // 提示日志文件
  const char * totPosition="log/";  // 总体日志文件

  const char * totFileName="RENDERMAX.log"; // 总体日志名

  static std::fstream m_logFile; // 日志文件流
  static std::fstream m_totLogFile; // 总体日志文件流 
  static bool m_openSuccess; // 日志文件打开是否成功
  static bool m_isOpen; // 日志文件是否已经打开
  static bool m_totWrite; // 控制是否写入总体日志
  int m_level; // 日志级别
  struct tm * m_localTime; // 日志时间

  struct SYNCLIST{
    std::string _logInfo;
    SYNCLIST * next;
    SYNCLIST(): next(nullptr){};
    SYNCLIST(std::string & logInfo): _logInfo(logInfo),next(nullptr){};
  };
  static SYNCLIST * m_syncInfoList; // 日志队列
  static std::mutex MUTEX;
  static bool m_b_FirstTime;
  static std::string m_s_LogFilePrev;
};

//开启异步
#define _LOGSYNCON Log::setSYNC(Log::SYNCSET::LL_SYNC);
//关闭异步
#define _LOGSYNCUN Log::setSYNC(Log::SYNCSET::LL_UNSYNC);
//清理异步队列
#define _LOGSYNCLEAN Log::cleanSYNC();
//异步LOG宏
#define _LOGWITHSYNC(str, ...) { _LOGSYNCON Log(Log::LL_INFORMATION, str, ##__VA_ARGS__); _LOGSYNCUN }

#endif