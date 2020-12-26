#ifndef _SORT_H_
#define _SORT_H_

#include "Vector.h"
#include <chrono>

typedef unsigned int DATA;

class Record
{
public:
    Record()
        : time_(0),
          space_(0),
          comp_(0),
          swap_(0)
    {
    }

    std::chrono::duration<double> time_;
    int space_;
    int comp_;
    int swap_;
};

void Swap(DATA &data_1, DATA &data_2)
{
    DATA temp = 0;
    temp = data_1;
    data_1 = data_2;
    data_2 = temp;
    return;
}

class Heap
{
public:
    Heap() {}
    ~Heap() {}
    int Size() { return nodes_.Size(); }
    bool Empty() { return Size() ? false : true; }
    void Insert(const DATA &elem)
    {
        nodes_.PushBack(elem);
        right_ = Size() - 1;
        AjustUp();
    }
    DATA GetMax()
    {
        return nodes_[0];
    }
    Vector<DATA> HeapSort(Record &record)
    {
        record.space_ += Size();
        for (int i = Size() - 1; i > 0; --i)
        {
            Swap(nodes_[0], nodes_[i]);
            ++record.swap_;
            right_--;
            AjustDown(record);
        }
        return nodes_;
    }

private:
    int Lc(int pr)
    {
        int ans = 0;
        return ((ans = 1 + pr * 2) <= right_) ? ans : -1;
    }
    int Rc(int pr)
    {
        int ans = 0;
        return ((ans = (1 + pr) * 2) <= right_) ? ans : -1;
    }
    int Pr(int c)
    {
        return (c > 0) ? (c - 1) / 2 : -1;
    }
    int FirstPriority(int pr, Record &record)
    {
        int lc = Lc(pr);
        int rc = Rc(pr);
        int first_priority = pr;
        ++record.comp_;
        if (lc != -1 && nodes_[first_priority] < nodes_[lc])
        {
            first_priority = lc;
        }
        ++record.comp_;
        if (rc != -1 && nodes_[first_priority] < nodes_[rc])
        {
            first_priority = rc;
        }

        return first_priority;
    }
    void AjustUp() //入堆后上调整
    {
        int low = Size() - 1;
        int high = 0;
        while ((high = Pr(low)) != -1)
        {
            if (nodes_[low] < nodes_[high])
            {
                break;
            }
            Swap(nodes_[low], nodes_[high]);
            low = high;
        }
    }
    void AjustDown(Record &record) //出堆后下调整
    {
        int low = 0;
        int high = 0;
        while ((low = FirstPriority(high, record)) != high)
        {
            ++record.comp_;
            ++record.swap_;
            Swap(nodes_[low], nodes_[high]);
            high = low;
        }
    }
    int right_;
    Vector<DATA> nodes_;
};

Record BubbleSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    record.space_ += vec.Size();
    int length = vec.Size();
    for (int i = 0; i < length - 1; ++i)
    {
        int one_round_swap = 0;
        for (int j = 0; j < length - i - 1; ++j)
        {
            ++record.comp_;
            if (vec[j] > vec[j + 1])
            {
                Swap(vec[j], vec[j + 1]);
                ++one_round_swap;
                ++record.swap_;
            }
        }
        if (one_round_swap == 0)
        {
            break;
        }
    }
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

