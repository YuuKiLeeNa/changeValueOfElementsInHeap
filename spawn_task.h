#ifndef  __SPAWN_TASK_H__
#define __SPAWN_TASK_H__
#include<future>
#include<thread>
#include<utility>

template<typename FUN, typename ...ARGS>std::future<typename std::result_of<FUN(ARGS&&...)>::type>spawn_task(FUN&& f, ARGS&&...args)
{
	typedef typename std::result_of<FUN(ARGS&&...)>::type RESULT_TYPE;
	std::packaged_task<RESULT_TYPE(ARGS&&...)>packageTask(std::forward<FUN>(f));
	auto fu = packageTask.get_future();
	std::thread t(std::move(packageTask), std::forward<ARGS>(args)...);
	t.detach();
	return fu;
}

#endif