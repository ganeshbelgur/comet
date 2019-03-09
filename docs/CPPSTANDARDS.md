# C++ Coding Standards

Style guidelines are not overly strict. The important thing is that code is clear and readable with an appropriate amount of whitespace and reasonable length lines. A few best practices are also mentioned.

## Descriptive and Consistent Naming

C++ allows for arbitrary length identifier names, so there's no reason to be terse when naming variables. Use descriptive names, and be consistent in the style `CamelCase`.

### Common C++ Naming Conventions

 * Types start with capitals: `MyClass`
 * functions and variables start with lower case: `myMethod`
 * constants are all capital: `const int PI=3.14159265358979323;`

*Note that the C++ standard does not follow any of these guidelines. Everything in the standard is lowercase only.*

### Distinguish Private Object Data

Name static global data with a `s_` prefix to distinguish it from private data.
Name private data with a `m_` prefix to distinguish it from public data.

### Well formed example

```cpp
class MyClass
{
public:
    MyClass(int data)
        : m_data(data)
    {
    }

    int getData() const
    {
        return m_data;
    }

private:
    int m_data;
};
```

## Distinguish C++ Files From C Files

C++ source file should be named `.cpp` or `.cc` NOT `.c`
C++ header files should be named `.hpp` NOT `.h`

## Use `nullptr`

C++11 introduces `nullptr` which is a special type denoting a null pointer value. This should be used instead of 0 or NULL to indicate a null pointer.

## Comments

Comment blocks should use `//`, not `/* */`. Using `//` makes it much easier to comment out a block of code while debugging.

```cpp
// this function does something
int myFunc()
{
}
```

To comment out this function block during debugging we might do:

```cpp
/*
// this function does something
int myFunc()
{
}
*/
```

which would be impossible if the function comment header used `/* */`

## Never Use `using` In a Header File

This causes the name space you are `using` to be pulled into the namespace of the header file.

## Include Guards

Header files must contain an distinctly named include guard to avoid problems with including the same header multiple times or conflicting with other headers from other projects

```cpp
#ifndef MYPROJECT_MYCLASS_HPP
#define MYPROEJCT_MYCLASS_HPP

namespace Myproject
{
  class MyClass
  {
  };
}

#endif
```

## 4 spaces indent level.

Tabs are not allowed, and a mixture of tabs and spaces is strictly forbidden. Modern autoindenting IDEs and editors require a consistent standard to be set.

```cpp
// Good Idea
int myFunction(bool b)
{
  if (b)
  {
    // do something
  }
}
```

## {} are required for blocks.
Leaving them off can lead to semantic errors in the code.

```cpp
// Bad Idea
// this compiles and does what you want, but can lead to confusing
// errors if close attention is not paid.
for (int i = 0; i < 15; ++i)
  std::cout << i << std::endl;

// Bad Idea
// the cout is not part of the loop in this case even though it appears to be
int sum = 0;
for (int i = 0; i < 15; ++i)
  ++sum;
  std::cout << i << std::endl;


// Good Idea
// It's clear which statements are part of the loop (or if block, or whatever)
int sum = 0;
for (int i = 0; i < 15; ++i)
{
  ++sum;
  std::cout << i << std::endl;
}
```

## Allman style braces

```cpp
// Bad Idea
// It isn't clear where the braces start
for (int i = 0; i < 15; ++i) {
  ++sum;
  std::cout << i << std::endl;
}

// Good Idea
// This style puts the brace associated with a control statement on the next line,
// indented to the same level as the control statement.
// Statements within the braces are indented to the next level.
for (int i = 0; i < 15; ++i)
{
  ++sum;
  std::cout << i << std::endl;
}
```

## Keep lines a reasonable length

```cpp
// Bad Idea
// hard to follow
if (x && y && myFunctionThatReturnsBool() && caseNumber3 && (15 > 12 || 2 < 3))
{
}

// Good Idea
// Logical grouping, easier to read
if (x && y && myFunctionThatReturnsBool()
    && caseNumber3
    && (15 > 12 || 2 < 3))
{
}
```


