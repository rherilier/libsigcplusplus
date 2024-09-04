/* Copyright 2024, The libsigc++ Development Team
 *  Assigned to public domain.  Use as you wish without restriction.
 */

#include "testutilities.h"
#include <sigc++/trackable.h>
#include <sigc++/signal_connect.h>

namespace
{

TestUtilities* util = nullptr;
std::ostringstream result_stream;

void
fun(int i)
{
  result_stream << "fun(int " << i << ")";
}

[[maybe_unused]]
void
fun(double d)
{
  result_stream << "fun(double " << d << ")";
}

struct foo : public sigc::trackable
{
  void fun_nonconst(int i)
  {
    result_stream << "foo::fun_nonconst(int " << i << ")";
  }

  void fun_nonconst(double d)
  {
    result_stream << "foo::fun_nonconst(double " << d << ")";
  }

  void fun_const(int i) const
  {
    result_stream << "foo::fun_const(int " << i << ")";
  }

  void fun_const(double d) const
  {
    result_stream << "foo::fun_const(double " << d << ")";
  }

  void fun_volatile(int i) volatile
  {
    result_stream << "foo::fun_volatile(int " << i << ")";
  }

  void fun_volatile(double d) volatile
  {
    result_stream << "foo::fun_volatile(double " << d << ")";
  }

  void fun_const_volatile(int i) const volatile
  {
    result_stream << "foo::fun_const_volatile(int " << i << ")";
  }

  void fun_const_volatile(double d) const volatile
  {
    result_stream << "foo::fun_const_volatile(double " << d << ")";
  }
};

void
test_signal_connect_lambda()
{
  sigc::signal<void(int)> signal;

  sigc::signal_connect(signal, [](int i) -> void {
    result_stream << "lambda(int " << i << ")";
  });

  signal.emit(42);
  util->check_result(result_stream, "lambda(int 42)");
}

void
test_signal_connect_std_function()
{
  sigc::signal<void(int)> signal;
  std::function<void(int)> fun = [](int i) -> void {
    result_stream << "std::function(int " << i << ")";
  };

  sigc::signal_connect(signal, fun);

  signal.emit(42);
  util->check_result(result_stream, "std::function(int 42)");
}

void
test_signal_connect_fun()
{
  sigc::signal<void(int)> signal;

  sigc::signal_connect(signal, &fun);

  signal.emit(42);
  util->check_result(result_stream, "fun(int 42)");
}

void
test_signal_connect_method_nonconst()
{
  sigc::signal<void(int)> signal;
  foo f;

  sigc::signal_connect(signal, f, &foo::fun_nonconst);

  signal.emit(42);
  util->check_result(result_stream, "foo::fun_nonconst(int 42)");
}

void
test_signal_connect_method_const()
{
  sigc::signal<void(int)> signal;
  foo f;

  sigc::signal_connect(signal, f, &foo::fun_const);

  signal.emit(42);
  util->check_result(result_stream, "foo::fun_const(int 42)");
}

void
test_signal_connect_method_const_with_const_object()
{
  sigc::signal<void(int)> signal;
  const foo f;

  sigc::signal_connect(signal, f, &foo::fun_const);

  signal.emit(42);
  util->check_result(result_stream, "foo::fun_const(int 42)");
}

void
test_signal_connect_method_volatile()
{
  sigc::signal<void(int)> signal;
  foo f;

  sigc::signal_connect(signal, f, &foo::fun_volatile);

  signal.emit(42);
  util->check_result(result_stream, "foo::fun_volatile(int 42)");
}

void
test_signal_connect_method_const_volatile()
{
  sigc::signal<void(int)> signal;
  foo f;

  sigc::signal_connect(signal, f, &foo::fun_const_volatile);

  signal.emit(42);
  util->check_result(result_stream, "foo::fun_const_volatile(int 42)");
}

void
test_signal_connect_method_const_volatile_with_const_object()
{
  sigc::signal<void(int)> signal;
  const foo f;

  sigc::signal_connect(signal, f, &foo::fun_const_volatile);

  signal.emit(42);
  util->check_result(result_stream, "foo::fun_const_volatile(int 42)");
}

void
test_signal_connect_method()
{
  test_signal_connect_method_nonconst();
  test_signal_connect_method_const();
  test_signal_connect_method_const_with_const_object();
  test_signal_connect_method_volatile();
  test_signal_connect_method_const_volatile();
  test_signal_connect_method_const_volatile_with_const_object();
}

} // end anonymous namespace

int
main(int argc, char* argv[])
{
  util = TestUtilities::get_instance();

  if (!util->check_command_args(argc, argv))
    return util->get_result_and_delete_instance() ? EXIT_SUCCESS : EXIT_FAILURE;

  test_signal_connect_lambda();

  test_signal_connect_std_function();

  test_signal_connect_fun();

  test_signal_connect_method();

  return util->get_result_and_delete_instance() ? EXIT_SUCCESS : EXIT_FAILURE;
}
