#ifndef USER_HPP
#define USER_HPP

class User {
    private:
        static int userId;
    public:
        User(){
            userId ++;
        }
};

#endif