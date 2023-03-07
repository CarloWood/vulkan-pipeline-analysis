#pragma once

#include <type_traits>
#include <cstdint>
#include <array>
#include <vector>

template<typename T>
static constexpr bool is_container_v = false;

template<typename T, std::size_t S>
static constexpr bool is_container_v<std::array<T, S>> = true;

template<typename T>
static constexpr bool is_container_v<std::vector<T>> = true;

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
    DoutEntering(dc::notice, m_name << "::reset()");
    reset_<0>();
  }

  bool next()
  {
    DoutEntering(dc::notice, m_name << "::next()");
    return next_<sizeof...(Args) - 1>();
  }

 private:
  template<std::size_t I>
  void reset_()
  {
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
    bool success = true;
    if constexpr (sizeof...(Args) == 0)
      return false;
    else
    {
      if constexpr (is_container_v<std::decay_t<decltype(std::get<I>(members_))>>)
      {
        auto& container = std::get<I>(members_);
        auto it = container.begin();
        auto end = container.end();
        while (it != end && !it->next())
        {
          it->reset();
          ++it;
        }
        success = it != end;
      }
      else if (!std::get<I>(members_).next())
      {
        std::get<I>(members_).reset();
        success = false;
      }
    }
    if (success)
      return true;
    if constexpr (I > 0)
      return next_<I - 1>();
    else
      return false;
  }

  char const* m_name;
  Tuple members_;
};
