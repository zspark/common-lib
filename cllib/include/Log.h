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
  }; // ��־�첽��־
  Log(const int Level,const char * logValue,...); // ���
  bool writeLogFile(std::string & logInfo); // д��־
  virtual ~Log();

  static void setSYNC(SYNCSET); // ����SYNC
  static void cleanSYNC(); // �첽������
public:
  static SYNCSET m_logSyncSet; // ��־�첽����
private:
  bool readyEnviron(const int level); // ��־����׼��
  void openLogFile(const int level,const char * file); // ����־�ļ�
  bool getTime(); // ��ȡ��־ʱ��
  void error(); // ��־ϵͳ������
  bool addSyncNode(std::string &); // ����첽�ڵ�
  bool syncWrite(); // �첽д����
  std::string getPath(); // ��ȡ�ҵ��ĵ�Ŀ¼
private:
  static int m_syncInfoNumber; // �첽��Ϣ��
  //��־�ļ�Ŀ¼
  const char * errorPosition="log/ERROR.log";  // ������־�ļ�
  const char * waringPosition="log/WARING.log";  // ������־�ļ�
  const char * informationPosition="log/INFORMATION.log";  // ��ʾ��־�ļ�
  const char * totPosition="log/";  // ������־�ļ�

  const char * totFileName="RENDERMAX.log"; // ������־��

  static std::fstream m_logFile; // ��־�ļ���
  static std::fstream m_totLogFile; // ������־�ļ��� 
  static bool m_openSuccess; // ��־�ļ����Ƿ�ɹ�
  static bool m_isOpen; // ��־�ļ��Ƿ��Ѿ���
  static bool m_totWrite; // �����Ƿ�д��������־
  int m_level; // ��־����
  struct tm * m_localTime; // ��־ʱ��

  struct SYNCLIST{
    std::string _logInfo;
    SYNCLIST * next;
    SYNCLIST(): next(nullptr){};
    SYNCLIST(std::string & logInfo): _logInfo(logInfo),next(nullptr){};
  };
  static SYNCLIST * m_syncInfoList; // ��־����
  static std::mutex MUTEX;
  static bool m_b_FirstTime;
  static std::string m_s_LogFilePrev;
};

//�����첽
#define _LOGSYNCON Log::setSYNC(Log::SYNCSET::LL_SYNC);
//�ر��첽
#define _LOGSYNCUN Log::setSYNC(Log::SYNCSET::LL_UNSYNC);
//�����첽����
#define _LOGSYNCLEAN Log::cleanSYNC();
//�첽LOG��
#define _LOGWITHSYNC(str, ...) { _LOGSYNCON Log(Log::LL_INFORMATION, str, ##__VA_ARGS__); _LOGSYNCUN }

#endif