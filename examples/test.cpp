#include "progress_bar.hpp"

#include <chrono>
#include <iostream>
#include <ranges>
#include <thread>


int main() {
    int total = 100;
    cpb::progress_bar progress(100);
    for (auto i : std::views::iota(0, total)) {
        // Update the progress bar
        progress.update(i + 1, [](int v) {
            std::cout << "Some other output " << v << '\n';
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\n";
    progress.done_char('^');
    progress.undone_char('_');
    for (auto b : std::views::iota(0, total)) {
        progress.update(b + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "\n";
    progress.done_char('X');
    progress.undone_char('-');
    for (auto b : std::views::iota(0, total)) {
        progress.update(b + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 输出一个换行来防止进度条下一行被覆盖
    std::cout << std::endl;
}