Record SelectSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    int length = vec.Size();
    record.space_ += length;
    for (int i = 0; i < length - 1; ++i)
    {
        int k = i;
        for (int j = i + 1; j < length; j++)
        {
            ++record.comp_;
            if (vec[j] < vec[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            ++record.swap_;
            Swap(vec[i], vec[k]);
        }
    }
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

Record InsertSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    int length = vec.Size();
    record.space_ += length;
    for (int i = 0; i < length - 1; ++i)
    {
        DATA temp = vec[i + 1];
        int j = i;
        while (j >= 0 && temp < vec[j])
        {
            ++record.comp_;
            vec[j + 1] = vec[j];
            --j;
        }
        ++record.comp_;
        ++record.swap_;
        vec[j + 1] = temp;
    }
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

Record ShellSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    int length = vec.Size();
    record.space_ += length;
    int gap = length + 1;
    do
    {
        gap = gap / 3 + 1;
        for (int i = gap; i < length; i++)
        {
            DATA temp = vec[i];
            int j = i - gap;
            while (j >= 0 && temp < vec[j])
            {
                ++record.comp_;
                vec[j + gap] = vec[j];
                j = j - gap;
            }
            ++record.comp_;
            ++record.swap_;
            vec[j + gap] = temp;
        }
    } while (gap > 1);
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

void QuickSort(Vector<DATA> &vec, int left, int right, Record &record)
{
    if (left < right)
    {
        int pivot_pos = left;
        DATA pivot = vec[left];
        for (int i = left + 1; i <= right; ++i)
        {
            ++record.comp_;
            if (vec[i] < pivot)
            {
                ++pivot_pos;
                if (pivot_pos != i)
                {
                    ++record.swap_;
                    Swap(vec[pivot_pos], vec[i]);
                }
            }
        }
        vec[left] = vec[pivot_pos];
        vec[pivot_pos] = pivot;
        QuickSort(vec, left, pivot_pos - 1, record);
        QuickSort(vec, pivot_pos + 1, right, record);
    }
    return;
}

Record QuickSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    record.space_ += vec.Size();
    QuickSort(vec, 0, vec.Size() - 1, record);
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

Record HeapSort(Vector<DATA> vec)
{
    Record record;
    Heap vec2;
    for (int i = 0; i < vec.Size(); ++i)
    {
        vec2.Insert(vec[i]);
    }
    auto start = std::chrono::system_clock::now();
    vec = vec2.HeapSort(record);
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

void Merge(Vector<DATA> &vec, Vector<DATA> &vec_assist, const int left, const int mid, const int right, Record &record)
{
    for (int i = left; i <= right; ++i)
    {
        vec_assist[i] = vec[i];
    }
    int assist_1 = left, assist_2 = mid + 1, index = left;
    while (assist_1 <= mid && assist_2 <= right)
    {
        ++record.comp_;
        if (vec_assist[assist_1] <= vec_assist[assist_2])
        {
            vec[index++] = vec_assist[assist_1++];
        }
        else
        {
            vec[index++] = vec_assist[assist_2++];
        }
    }
    while (assist_1 <= mid)
    {
        vec[index++] = vec_assist[assist_1++];
    }
    while (assist_2 <= right)
    {
        vec[index++] = vec_assist[assist_2++];
    }
}

void MergeSort(Vector<DATA> &vec, Vector<DATA> &vec_assist, int left, int right, Record &record)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    MergeSort(vec, vec_assist, left, mid, record);
    MergeSort(vec, vec_assist, mid + 1, right, record);
    Merge(vec, vec_assist, left, mid, right, record);
}

Record MergeSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    Vector<DATA> vec_assist = vec;
    record.space_ += 2 * vec.Size();
    MergeSort(vec, vec_assist, 0, vec.Size() - 1, record);
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

int MaxBit(Vector<DATA> vec)
{
    int max_data = vec[0];
    for (int i = 1; i < vec.Size(); ++i)
    {
        if (vec[i] > max_data)
        {
            max_data = vec[i];
        }
    }
    int bit_num = 0;
    while (max_data)
    {
        ++bit_num;
        max_data /= 10;
    }
    return bit_num;
}

int Digit(DATA number, int d)
{
    int quantity = 1;
    while (--d > 0)
    {
        quantity *= 10;
    }
    return (number / quantity) % 10;
}

Record RadixSort(Vector<DATA> vec)
{
    Record record;
    auto start = std::chrono::system_clock::now();
    int digit_num = MaxBit(vec);
    int length = vec.Size();
    Vector<DATA> bucket(length, 0);
    record.space_ += 2 * length;
    record.space_ += 10;
    Vector<int> count(10, 0);
    for (int d = 1; d <= digit_num; ++d)
    {
        for (int i = 0; i < 10; i++)
        {
            count[i] = 0;
        }
        for (int i = 0; i < length; ++i)
        {
            ++count[Digit(vec[i], d)];
        }
        for (int i = 1; i < 10; ++i)
        {
            count[i] += count[i - 1];
        }

        for (int i = length - 1; i >= 0; --i)
        {
            int k = Digit(vec[i], d);
            bucket[count[k] - 1] = vec[i];
            --count[k];
        }
        for (int i = 0; i < length; ++i)
        {
            vec[i] = bucket[i];
        }
    }
    auto end = std::chrono::system_clock::now();
    record.time_ = end - start;
    return record;
}

#endif //!_SORT_H_