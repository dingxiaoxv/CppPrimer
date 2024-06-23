#include "message.h"
#include <iostream>
#include <utility>

Message::Message(const Message &m)
    : contents_(m.contents_), folders_(m.folders_) {
  addToFolders(m);
}

Message::Message(Message &&m) : contents_(std::move(m.contents_)) {
  moveFolders(&m);
}

Message::~Message() { removeFromFolders(); }

Message &Message::operator=(const Message &rhs) {
  removeFromFolders();
  contents_ = rhs.contents_;
  folders_ = rhs.folders_;
  addToFolders(rhs);
  return *this;
}

void Message::saveTo(Folder &f) {
  folders_.insert(&f);
  f.addMsg(this);
}

void Message::removeFrom(Folder &f) {
  folders_.erase(&f);
  f.remMsg(this);
}

void Message::addFldr(Folder *f) { folders_.insert(f); }

void Message::remFldr(Folder *f) { folders_.erase(f); }

void Message::addToFolders(const Message &m) {
  for (auto f : m.folders_) {
    f->addMsg(this);
  }
}

void Message::removeFromFolders() {
  for (auto f : folders_) {
    f->remMsg(this);
  }
}

void Message::moveFolders(Message *m) {
  folders_ = std::move(m->folders_);
  for (auto f : folders_) {
    f->remMsg(m);
    f->addMsg(this);
  }
  m->folders_.clear();
}

Folder::Folder(const Folder &f) : name_(f.name_), msgs_(f.msgs_) {
  addToMessages(f);
}

Folder::~Folder() { removeFromMessages(); }

Folder &Folder::operator=(const Folder &rhs) {
  removeFromMessages();
  name_ = rhs.name_;
  msgs_ = rhs.msgs_;
  addToMessages(rhs);
  return *this;
}

void Folder::addMsg(Message *m) {
  auto ret = msgs_.insert(m);
  // if (ret.second) {
  //   std::cout << "insert successfully" << std::endl;
  // } else {
  //   std::cout << "insert failed!" << std::endl;
  // }
}

void Folder::remMsg(Message *m) {
  size_t ret = msgs_.erase(m);
  // if (ret > 0) {
  //   std::cout << "erase successfully" << std::endl;
  // } else {
  //   std::cout << "erase failed!" << std::endl;
  // }
}

void Folder::addToMessages(const Folder &f) {
  for (auto msg : f.msgs_) {
    msg->addFldr(this);
  }
}

void Folder::removeFromMessages() {
  for (auto msg : msgs_) {
    msg->remFldr(this);
  }
}