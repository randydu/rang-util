#ifndef RANG_UTIL_H
#define RANG_UTIL_H

#include <rang.hpp>

namespace rang::util
{
    template <typename S>
    concept Streamable = requires(S s, std::ostream &os)
    {
        // clang-format off
        { os << s } -> std::same_as<decltype(os)>; // support streaming operator
        // clang-format on
    };

    template <typename S, typename T = S>
    concept ConstructorStreamable = requires(S s, T t, std::ostream &os)
    {
        // clang-format off
        { os << s(t) } -> std::same_as<decltype(os)>; // support streaming operator
        // clang-format on
    };

    template <typename T>
    concept Style = Streamable<T>; // && ConstructorStreamable<T>;

    namespace __detail
    {

        struct style_reset_t
        {
            inline friend std::ostream &operator<<(std::ostream &os, style_reset_t self)
            {
                return os << rang::style::reset;
            }
        };

        template <Style S, Style T>
        class style_composer_t
        {
            using this_type = style_composer_t;

        public:
            constexpr style_composer_t(const S &s, const T &t) : s_(s), t_(t) {}
            constexpr style_composer_t(S &&s, T &&t) : s_(std::forward<S>(s)), t_(std::forward<T>(t)) {}

            constexpr friend std::ostream &operator<<(std::ostream &os, style_composer_t self)
            {
                return os << self.s_ << self.t_;
            }

            template <Style V>
            constexpr Style auto operator()(V &&v) const
            {
                auto s = style_composer_t<this_type, V>(*this, std::forward<V>(v));
                return style_composer_t<decltype(s), rang::style>(std::move(s), rang::style::reset); // auto-reset
            }

        private:
            S s_;
            T t_;
        };

        template <Style S>
        class style_it_t
        {
        public:
            constexpr style_it_t(const S &s) : s_(s) {}
            constexpr style_it_t(S &&s) : s_(std::forward<S>(s)) {}

            template <Style T>
            constexpr Style auto operator()(T &&t) const
            {
                auto s = style_composer_t<S, T>(s_, std::forward<T>(t));
                return style_composer_t<decltype(s), rang::style>(std::move(s), rang::style::reset); // reset style
            }

            constexpr friend std::ostream &operator<<(std::ostream &os, style_it_t self)
            {
                return os << self.s_;
            }

        private:
            S s_;
        };

        // constant style
        template <Style S, std::size_t N>
        class style_repeat_t
        {
        public:
            constexpr style_repeat_t(const S &s) : s_(s) {}
            constexpr style_repeat_t(S &&s) : s_(std::forward<S>(s)) {}

            constexpr friend std::ostream &operator<<(std::ostream &os, const style_repeat_t &self)
            {
                for (std::size_t i = 0; i < N; ++i)
                {
                    os << self.s_;
                }
                return os;
            }

        private:
            S s_;
        };

        // Do nothing
        class style_dummy
        {
        public:
            style_dummy() = default;

            template <Style T>
            constexpr Style auto operator()(T &&t) const
            {
                return t;
            }
            constexpr friend std::ostream &operator<<(std::ostream &os, const style_dummy &self)
            {
                return os;
            }
        };
    } // namespace __detail

    inline constexpr auto style_dummy = __detail::style_dummy{};

    constexpr Style auto make_style(){
        return style_dummy;
    }

    template <Style S>
    constexpr Style auto make_style(S &&s)
    {
        return __detail::style_it_t<std::remove_cvref_t<S>>(std::forward<S>(s));
    }

    template <Style S1, Style S2, Style... Ts>
    constexpr Style auto make_style(S1 &&s1, S2 &&s2, Ts... ts)
    {
        Style auto s = __detail::style_composer_t<std::remove_cvref_t<S1>, std::remove_cvref_t<S2>>(std::forward<S1>(s1), std::forward<S2>(s2));
        if constexpr (sizeof...(Ts) == 0)
            return s;
        else
            return make_style(std::move(s), std::forward<Ts>(ts)...);
    }

    template <Style S, int N>
    constexpr Style auto repeat_style(S &&s)
    {
        return __detail::style_repeat_t<std::remove_cvref_t<S>, N>(std::forward<S>(s));
    }


    namespace html
    {
        // break to next line
        inline constexpr auto BR0 = style_dummy;
        inline constexpr auto BR1 = repeat_style<char, 1>('\n');
        inline constexpr auto BR2 = repeat_style<char, 2>('\n');
        inline constexpr auto BR3 = repeat_style<char, 3>('\n');
        inline constexpr auto BR4 = repeat_style<char, 4>('\n');
        inline constexpr auto BR5 = repeat_style<char, 5>('\n');
        inline constexpr auto BR6 = repeat_style<char, 6>('\n');
        inline constexpr auto BR7 = repeat_style<char, 7>('\n');
        inline constexpr auto BR8 = repeat_style<char, 8>('\n');
        inline constexpr auto BR9 = repeat_style<char, 9>('\n');

        // Default break one line
        inline constexpr auto BR = BR1;
    }
} // namespace rang::util

#endif