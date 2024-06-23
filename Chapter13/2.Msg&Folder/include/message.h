#ifndef MESSAGE_H
#define MESSAGE_H

#include <set>
#include <string>

class Folder;

class Message {
  friend class Folder;

public:
  Message(const std::string &s = "") : contents_(s) {}
  Message(const Message &);
  Message(Message &&);
  Message &operator=(const Message &);
  ~Message();
  void saveTo(Folder &);
  void removeFrom(Folder &);
  void addFldr(Folder *);
  void remFldr(Folder *);

private:
  void addToFolders(const Message &);
  void removeFromFolders();
  void moveFolders(Message *);

private:
  std::string contents_;
  std::set<Folder *> folders_;
};

class Folder {
  friend class Message;

public:
  Folder(const std::string &s = "") : name_(s) {}
  Folder(const Folder &);
  Folder &operator=(const Folder &);
  ~Folder();
  void addMsg(Message *);
  void remMsg(Message *);

private:
  void addToMessages(const Folder &);
  void removeFromMessages();

private:
  std::string name_;
  std::set<Message *> msgs_;
};

#endif