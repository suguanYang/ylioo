---
title: "JavaScript Event Loop and Task Scheduling"
---

```
while(true) {
	while (microtask = microtasks.pop()) {
		microtask.run_steps();
		// run_steps is the instruction of the task, includes the javascript callback
	}

	// run_steps will excute the callback if has
	if (task = tasks.pop()) {
		// settimeout, setinterval, scripts
		task.run_steps();
	}

	if (is_time_to_rendering()) {
		for (cb in request_animation_frame_callbacks) {
			js_call_stack.push(cb)
		}
		style_calculation();
		layout();
		painting();
	}

	sleep_until_a_task_appears();
}

```

normally the task was ordered by FIFO

## the setTimeout
### example 1
the first setTimeout task was poped out first, beacuse it pushed to task-queue first
```javascript
setTimeout(function () {console.log(1)}, 6);
let i = 0;
while(i < 1000000000) {
 i++;
}
setTimeout(function () {console.log(2)}, 4);
// 1
// 2
```
### example 2
the second task was poped out first, shows that the browser will re-shcedule the task order while javascript main thread was runing, in example 1, the second timeout was pushed to task immediately after js main call stack empty, the browser may doesn't have time to re-shcedule
```javascript
setTimeout(function () {console.log(1)}, 6);
setTimeout(function () {console.log(2)}, 4);
let i = 0;
while(i < 1000000000) {
 i++;
}
// 2
// 1
```
 
