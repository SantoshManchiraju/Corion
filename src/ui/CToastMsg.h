#ifndef CTOASTMSG_H
#define CTOASTMSG_H

#include <QLabel>
#include <QTime>
#include <thread>
#include <mutex>

class CToastMsg : public QLabel
{
private:
    int m_timeout;
    QTime m_closeTime;

    std::thread m_thread;
    std::mutex m_mutex;

public:
    CToastMsg(QWidget *parent, int timeout = 3);

    void run();
    void showMsg(std::string msg);
    void wait_and_close();
};

#endif // CTOASTMSG_H
