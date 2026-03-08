#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

namespace lex::cli {

// Animated spinner/progress bar for CLI feedback
class AnimatedSpinner {
public:
    enum Style { Dots, Braille, Arrow, Pulse, Earth, Moon, Clock, Bars };

    AnimatedSpinner(const std::string& message = "", Style style = Style::Dots)
        : message_(message), style_(style), running_(false), progress_(-1) {}

    void set_progress(int percent) { progress_ = percent; }
    void set_message(const std::string& msg) { message_ = msg; }

    void start() {
        running_ = true;
        thread_ = std::thread(&AnimatedSpinner::animate, this);
    }

    void stop() {
        running_ = false;
        if (thread_.joinable()) thread_.join();
        clear_line();
    }

    void success(const std::string& msg = "") {
        stop();
        std::cout << "\r\033[32m✓\033[0m " << (msg.empty() ? message_ : msg) << "\n";
    }

    void fail(const std::string& msg = "") {
        stop();
        std::cout << "\r\033[31m✗\033[0m " << (msg.empty() ? message_ : msg) << "\n";
    }

private:
    std::string message_;
    Style style_;
    std::atomic<bool> running_;
    std::atomic<int> progress_;
    std::thread thread_;

    const std::vector<std::vector<std::string>> frames_ = {
        {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"}, // Braille
        {"◜", "◠", "◝", "◞", "◡", "◟"},                       // Dots
        {"←", "↖", "↑", "↗", "→", "↘", "↓", "↙"},               // Arrow
        {"◉", "◎", "●", "◎"},                                   // Pulse
        {"🌍", "🌎", "🌏"},                                      // Earth
        {"🌑", "🌒", "🌓", "🌔", "🌕", "🌖", "🌗", "🌘"},      // Moon
        {"🕛", "🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚"}, // Clock
        {"▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"}                // Bars
    };

    void animate() {
        const auto& frames = frames_[static_cast<int>(style_)];
        size_t frame = 0;

        // Hide cursor
        std::cout << "\033[?25l";

        while (running_) {
            std::string output = "\r";

            if (progress_ >= 0 && progress_ <= 100) {
                // Progress bar mode
                int filled = progress_ / 5;
                output += "[";
                for (int i = 0; i < filled; ++i) output += "#";
                for (int i = 0; i < 20 - filled; ++i) output += "-";
                output += "] ";
                output += std::to_string(progress_) + "% ";
                output += message_;
            } else {
                // Spinner mode
                output += "\033[36m" + frames[frame] + "\033[0m ";
                output += message_;
            }

            std::cout << output << std::flush;
            frame = (frame + 1) % frames.size();
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }

        // Show cursor
        std::cout << "\033[?25h";
    }

    void clear_line() {
        std::cout << "\r" << std::string(message_.size() + 50, ' ') << "\r" << std::flush;
    }
};

} // namespace lex::cli
