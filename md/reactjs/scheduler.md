The react using messageChannel as a task to run the fiber reconcile,
the messageChannel will queue a task, an event-loop will run forever to pick up the jobs(callbacks) from tasks, microtasks, rendering etc.

the event-loop will push job to the javascript call stack each round, and the browser's main thread will run that job, when call stack empty, the event-loop will continue to run.

the event-loop algrithm looks like this:
```
while(true) {
	while (microtask = microtasks.pop()) {
		js_call_stack.push(microtask.callback);
	}

	if (task = tasks.pop()) {
		js_call_stack.push(task.callback);
	}

	if (is_time_to_rendering()) {
		for (cb in request_animation_frame_callbacks) {
			js_call_stack.push(cb)
		}
		style_calculation();
		layout();
		painting();
	}
}

```

the `microtasks` is the highest prioritied job in event-loop, if the scheduler using `microtasks`(like promise), it will block the main-thread since the schduler run the reconcile recursly.
the settimeout and setinterval can't get the callback immediately even though the second parmater was set to be 0, so there would be a lot of waste betweent the rendering frames.
the `is_time_to_rendering` was can not be established, thers is no standrad to make browser followed up, the browser decides the rendering time by itself, so the `requestAnimationFrame` would not be the option nethier.

