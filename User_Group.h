#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <set>

class Group;

class User{
public:
    User(int n_userid, std::string n_username, std::string n_addinf = "")
    : userid(n_userid), username(std::move(n_username)), addinf(std::move(n_addinf)){}

    int get_id() const{
        return userid;
    }

    std::string get_name(){
        return username;
    }

    std::string get_addinf(){
        return addinf;
    }

    void set_group(std::shared_ptr<Group> n_group){
        usergroup = std::move(n_group);
    }

    std::shared_ptr<Group> get_group(){
        return usergroup;
    }


private:
    int userid;
    std::string username;
    std::string addinf;
    std::shared_ptr<Group> usergroup;
};


class Group{
public:
    explicit Group(int n_groupid): groupid(n_groupid){}

    int get_id() const {
        return groupid;
    }

    auto get_users(){
        return groupusers;
    }

    void set_user(const std::shared_ptr<User> n_user){
        groupusers.insert(n_user);

        n_user->set_group(static_cast<std::shared_ptr<Group>>(this));
    }

    void clear_user(const std::shared_ptr<User> n_userid){
        groupusers.erase(n_userid);
    }


private:
    int groupid;
    std::set<std::weak_ptr<User>> groupusers;
};