# stack@0.0.4

- Сделать класс `stack` более безопасным относительно исключений (обеспечивающим строгую гарантию), заменив метод `pop` на два соответствующих `pop` и `top`.
```
template <typename T>
class stack
{
public:
  stack(); /*noexcept || strong*/
  size_t count() const /*noexcept || strong*/;
  void push(T const &) /*noexcept || strong*/;
  void pop() /*noexcept || strong*/;
  T top() /*noexcept || strong*/
private:
  swap( stack & ) /*noexcept || strong*/
  T * array_;
  size_t array_size_;
  size_t count_;
};
```
