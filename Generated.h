#pragma once

#include "utils/RandomNumber.h"
#include <type_traits>
#include <cstdint>
#include <array>
#include <vector>
#include <tuple>

template<typename T>
static constexpr bool is_container_v = false;

template<typename T, std::size_t S>
static constexpr bool is_container_v<std::array<T, S>> = true;

template<typename T>
static constexpr bool is_container_v<std::vector<T>> = true;

template<typename T>
static constexpr bool is_container_v<std::deque<T>> = true;

template<typename Tuple>
class Generated;

template<typename... Args>
class Generated<std::tuple<Args&...>>
{
 public:
  using Tuple = std::tuple<Args&...>;

//  Generated() = default;
  Generated(char const* name, Tuple members) : m_name(name), members_(members) { }

  void reset()
  {
    DoutEntering(dc::debug, m_name << "::reset() [" << this << "]");
    reset_<0>();
  }

  bool next()
  {
    DoutEntering(dc::debug|continued_cf, m_name << "::next() [" << this << "] = ");
    bool result = next_<sizeof...(Args) - 1>();
    Dout(dc::finish, std::boolalpha << result);
    return result;
  }

  void randomize(utils::RandomNumber& rn)
  {
    DoutEntering(dc::debug, m_name << "::randomize() [" << this << "]");
    randomize_<0>(rn);
  }

 private:
  template<std::size_t I>
  void reset_()
  {
    DoutEntering(dc::debug, m_name << "::reset_<" << I << ">() [" << this << "]");
    if constexpr (sizeof...(Args) == 0)
      return;
    else if constexpr (is_container_v<std::decay_t<decltype(std::get<I>(members_))>>)
    {
      auto& container = std::get<I>(members_);
      for (auto& element : container)
        element.reset();
    }
    else
      std::get<I>(members_).reset();
    if constexpr (I + 1 < sizeof...(Args))
      reset_<I + 1>();
  }

  template<std::size_t I>
  bool next_()
  {
    DoutEntering(dc::debug, m_name << "::next_<" << I << ">() [" << this << "]");
    bool success = true;
    if constexpr (sizeof...(Args) == 0)
      return false;
    else
    {
      if constexpr (is_container_v<std::decay_t<decltype(std::get<I>(members_))>>)
      {
        auto& container = std::get<I>(members_);
        auto it = container.rbegin();
        auto end = container.rend();
        while (it != end && !it->next())
          ++it;
        success = it != end;
        if (success)
          while (it != container.rbegin())
          {
            --it;
            it->reset();
          }
      }
      else if (!std::get<I>(members_).next())
      {
        success = false;
      }
    }
    if (success)
      return true;
    if constexpr (I > 0)
    {
      success = next_<I - 1>();
      if (success)
        std::get<I>(members_).reset();
      return success;
    }
    else
      return false;
  }

  template<std::size_t I>
  void randomize_(utils::RandomNumber& rn)
  {
    if constexpr (sizeof...(Args) == 0)
      return;
    else if constexpr (is_container_v<std::decay_t<decltype(std::get<I>(members_))>>)
    {
      auto& container = std::get<I>(members_);
      for (auto& element : container)
        element.randomize(rn);
    }
    else
      std::get<I>(members_).randomize(rn);
    if constexpr (I + 1 < sizeof...(Args))
      randomize_<I + 1>(rn);
  }

  char const* m_name;
  Tuple members_;
};
