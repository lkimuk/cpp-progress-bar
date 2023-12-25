#ifndef CPP_PROGRESS_BAR_H_
#define CPP_PROGRESS_BAR_H_

#include <concepts>
#include <format>
#include <functional>
#include <iostream>

#include "aspect.hpp"


namespace cpb {

struct fill {
    char value;
    int width;
};

} // namespace cpb


template <>
struct std::formatter<cpb::fill> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  auto format(const cpb::fill& f, auto& ctx) const {
    return std::fill_n(ctx.out(), f.width, f.value);
  }
};


namespace cpb {

class progress_bar {
public:
    progress_bar(int total, int bar_length = 50, std::ostream& os = std::cout)
        : m_bar_length{ bar_length }
        , m_data_length{ total }
        , m_done_char{ '#' }
        , m_undone_char{ '.' }
        , m_opening_bracket{ '[' }
        , m_closing_bracket{ ']' }
        , m_os{ os }
    {}

    auto bar_length(int len) -> void {
        m_bar_length = len;
    } 

    auto bar_length() const -> int {
        return m_bar_length;
    }

    auto data_length(int len) -> void {
        m_data_length = len;
    } 

    auto data_length() const -> int {
        return m_data_length;
    }

    auto done_char(char ch) -> void {
        m_done_char = ch;
    } 

    auto done_char() const -> char {
        return m_done_char;
    }

    auto undone_char(char ch) -> void {
        m_undone_char = ch;
    } 

    auto undone_char() const -> char {
        return m_undone_char;
    }

    auto opening_bracket(char ch) -> void {
        m_opening_bracket = ch;
    } 

    auto opening_bracket() const -> char {
        return m_opening_bracket;
    }

    auto closing_bracket(char ch) -> void {
        m_closing_bracket = ch;
    }

    auto closing_bracket() const -> char {
        return m_closing_bracket;
    }

    auto stream(std::ostream& os) -> void {
        m_os.rdbuf(os.rdbuf());
    }

    auto update(int cur) const -> void {
        aopcxx::make_aspect<progress_bar>(this, cur);
    }

    auto update(int cur, std::invocable<int> auto fn) const -> void {
        aopcxx::make_aspect<progress_bar>(this, fn, cur);
    }


    auto before(int = {}) const -> void {
        m_os << "\033[2K\r";
    }

    auto after(int cur) const -> void {
        auto progress = static_cast<float>(cur) / m_data_length;
        auto finished_length = static_cast<int>(progress * m_bar_length);
        // auto progress_info = std::format("Progress: [{3:>3}%] {4}{0:{6}^{1}}{0:.^{2}}{5}", "", finished_length, m_bar_length - finished_length, static_cast<int>(progress * 100), m_opening_bracket, m_closing_bracket/*, m_done_char*/, "#"); 
        auto progress_info = std::format("Progress: [{:>3}%] {}{}{}{}", static_cast<int>(progress * 100), m_opening_bracket, fill{m_done_char, finished_length}, fill{m_undone_char, m_bar_length - finished_length}, m_closing_bracket);
        m_os << progress_info << std::flush;
    }


private:
    int m_bar_length;
    int m_data_length;
    char m_done_char;
    char m_undone_char;
    char m_opening_bracket;
    char m_closing_bracket;
    std::ostream& m_os;
};


} // namespace cpb


#endif // CPP_PROGRESS_BAR_H_
