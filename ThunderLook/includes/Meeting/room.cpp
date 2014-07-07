#include "room.h"

Room::Room()
{
}

Room::~Room()
{

}

Room::Room(int id, QString name)
{
    this->_id = id;
    this->_name = name;
}

Room::Room(const Room &_room)
{
    this->_id = _room._id;
    this->_name = _room._name;
}
