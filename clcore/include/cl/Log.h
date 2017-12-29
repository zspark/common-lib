#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <mutex>
#include "clTypes.h"

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
  Log(const clInt Level,const clChar * logValue,...); // ���
  clBool writeLogFile(clString & logInfo); // д��־
  virtual ~Log();

  static clVoid setSYNC(SYNCSET); // ����SYNC
  static clVoid cleanSYNC(); // �첽������
public:
  static SYNCSET m_logSyncSet; // ��־�첽����
private:
  clBool readyEnviron(const int level); // ��־����׼��
  clVoid openLogFile(const int level,const clChar * file); // ����־�ļ�
  clBool getTime(); // ��ȡ��־ʱ��
  clVoid error(); // ��־ϵͳ������
  clBool addSyncNode(clString &); // ����첽�ڵ�
  clBool syncWrite(); // �첽д����
  clString getPath(); // ��ȡ�ҵ��ĵ�Ŀ¼
private:
  static int m_syncInfoNumber; // �첽��Ϣ��
  //��־�ļ�Ŀ¼
  const clChar * errorPosition="log/ERROR.log";  // ������־�ļ�
  const clChar * waringPosition="log/WARING.log";  // ������־�ļ�
  const clChar * informationPosition="log/INFORMATION.log";  // ��ʾ��־�ļ�
  const clChar * totPosition="log/";  // ������־�ļ�

  const clChar * totFileName="RENDERMAX.log"; // ������־��

  static fstream m_logFile; // ��־�ļ���
  static fstream m_totLogFile; // ������־�ļ��� 
  static clBool m_openSuccess; // ��־�ļ����Ƿ�ɹ�
  static clBool m_isOpen; // ��־�ļ��Ƿ��Ѿ���
  static clBool m_totWrite; // �����Ƿ�д��������־
  int m_level; // ��־����
  struct tm * m_localTime; // ��־ʱ��

  struct SYNCLIST{
    clString _logInfo;
    SYNCLIST * next;
    SYNCLIST(): next(nullptr){};
    SYNCLIST(clString & logInfo): _logInfo(logInfo),next(nullptr){};
  };
  static SYNCLIST * m_syncInfoList; // ��־����
  static mutex MUTEX;
  static clBool m_b_FirstTime;
  static clString m_s_LogFilePrev;
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