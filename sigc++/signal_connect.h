/*
 * Copyright 2024, The libsigc++ Development Team
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#ifndef SIGC_SIGNAL_CONNECT_H
#define SIGC_SIGNAL_CONNECT_H

#include <sigc++/signal.h>
#include <sigc++/bind.h>
#include <sigc++/functors/ptr_fun.h>
#include <sigc++/functors/mem_fun.h>

namespace sigc
{

/** Connect a callable objet to a signal.
 * @param signal The signal to connect to.
 * @param fun The callable object that should be wrapped.
 * @return A connection.
 *
 * @ingroup signal
 */
template<typename T_return, typename... T_arg, typename T_fun = T_return(T_arg...)>
inline connection
signal_connect(signal<T_return, T_arg...>& signal, T_fun&& fun)
{
  return signal.connect(fun);
}

/** Connect a function to a signal
 * @param signal The signal to connect to.
 * @param fun The function that should be wrapped.
 * @return A connection.
 *
 * @newin{3,8}
 * @ingroup signal
 */
template<typename T_return, typename... T_arg>
inline connection
signal_connect(signal<T_return(T_arg...)>& signal, T_return (*fun)(T_arg...))
{
  return signal.connect(ptr_fun<T_return, T_arg...>(fun));
}

/** Connect a non-const method to a signal
 * @param signal The signal to connect to.
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @return A connection.
 *
 * @newin{3,8}
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_arg>
inline connection
signal_connect(signal<T_return(T_arg...)>& signal, T_obj& obj, T_return (T_obj::*fun)(T_arg...))
{
  return signal.connect(mem_fun<T_return, T_obj, T_obj, T_arg...>(obj, fun));
}

/** Connect a const method to a signal
 * @param signal The signal to connect to.
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @return A connection.
 *
 * @newin{3,8}
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_arg>
inline connection
signal_connect(signal<T_return(T_arg...)>& signal, const T_obj& obj, T_return (T_obj::*fun)(T_arg...) const)
{
  return signal.connect(mem_fun<T_return, const T_obj, const T_obj, T_arg...>(obj, fun));
}

/** Connect a non-const volatile method to a signal
 * @param signal The signal to connect to.
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @return A connection.
 *
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_arg>
inline connection
signal_connect(signal<T_return(T_arg...)>& signal, T_obj& obj, T_return (T_obj::*fun)(T_arg...) volatile)
{
  return signal.connect(sigc::mem_fun<T_return, T_obj, T_obj, T_arg...>(obj, fun));
}

/** Connect a const volatile method to a signal
 * @param signal The signal to connect to.
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @return A connection.
 *
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_arg>
inline connection
signal_connect(signal<T_return(T_arg...)>& signal, const T_obj& obj, T_return (T_obj::*fun)(T_arg...) const volatile)
{
  return signal.connect(sigc::mem_fun<T_return, const T_obj, const T_obj, T_arg...>(obj, fun));
}

/** Connect a function with bound arguments to a signal
 * @param signal the signal to connect to.
 * @param fun the function that should be wrapped.
 * @param bound Arguments to bind to @e fun.
 * @return A connection.
 *
 * @note first bound argument is explicit to avoid ambiguous call when compiling with Clang (but not GCC)
 *
 * @ingroup signal
 */
template<typename T_return, typename... T_unbound, typename T_bound0, typename... T_boundn>
inline connection
signal_connect(signal<T_return(T_unbound...)>& signal, T_return (*fun)(T_unbound..., T_bound0, T_boundn...), T_bound0&& bound0, T_boundn&&... boundn)
{
  return signal.connect(bind(ptr_fun<T_return, T_unbound..., T_bound0, T_boundn...>(fun), std::forward<T_bound0>(bound0), std::forward<T_boundn>(boundn)...));
}

/** Connect non-const method with bound arguments to a signal
 * @param signal The signal to connect to
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @param bound Arguments to bind to @e fun.
 * @return A connection.
 *
 * @note first bound argument is explicit to avoid ambiguous call when compiling with Clang (but not GCC)
 *
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_unbound, typename T_bound0, typename... T_boundn>
inline connection
signal_connect(signal<T_return(T_unbound...)>& signal, T_obj& obj, T_return (T_obj::*fun)(T_unbound..., T_bound0, T_boundn...), T_bound0&& bound0, T_boundn&&... boundn)
{
  return signal.connect(bind(mem_fun<T_return, T_obj, T_obj, T_unbound..., T_bound0, T_boundn...>(obj, fun), std::forward<T_bound0>(bound0), std::forward<T_boundn>(boundn)...));
}

/** Connect a const method with bound arguments to a signal
 * @param signal The signal to connect to
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @param bound Arguments to bind to @e fun.
 * @return A connection.
 *
 * @note first bound argument is explicit to avoid ambiguous call when compiling with Clang (but not GCC)
 *
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_unbound, typename T_bound0, typename... T_boundn>
inline connection
signal_connect(signal<T_return(T_unbound...)>& signal, const T_obj& obj, T_return (T_obj::*fun)(T_unbound..., T_bound0, T_boundn...) const, T_bound0&& bound0, T_boundn&&... boundn)
{
  return signal.connect(bind(mem_fun<T_return, const T_obj, const T_obj, T_unbound..., T_bound0, T_boundn...>(obj, fun), std::forward<T_bound0>(bound0), std::forward<T_boundn>(boundn)...));
}

/** Connect a non-const volatile method with bound arguments to a signal
 * @param signal The signal to connect to
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @param bound Arguments to bind to @e fun.
 * @return A connection.
 *
 * @note first bound argument is explicit to avoid ambiguous call when compiling with Clang (but not GCC)
 *
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_unbound, typename T_bound0, typename... T_boundn>
inline connection
signal_connect(signal<T_return(T_unbound...)>& signal, T_obj& obj, T_return (T_obj::*fun)(T_unbound..., T_bound0, T_boundn...) volatile, T_bound0&& bound0, T_boundn&&... boundn)
{
  return signal.connect(bind(mem_fun<T_return, T_obj, T_obj, T_unbound..., T_bound0, T_boundn...>(obj, fun), std::forward<T_bound0>(bound0), std::forward<T_boundn>(boundn)...));
}

/** Connect const volatile method with bound arguments to a signal
 * @param signal The signal to connect to
 * @param obj Reference to object instance the functor should operate on.
 * @param fun Pointer to method that should be wrapped.
 * @param bound Arguments to bind to @e fun.
 * @return A connection.
 *
 * @note first bound argument is explicit to avoid ambiguous call when compiling with Clang (but not GCC)
 *
 * @ingroup signal
 */
template<typename T_return, typename T_obj, typename... T_unbound, typename T_bound0, typename... T_boundn>
inline connection
signal_connect(signal<T_return(T_unbound...)>& signal, const T_obj& obj, T_return (T_obj::*fun)(T_unbound..., T_bound0, T_boundn...) const volatile, T_bound0&& bound0, T_boundn&&... boundn)
{
  return signal.connect(bind(mem_fun<T_return, const T_obj, const T_obj, T_unbound..., T_bound0, T_boundn...>(obj, fun), std::forward<T_bound0>(bound0), std::forward<T_boundn>(boundn)...));
}

} /* namespace sigc */

#endif /* SIGC_SIGNAL_CONNECT_H */
