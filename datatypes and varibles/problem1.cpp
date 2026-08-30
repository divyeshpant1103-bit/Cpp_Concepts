#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <chrono>
#include <queue>
#include <stack>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std::chrono;

// ==========================================
// 1. Data Structures: Search Result (Linked List)
// ==========================================
struct SearchResult
{
    std::string filePath;
    SearchResult *next;

    SearchResult(const std::string &path) : filePath(path), next(nullptr) {}
};

class SearchResultList
{
public:
    SearchResult *head;
    SearchResult *tail;
    int count;

    SearchResultList() : head(nullptr), tail(nullptr), count(0) {}

    ~SearchResultList()
    {
        SearchResult *current = head;
        while (current != nullptr)
        {
            SearchResult *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void append(const std::string &path)
    {
        SearchResult *newNode = new SearchResult(path);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void appendAll(const std::vector<std::string> &paths)
    {
        for (const auto &p : paths)
        {
            append(p);
        }
    }

    void printResults() const
    {
        SearchResult *current = head;
        if (!current)
        {
            std::cout << "  [No results found]\n";
            return;
        }
        while (current != nullptr)
        {
            std::cout << "  -> " << current->filePath << "\n";
            current = current->next;
        }
    }
};

// ==========================================
// 2. Core Engine: File Indexer
// ==========================================
class FileIndexer
{
private:
    // Hash Maps for O(1) average case lookups
    std::unordered_map<std::string, std::vector<std::string>> filenameIndex;
    std::unordered_map<std::string, std::vector<std::string>> extensionIndex;

    // Cache map: maps directory path -> boolean (true if already indexed)
    std::unordered_map<std::string, bool> cacheMap;

    void processFile(const fs::directory_entry &entry)
    {
        std::string path = entry.path().string();
        std::string filename = entry.path().filename().string();
        std::string extension = entry.path().extension().string();

        filenameIndex[filename].push_back(path);
        if (!extension.empty())
        {
            extensionIndex[extension].push_back(path);
        }
    }

public:
    // Breadth-First Search Traversal (Level by Level)
    void scanBFS(const std::string &targetDirectory)
    {
        std::queue<std::string> q;
        q.push(targetDirectory);

        while (!q.empty())
        {
            std::string currentDir = q.front();
            q.pop();

            try
            {
                for (const auto &entry : fs::directory_iterator(currentDir))
                {
                    if (entry.is_directory())
                    {
                        q.push(entry.path().string());
                    }
                    else if (entry.is_regular_file())
                    {
                        processFile(entry);
                    }
                }
            }
            catch (const fs::filesystem_error &e)
            {
                // Ignore permission denied errors gracefully
            }
        }
    }

    // Depth-First Search Traversal (Deepest First using explicit Stack)
    void scanDFS(const std::string &targetDirectory)
    {
        std::stack<std::string> s;
        s.push(targetDirectory);

        while (!s.empty())
        {
            std::string currentDir = s.top();
            s.pop();

            try
            {
                for (const auto &entry : fs::directory_iterator(currentDir))
                {
                    if (entry.is_directory())
                    {
                        s.push(entry.path().string());
                    }
                    else if (entry.is_regular_file())
                    {
                        processFile(entry);
                    }
                }
            }
            catch (const fs::filesystem_error &e)
            {
                // Ignore permission denied errors gracefully
            }
        }
    }

    void indexDirectory(const std::string &targetDirectory, const std::string &mode = "BFS")
    {
        if (cacheMap.find(targetDirectory) != cacheMap.end())
        {
            std::cout << "[Cache] Directory '" << targetDirectory << "' is already indexed. Skipping scan.\n";
            return;
        }

        std::cout << "[Indexer] Scanning directory using " << mode << "...\n";
        if (mode == "BFS")
            scanBFS(targetDirectory);
        else
            scanDFS(targetDirectory);

        cacheMap[targetDirectory] = true;
        std::cout << "[Indexer] Indexing complete.\n";
    }

    // Getters for the Searcher class
    const std::unordered_map<std::string, std::vector<std::string>> &getFilenameIndex() const { return filenameIndex; }
    const std::unordered_map<std::string, std::vector<std::string>> &getExtensionIndex() const { return extensionIndex; }
};

// ==========================================
// 3. User Interface: Searcher
// ==========================================
class Searcher
{
private:
    const FileIndexer &indexer;

public:
    enum SearchMode
    {
        EXACT,
        EXTENSION,
        SUBSTRING
    };

    Searcher(const FileIndexer &idx) : indexer(idx) {}

    SearchResultList *search(const std::string &query, SearchMode mode)
    {
        SearchResultList *results = new SearchResultList();

        if (mode == EXACT)
        {
            auto it = indexer.getFilenameIndex().find(query);
            if (it != indexer.getFilenameIndex().end())
            {
                results->appendAll(it->second);
            }
        }
        else if (mode == EXTENSION)
        {
            // Ensure query starts with a dot
            std::string extQuery = (query[0] != '.') ? "." + query : query;
            auto it = indexer.getExtensionIndex().find(extQuery);
            if (it != indexer.getExtensionIndex().end())
            {
                results->appendAll(it->second);
            }
        }
        else if (mode == SUBSTRING)
        {
            // Must iterate over keys for substring match
            for (const auto &pair : indexer.getFilenameIndex())
            {
                if (pair.first.find(query) != std::string::npos)
                {
                    results->appendAll(pair.second);
                }
            }
        }
        return results;
    }
};

// ==========================================
// 4. Evaluation: Benchmark Runner
// ==========================================
class BenchmarkRunner
{
public:
    static void runBenchmark(FileIndexer &indexer, const std::string &targetDirectory, const std::string &query)
    {
        std::cout << "\n========== BENCHMARK TEST ==========\n";

        // 1. Raw Uncached Scan (Naive O(n) traversal)
        std::cout << "[Running] Naive Raw OS Scan...\n";
        auto startRaw = high_resolution_clock::now();
        int rawMatchCount = 0;
        try
        {
            for (const auto &entry : fs::recursive_directory_iterator(targetDirectory))
            {
                if (entry.is_regular_file() && entry.path().filename().string() == query)
                {
                    rawMatchCount++;
                }
            }
        }
        catch (const fs::filesystem_error &e)
        {
        }
        auto stopRaw = high_resolution_clock::now();
        auto durationRaw = duration_cast<microseconds>(stopRaw - startRaw);

        // 2. Ensure Indexed
        indexer.indexDirectory(targetDirectory, "BFS");

        // 3. Indexed Lookup (O(1) Hash Map)
        std::cout << "[Running] Indexed Hash Map Lookup...\n";
        Searcher searcher(indexer);
        auto startIndexed = high_resolution_clock::now();
        SearchResultList *results = searcher.search(query, Searcher::EXACT);
        auto stopIndexed = high_resolution_clock::now();
        auto durationIndexed = duration_cast<microseconds>(stopIndexed - startIndexed);

        // Print Metrics
        std::cout << "------------------------------------\n";
        std::cout << "Query: " << query << "\n";
        std::cout << "Matches Found: " << results->count << "\n";
        std::cout << "Raw Scan Time     : " << durationRaw.count() << " microseconds\n";
        std::cout << "Indexed Lookup Time: " << durationIndexed.count() << " microseconds\n";

        if (durationIndexed.count() > 0)
        {
            double speedup = static_cast<double>(durationRaw.count()) / durationIndexed.count();
            std::cout << "Speedup Factor    : " << speedup << "x faster\n";
        }
        std::cout << "====================================\n\n";

        delete results;
    }
};

// ==========================================
// 5. Main Execution (Interactive CLI)
// ==========================================
int main()
{
    std::cout << "========================================\n";
    std::cout << "        SMART FILE SEARCH TOOL\n";
    std::cout << "========================================\n\n";

    FileIndexer indexer;
    std::string targetDirectory;

    std::cout << "Enter the directory path to index (e.g., ./ or /Users/divyesh/Documents/): ";
    std::getline(std::cin, targetDirectory);

    std::string traverseMode;
    std::cout << "Choose indexing mode (BFS or DFS): ";
    std::getline(std::cin, traverseMode);

    // Normalize input
    if (traverseMode == "dfs" || traverseMode == "DFS")
    {
        traverseMode = "DFS";
    }
    else
    {
        traverseMode = "BFS"; // Default
    }

    // Build the initial index based on user input
    indexer.indexDirectory(targetDirectory, traverseMode);
    Searcher searcher(indexer);

    while (true)
    {
        std::cout << "\n----------------------------------------\n";
        std::cout << "1. Exact Match Search (e.g., problem1.cpp)\n";
        std::cout << "2. Extension Search (e.g., .txt or .cpp)\n";
        std::cout << "3. Substring Search (e.g., prob)\n";
        std::cout << "4. Run Benchmark (Raw Scan vs Indexed)\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an option (1-5): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        if (choiceStr == "5")
        {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        }

        if (choiceStr == "4")
        {
            std::string query;
            std::cout << "\nEnter exact filename to benchmark against raw OS scan: ";
            std::getline(std::cin, query);
            BenchmarkRunner::runBenchmark(indexer, targetDirectory, query);
            continue;
        }

        std::string query;
        std::cout << "\nEnter search query: ";
        std::getline(std::cin, query);

        Searcher::SearchMode mode;
        if (choiceStr == "1")
            mode = Searcher::EXACT;
        else if (choiceStr == "2")
            mode = Searcher::EXTENSION;
        else if (choiceStr == "3")
            mode = Searcher::SUBSTRING;
        else
        {
            std::cout << "Invalid option. Please try again.\n";
            continue;
        }

        // Measure search time
        auto start = high_resolution_clock::now();
        SearchResultList *results = searcher.search(query, mode);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        std::cout << "\n--- Search Results ---\n";
        results->printResults();
        std::cout << "\nFound " << results->count << " matches in " << duration.count() << " microseconds.\n";

        delete results; // Prevent memory leaks
    }

    return 0;
}