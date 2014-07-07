#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    ~User();
    User(int _id, QString addr);
    User(const User & _user);

    int id(){ return _id; }
    QString address(){ return _address; }

private:
    int _id;
    QString _address;
};

#endif // USER_H