## Use "" For Including Local Files
... `<>` is [reserved for system includes](http://blog2.emptycrate.com/content/when-use-include-verses-include).

```cpp
// Bad Idea. Requires extra -I directives to the compiler
// and goes against standards
#include <string>
#include <includes/MyHeader.hpp>

// Worse Idea
// requires potentially even more specific -I directives and
// makes code more difficult to package and distribute
#include <string>
#include <MyHeader.hpp>


// Good Idea
// requires no extra params and notifies the user that the file
// is a local file
#include <string>
#include "MyHeader.hpp"
```

## Initialize Member Variables
...with the member initializer list

```cpp
// Bad Idea
class MyClass
{
public:
  MyClass(int value)
  {
    m_value = value;
  }

private:
  int m_value;
};


// Good Idea
// C++'s memeber initializer list is unique to the language and leads to
// cleaner code and potential performance gains that other languages cannot
// match
class MyClass
{
public:
  MyClass(int value)
    : m_value(value)
  {
  }

private:
  int m_value;
};
```

## Forward Declare when Possible

This:
```cpp
// some header file
class MyClass;

void doSomething(const MyClass &);
```

instead of:

```cpp
// some header file
#include "MyClass.hpp"

void doSomething(const MyClass &);
```

This is a proactive approach to simplify compilation time and rebuilding dependencies.

## Always Use Namespaces

There is almost never a reason to declare an identifier in the global namespaces. Instead, functions and classes should exist in an appropriately named namespaces or in a class inside of a namespace. Identifiers which are placed in the global namespace risk conflicting with identifiers from other (mostly C, which doesn't have namespaces) libraries. Namespaces should begin with a capital letter and rest of the letters should be small.

## Avoid Compiler Macros

Compiler definitions and macros are replaced by the pre-processor before the compiler is ever run. This can make debugging very difficult because the debugger doesn't know where the source came from.

```cpp
// Good Idea
namespace Myproject
{
  class Constants
  {
    public:
      static const double PI = 3.14159;
  }
}

// Bad Idea
#define PI 3.14159;
```

## Limit Variable Scope

Variables should be declared as late as possible, and ideally, only when it's possible to initialize the object. Reduced variable scope results in less memory being used, more efficient code in general, and helps the compiler optimize the code further.

```cpp
// Good idea
for (int i = 0; i < 15; ++i)
{
  MyObject obj(i);
  // do something with obj
}

// Bad Idea
MyObject obj; // meaningless object initialization
for (int i = 0; i < 15; ++i)
{
  obj = MyObject(i); // unnecessary assignment operation
  // do something with obj
}
// obj is still taking up memory for no reason
```

## Use Exceptions Instead of Return Values to Indicate Error

Exceptions cannot be ignored. Return values, such as using `boost::optional`, can be ignored and if not checked can cause crashes or memory errors. An exception, on the other hand, can be caught and handled. Potentially all the way up the highest level of the application with a log and automatic restart of the application.

Stroustrup, the original designer of C++, [makes this point](http://www.stroustrup.com/bs_faq2.html#exceptions-why) much better.

## Avoid raw memory access

Raw memory access, allocation and deallocation, are difficult to get correct in C++ without [risking memory errors and leaks](http://blog2.emptycrate.com/content/nobody-understands-c-part-6-are-you-still-using-pointers). C++11 provides tools to avoid these problems.

```cpp
// Bad Idea
MyClass *myobj = new MyClass;

// ...
delete myobj;


// Good Idea
std::shared_ptr<MyClass> myobj = make_shared<MyClass>();
// ...
// myobj is automatically freed for you whenever it is no longer used.
```

## Avoid global data
... this includes singleton objects

Global data leads to unintended sideeffects between functions and can make code difficult or impossible to parallelize. Even if the code is not intended today for parallelization, there is no reason to make it impossible for the future.


## Prefer pre-increment to post-increment
... when it is semantically correct. Pre-increment is [faster](http://blog2.emptycrate.com/content/why-i-faster-i-c) then post-increment because it does not require a copy of the object to be made.

```cpp
// Bad Idea
for (int i = 0; i < 15; i++)
{
  std::cout << i << std::endl;
}


// Good Idea
for (int i = 0; i < 15; ++i)
{
  std::cout << i << std::endl;
}

```

## Const as much as possible
`const` tells the compiler that a variable or method is immutable. This helps the compiler optimize the code and helps the developer know if a function side effects. Also, using `const &` prevents the compiler from copying data unnecessarily. [Here](http://kotaku.com/454293019) are some comments on const from John Carmack.

```cpp
// Bad Idea
class MyClass
{
public:
  MyClass(std::string value)
    : m_value(value)
  {
  }

  std::string get_value()
  {
    return m_value;
  }

private:
  std::string m_value;
}


// Good Idea
class MyClass
{
public:
  MyClass(const std::string &value)
    : m_value(value)
  {
  }

  std::string get_value() const
  {
    return m_value;
  }

private:
  std::string m_value;
}
```

## Prefer Stack Operations to Heap Operations

Heap operations have performance penalties in mulithreaded environments on most platforms and can possibly lead to memory errors if not used carefully.

Modern C++11 has special move operations which are designed to enhances the performance of stack based data by reducing or eliminating copies, which can bring even the single threaded case on par with heap based operations.
