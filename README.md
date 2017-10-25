# stack@0.0.4

[![Build Status](https://travis-ci.org/yanaxgrishkova/stack04.svg?branch=master)](https://travis-ci.org/yanaxgrishkova/stack04)

- Сделать класс `stack` более безопасным относительно исключений (обеспечивающим строгую гарантию), заменив метод `pop` на два соответствующих `pop` и `top`.
```
template <typename T>
class stack
{
private:
  T * array_;
  size_t array_size_;
  size_t count_;
public:
  - [x] stack(); /* noexcept */
  - [x] size_t count() const /* noexcept */;
  - [x] void push(T const &) /* strong */;
  - [x] void pop() /* strong */;
  - [x] T top() /* strong */
private:
  - [x] swap( stack & ) /* noexcept */
};
```
