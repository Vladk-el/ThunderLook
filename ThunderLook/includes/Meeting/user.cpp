#include "user.h"

User::User()
{
}

User::~User()
{

}

User::User(const User & _user)
{
    this->_id = _user._id;
    this->_address = _user._address;
}

User::User(int _id, QString addr)
{
    this->_id = _id;
    this->_address = addr;
}
