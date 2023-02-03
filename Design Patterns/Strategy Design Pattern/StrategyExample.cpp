// StrategyExamples.cpp

//  Pattern Description:
//  The strategy pattern is a behavioral design pattern that allows an algorithm's behavior to be selected at runtime.
//  It defines a family of algorithms, encapsulates each one as an object, and makes them interchangeable.
//  The strategy pattern lets the algorithm vary independently from clients that use it.

//  In this example, we have an abstract base class called SortStrategy which defines the interface for sorting algorithms.
//  Then, we have two concrete implementations of this interface: bubbleSort and quickSort. The Sorter class is the client that uses these sorting algorithms.
//  It has a pointer to a SortStrategy object, which is set to an instance of bubbleSort or quickSort.
//  The client can then call the Sort method on the strategy object to sort the data,
//  and can change the strategy at runtime by calling the set_strategy method and passing in a different strategy object.

#include <iostream>
#include<vector>

class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void Sort(std::vector<int>& data) = 0;
};

class BubbleSort : public SortStrategy {
public:
    void Sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
};

class QuickSort : public SortStrategy {
public:
    void Sort(std::vector<int>& data) override
    {
        Quicksort(data, 0, data.size() - 1);
    }

private:
    void Quicksort(std::vector<int>& data, int low, int high) {
        if (low < high) {
            int pivot_index = Partition(data, low, high);
            Quicksort(data, low, pivot_index - 1);
            Quicksort(data, pivot_index + 1, high);
        }
    }

    int Partition(std::vector<int>& data, int low, int high) {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (data[j] <= pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};


class Sorter {
public:
    Sorter(std::unique_ptr<SortStrategy> strategy) : strategy_(std::move(strategy)) {}
    void Sort(std::vector<int>& data) { strategy_->Sort(data); }
    void SetStrategy(std::unique_ptr<SortStrategy> strategy) { strategy_ = std::move(strategy); }
private:
    std::unique_ptr<SortStrategy> strategy_;
};

int main() {
    std::vector<int> bubbleData = { 3, 4, 2, 1, 6, 5 };
    auto quickData = bubbleData;
    auto sorter = std::make_unique<Sorter>(std::make_unique<BubbleSort>());
    sorter->Sort(bubbleData);
    // Print sorted data
    for (auto& i : bubbleData) {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    sorter->SetStrategy(std::make_unique<QuickSort>());
    sorter->Sort(quickData);
    // Print sorted data
    for (auto& i : quickData) {
        std::cout << i << " ";
    }
}

