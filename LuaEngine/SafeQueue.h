#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>

template <class T>
class SafeQueue
{
public:
	SafeQueue(void)
		: q()
		, m()
		, c()
	{}

	~SafeQueue(void)
	{}

	void push(T t)
	{
		std::lock_guard<std::mutex> lock(m);
		q.push(t);
		c.notify_one();
	}

	T pop(void)
	{
		std::unique_lock<std::mutex> lock(m);
		while (q.empty())
		{
			c.wait(lock);
		}
		T val = q.front();
		q.pop();
		return val;
	}

	T front(void)
	{
		std::lock_guard<std::mutex> lock(m);
		T val = q.front();
		c.notify_one();
		return val;
	}

	bool empty(void)
	{
		std::lock_guard<std::mutex> lock(m);
		bool val = q.empty();
		c.notify_one();
		return val;
	}

private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
};