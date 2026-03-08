#pragma once

#include <filesystem>
#include <functional>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <atomic>

namespace lex::cli {

namespace fs = std::filesystem;

// Cross-platform file watcher using efficient polling
class FileWatcher {
public:
    using Callback = std::function<void(const std::string&)>;

    FileWatcher(const std::vector<std::string>& files, Callback callback)
        : files_(files), callback_(std::move(callback)), running_(true) {}

    void start() {
        // Record initial modification times
        for (const auto& file : files_) {
            try {
                mtimes_[file] = fs::last_write_time(file);
            } catch (...) {}
        }
        watch_thread_ = std::thread(&FileWatcher::watch_loop, this);
    }

    void stop() {
        running_ = false;
        if (watch_thread_.joinable()) {
            watch_thread_.join();
        }
    }

    ~FileWatcher() { stop(); }

private:
    std::vector<std::string> files_;
    Callback callback_;
    std::atomic<bool> running_;
    std::thread watch_thread_;
    std::map<std::string, fs::file_time_type> mtimes_;

    void watch_loop() {
        while (running_) {
            check_changes();
            // Poll every 200ms (more responsive than 500ms)
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    void check_changes() {
        for (const auto& file : files_) {
            try {
                auto current_mtime = fs::last_write_time(file);
                if (mtimes_[file] != current_mtime) {
                    mtimes_[file] = current_mtime;
                    callback_(file);
                }
            } catch (...) {}
        }
    }
};

} // namespace lex::cli
