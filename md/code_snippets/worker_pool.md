
```javascript
import * as Comlink from "comlink";

import debug from "./debug.ts";

type PWorker = {
  runner: Comlink.Remote<{
    run: (input: string) => Promise<string>;
  }>;
  status: "ready" | "runing";
};

export default class Pool {
  private pendingQ: ((worker: PWorker) => Promise<string>)[] = [];
  private filename: string;
  private maxWorkers: number;
  private workers: PWorker[];

  constructor(options: { filename: string; maxWorkers: number }) {
    this.filename = options.filename;
    this.maxWorkers = options.maxWorkers;
    this.workers = [];
  }

  async run(input: string) {
    let onResolve: (value: unknown) => void;
    const pendingSignal = new Promise((res) => (onResolve = res));
    let ret: string;
    let error: unknown = null;

    this.pendingQ.push((worker) =>
      worker.runner
        .run(input)
        .then(
          (res) => (ret = res),
          (err) => (error = err)
        )
        .catch((err) => (error = err))
        .finally(() => {
          onResolve(null);
        })
    );

    this.runNext();

    await pendingSignal;

    if (error !== null) {
      return Promise.reject(error);
    }

    return ret!;
  }

  private getWorker() {
    const readyWorker = this.workers.find(
      (worker) => worker.status === "ready"
    );
    if (readyWorker) {
      return readyWorker;
    }

    const worker: PWorker = {
      runner: Comlink.wrap(new Worker(this.filename)),
      status: "ready",
    };
    this.workers.push(worker);
    return worker;
  }

  private runNext() {
    if (
      this.workers.filter((w) => w.status === "runing").length <
        this.maxWorkers &&
      this.pendingQ.length > 0
    ) {
      const worker = this.getWorker();
      worker.status = "runing";
      const nextRun = this.pendingQ.shift()!;
      nextRun(worker).finally(() => {
        worker.status = "ready";
        this.runNext();
      });
      debug("WorkerPool runing: ", this.pendingQ.length, this.workers.length);
    }
  }
}
```
