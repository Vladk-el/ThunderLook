#ifndef ROOM_H
#define ROOM_H

#include <QString>

class Room
{
public:
    Room();
    ~Room();
    Room(int id, QString name);
    Room(const Room & _room);

    int id(){ return _id; }
    QString name(){ return _name; }

private:
    int _id;
    QString _name;
};

#endif // ROOM_H
