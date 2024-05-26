#ifndef __IUI_ENTRY_HPP__
#define __IUI_ENTRY_HPP__

class IUiEntry {
  public:
    virtual ~IUiEntry() = default;

    virtual int handleInput() = 0;
    virtual void display() const = 0;
};

#endif // __IUI_ENTRY_HPP__
