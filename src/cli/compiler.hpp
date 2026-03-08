#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <future>
#include <thread>
#include <utility>

#include "../lex/lex.hpp"

namespace lex::cli {

namespace fs = std::filesystem;

// Parallel file compiler with thread pool
class ParallelCompiler {
public:
    explicit ParallelCompiler(size_t max_threads = 0) {
        max_threads_ = max_threads > 0 ? max_threads : 
            std::max(1u, std::thread::hardware_concurrency());
    }

    std::vector<std::pair<std::string, bool>> compile_all(
        const std::vector<std::string>& files,
        const std::string& output_dir,
        const std::vector<Target>& targets,
        const std::vector<std::string>& target_names,
        const CompileOptions& options) {

        std::vector<std::pair<std::string, bool>> results;
        std::vector<std::future<std::pair<std::string, bool>>> futures;

        for (const auto& file : files) {
            futures.push_back(std::async(std::launch::async, [=]() {
                auto opts = options;
                opts.source_name = file;
                bool success = compile_single(file, output_dir, targets, target_names, opts);
                return std::make_pair(file, success);
            }));

            // Limit concurrent tasks
            if (futures.size() >= max_threads_) {
                for (auto& f : futures) results.push_back(f.get());
                futures.clear();
            }
        }

        for (auto& f : futures) results.push_back(f.get());
        return results;
    }

private:
    size_t max_threads_;

    static bool compile_single(
        const std::string& input_file,
        const std::string& output_dir,
        const std::vector<Target>& targets,
        const std::vector<std::string>& targetNames,
        const CompileOptions& options) {

        CompileResult result = compile_file(input_file, options);
        if (result.has_errors()) return false;

        fs::path input_path(input_file);
        std::string base_name = input_path.stem().string();

        for (size_t i = 0; i < targets.size() && i < targetNames.size(); ++i) {
            std::string extension = target_extension(targetNames[i]);
            fs::path output_path = fs::path(output_dir) / (base_name + extension);

            try {
                std::ofstream file(output_path);
                if (!file.is_open()) return false;
                file << (result.outputs.count(targetNames[i]) ?
                         result.outputs.at(targetNames[i]) : "");
            } catch (...) { return false; }
        }
        return true;
    }
};

} // namespace lex::cli
