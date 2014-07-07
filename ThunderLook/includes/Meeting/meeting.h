#ifndef MEETING_H
#define MEETING_H

class Meeting
{
public:
    Meeting(){ _id = -1; _pos = -1; _size = -1; }
    Meeting(int id, int pos, int size) : _id(id), _pos(pos), _size(size){}
    Meeting(const Meeting & meeting);
    ~Meeting(){}
    int id(){ return _id; }
    int pos(){ return _pos; }
    int size(){ return _size; }
private :
    int _id;
    int _pos;
    int _size;
};

#endif // MEETING_H
