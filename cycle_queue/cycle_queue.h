//============================================================================
// Name        : ring-queue.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#pragma once

#include<iostream>
using namespace std;

const int MAX_QUEUE_SIZE = 5;
template<typename T>
class CycleQueue
{
private:
    T m_array[MAX_QUEUE_SIZE]; // 留一个位置不用，以此区分满队列和空队列
    int m_nHead;
    int m_nTail;

public:
    CycleQueue() :
        m_nHead(0), m_nTail(0)
    {
    }

    bool in_queue(const T & data)
    {
        if (full())
        {
            out_queue();
        }

        m_array[m_nTail] = data;
        m_nTail = (m_nTail + 1) % MAX_QUEUE_SIZE;
        return true;
    }

    //出队操作，将队首数据复制并返回，改变队首指针
    T out_queue()
    {
        if (empty())
        {
            throw("队列已空");
        }

        T temp = m_array[m_nHead];
        m_nHead = (m_nHead + 1) % MAX_QUEUE_SIZE;
        return temp;
    }

    T sum()
    {
        T sum = 0;
        if (empty())
            return sum;
        for (int i = m_nHead; i != m_nTail;)
        {
            sum += m_array[i];
            i = (i + 1) % MAX_QUEUE_SIZE;
        }
        return sum;
    }

    void print_queue()
    {
        if (empty())
        {
            return;
        }
        for (int i = m_nHead; i != m_nTail;)
        {
            cout << m_array[i] << " ";
            i = (i + 1) % MAX_QUEUE_SIZE;
        }
    }

    bool empty()
    {
        return m_nTail == m_nHead;
    }

    bool full()
    {
        return (m_nTail + 1) % MAX_QUEUE_SIZE == m_nHead;
    }

    int size()
    {
        return (m_nTail - m_nHead + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    }

};
