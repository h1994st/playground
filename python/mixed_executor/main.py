import asyncio
import logging
import random
import sys
import time
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor

import uvloop


def blocks(kind: str, n: int):
    log = logging.getLogger(f"{kind} blocks({n})")
    log.info("running")
    duration = random.random() * 1.9 + 0.1
    log.info(f"sleep {duration} seconds")
    time.sleep(duration)
    log.info("done!")
    return n**2


async def main():
    log = logging.getLogger("main")
    log.info("starting")

    log.info("creating executor tasks")
    loop = asyncio.get_event_loop()
    thread_executor = ThreadPoolExecutor(max_workers=2)
    process_executor = ProcessPoolExecutor(max_workers=2)

    blocking_tasks = []
    for i in range(12):
        if i % 2 == 0:
            blocking_task = loop.run_in_executor(thread_executor, blocks, "thread", i)
        else:
            blocking_task = loop.run_in_executor(process_executor, blocks, "process", i)
        blocking_tasks.append(blocking_task)

    log.info("waiting for executor tasks")
    results = await asyncio.gather(*blocking_tasks)
    log.info(f"results: {results}")

    log.info("exiting")


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(levelname)s PID %(process)5s %(threadName)25s %(name)18s: %(message)s",
        stream=sys.stderr,
    )

    asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
    loop = asyncio.get_event_loop()
    try:
        loop.run_until_complete(main())
    finally:
        loop.close()
